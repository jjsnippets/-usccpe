// CPE 3201 - EMBEDDED SYSTEMS
// Group 4      TTh 7:30 AM - 10:30 AM LB 285 TC
// Cabatas, Art Louise; Cagasan, Mar Joseph; Lao, Karl Vincent; Sarcol, Joshua	BS CpE - 3      2026/05
// Design Project (Line Follower)

#include <xc.h>
#include <pic16f877a.h>
#include <stdint.h>

#pragma config FOSC  = HS       // High-Speed crystal oscillator
#pragma config WDTE  = OFF      // Watchdog Timer disabled
#pragma config PWRTE = ON       // Power-up Timer enabled (stabilises supply)
#pragma config BOREN = ON       // Brown-out Reset enabled
#pragma config LVP   = OFF      // Low-Voltage Programming OFF (frees RB3)
#pragma config CP    = OFF      // Flash code protection off
#pragma config CPD   = OFF      // Data EEPROM code protection off
#pragma config WRT   = OFF      // Flash write protection off

// Hardware configutation
#define _XTAL_FREQ  20000000UL  // 20 MHz

// Speed parameters
#define BASE_SPEED      110     // Normal driving speed
#define RECOVERY_SPEED  120     // Speed when searching for a lost line

// PID parameters 
#define KP              18      // Proportional gain (integer scaled)
#define KI              0       // Integral gain
#define KD              16      // Derivative gain
#define INTEGRAL_MAX    100     // Integral windup clamp
#define INTEGRAL_MIN    (-100)

// Startup delays
#define START_DELAY         1000
#define COUNTDOWN_STEP_MS   10

// Sensors: Sensor sees LINE (black) when ADC > THRESHOLD
#define CALIB_SAMPLES   200     // Number of ADC readings to average per sensor
#define LOST_LINE_TIME  3000    // Broken line grace period (cycles), instead of interrupt logic

// TB6612FNG
#define PWM_DUTY_CAP    138     // To safely drive the motors
                                // Motors fed directly from 11.1V battery
                                // cap duty cycle to ~54% (6V/11.1V)
#define REVERSE_SCALE   1       // Divisor for reverse motor speed (1 = no attenuation)

// Port and pin names
#define AIN1        PORTDbits.RD0       // Left  motor dir bit 1
#define AIN2        PORTDbits.RD1       // Left  motor dir bit 2
#define BIN1        PORTDbits.RD2       // Right motor dir bit 1
#define BIN2        PORTDbits.RD3       // Right motor dir bit 2
#define STBY        PORTDbits.RD4       // Driver standby (HIGH = enabled)
#define TRIMMER_CH  6                   // AN6 (RE1)

// Display to LEDs
#define LEDS(x) do { PORTB = ((x) & 0b00111111); } while(0)

// Convenience macros for movement
#define MOTOR_FORWARD(p1, p2)   do { p1 = 1; p2 = 0; } while(0)
#define MOTOR_REVERSE(p1, p2)   do { p1 = 0; p2 = 1; } while(0)
#define MOTOR_BRAKE(p1, p2)     do { p1 = 1; p2 = 1; } while(0)
#define MOTOR_COAST(p1, p2)     do { p1 = 0; p2 = 0; } while(0)

// Clamp function
#define CLAMP(val, lo, hi)  ((val) < (lo) ? (lo) : ((val) > (hi) ? (hi) : (val)))

// Sensor position weights for weighted-average error calculation
// 0 = Far-left sensor, 5 = Far right sensor
// Scaled by 16 (2^4) to preserve two decimal places during PID integer arithmetic
static const int16_t SENSOR_WEIGHT[6] = {120, 48, 16, -16, -48, -120};

// Motor selection
typedef enum {
    MOTOR_LEFT  = 0,
    MOTOR_RIGHT = 1
} MotorID;

// Motor direction states
typedef enum {
    DIR_FORWARD = 0,
    DIR_REVERSE = 1,
    DIR_BRAKE   = 2,
    DIR_COAST   = 3
} MotorDir;

// Robot operational states
typedef enum {
    STATE_FOLLOWING = 0,    // Actively following line
    STATE_LOST      = 1     // Line lost - recovery behaviour active
} RobotState;

// Function prototypes
int16_t PIDError(uint8_t sensor_mask);
uint16_t ADCRead(uint8_t channel);
void MotorsDrive(int16_t left_speed, int16_t right_speed);
void SetMotorDirection(MotorID motor, MotorDir dir);
void SetMotorSpeed(MotorID motor, uint8_t speed);
void MotorsStop(void);
void inline DelayMS(uint16_t ms);

// Global variables
int16_t  g_last_error = 0;
int16_t  g_integral   = 0;
uint16_t g_lost_counter = 0;        // Time (cycles) since line was last seen
uint16_t g_line_threshold = 512;    // Startup default, Computed during calibration


void main() {
    // Local variables
    RobotState  state = STATE_FOLLOWING;    // State machine, starting position assumes robot is at line
    uint8_t     sensor_mask = 0;            // Bitmask of sensor readings (1 == line detected)
    uint16_t    adc_val;                    // Current ADC value reading

    // Configuration and set-up
    {
        // GPIO ports setup
        // Unused ports set as output
        TRISA = 0x2F; PORTA = 0x00;     // 00i0 iiii (0x2F)
                                        // --q- qqqq QTR-8A sensor analog inputs (lhs)
                                        // ---x ---- (RA4 cannot be used as analog input)

        TRISB = 0xC0; PORTB = 0x00;     // iioo oooo (0xC0)
                                        // --ll llll LED line indicator outputs
                                        // pp-- ---- Reserved for ICSP (unused in final design)

        TRISC = 0x00; PORTC = 0x00;     // 0000 0oo0 (0x00)
                                        // ---- --b- PWMB output
                                        // ---- -a-- PWMA output

        TRISD = 0x00; PORTD = 0x00;     // 000o oooo (0x00)
                                        // ---- ---a AIN1 output
                                        // ---- --a- AIN2 output
                                        // ---- -b-- BIN1 output
                                        // ---- b--- BIN2 output
                                        // ---s ---- STBY output

        TRISE = 0x07; PORTE = 0x00;     // 0000 0iii (0x07)
                                        // ---- ---q QTR-8A sensor analog inputs (rhs)
                                        // ---- --t- Trimmer analog input
                                        // ---- -u-- Unused analog input (ADCON1 override)

        // A/D Module set-up
        ADCON1 = 0x80;                  // 1000 0000 (0x80)
                                        // ---- 0000 All analog pins
                                        // -0-- ---- FOSC/32 conversion clock (ADCS2)
                                        // 1--- ---- Right justified
        
        ADCON0 = 0x81;                  // 1000 0001 (0x81)
                                        // ---- ---1 Turn on A/D module
                                        // ---- -g-- Clear GO/DONE
                                        // --aa a--- Clear channel select
                                        // 10-- ---- FOSC/32 conversion clock (ADCS1:ADCS0)

        // Timer2 as PWM
        PR2 = 0xFF;                     // (Period length is mostly just for motor smoothness)
                                        // PWM frequency ~4.88 kHz at 20 MHz (FOSC/32, prescale 1:4)
                                        // Duty cycle ceiling = 4*(PR2+1) = 1024 counts.
        T2CON = 0x05;                   // 0000 0101 (0x05)
                                        // ---- --01 1:4 prescaler (PWM period = (255+1)*4*4*(1/20MHz) ~= 204.8us)
                                        // ---- -1-- Turn on Timer2
                                        // -000 ---- 1:1 postscaler (unused for PWM, only affects TMR2IF rate)
        
        // CCP modules setup (both as PWM)
        CCP1CON = 0x0C;                 // 0000 1100 (0x0C)
                                        // ---- 11xx CCP1 as PWM
        CCPR1L = 0x00;                  // --00 ---- initialize to 0% duty cycle

        CCP2CON = 0x0C;                 // 0000 1100 (0x0C)
                                        // ---- 11xx CCP2 as PWM
        CCPR2L = 0x00;                  // --00 ---- initialize to 0% duty cycle

        // Turn on all LEDs as indication for successful port configuration
        LEDS(0x3F); DelayMS(START_DELAY);
    }

    // Start motors stopped
    STBY = 1;
    MotorsStop();

    /* Use trimmer as fine tuning during calibration
    {
        // Read trimmer
        adc_val  = ADCRead(TRIMMER_CH);
        LEDS(adc_val / 16); DelayMS(START_DELAY * 2);
        
        // Base speed as value between BASE_SPEED_MIN to BASE_SPEED_MAX (linear)
        // Base speed can be changed to PID parameters with similar math
        BASE_SPEED = (uint8_t)(BASE_SPEED_MIN +
            ((uint32_t)adc_val * (BASE_SPEED_MAX - BASE_SPEED_MIN)/ 1023UL));
    }
    */

    // Calibrate sensors
    {
        uint16_t cal_min = 1023;
        uint16_t cal_max = 0;

        // Calibration window
        // Operator sweeps robot over track for START_DELAY duration
        uint32_t cal_end = CALIB_SAMPLES;
        for(uint16_t s = cal_end; s > 0; s--) {
            for(uint8_t i = 0; i < 6; i++) {
                uint16_t val = ADCRead(i);
                if(val < cal_min) cal_min = val;
                if(val > cal_max) cal_max = val;
            }
            LEDS(s);            // "samples left" indicator
            __delay_ms(5);
        }

        g_line_threshold = (cal_min + cal_max) / 2;

        // Turn off all LEDs to indicate finished calibration 
        LEDS(0x00);
        DelayMS(START_DELAY);
    }

    // Show how centered the robot is
    {
        // Copy from main program loop
        for(int16_t i = START_DELAY; i > 0; i--){
            sensor_mask = 0;
            for(uint8_t j = 0; j < 6; j++)
                if(ADCRead(j) > g_line_threshold)
                    sensor_mask |= (uint8_t)(1U << j);
            LEDS(sensor_mask);
            __delay_ms(1);
        }
    }

    // LEDs Countdown animation
    LEDS(0x03); DelayMS(START_DELAY);   // [- - - - o o]
    LEDS(0x0F); DelayMS(START_DELAY);   // [- - o o o o]
    LEDS(0x3F); DelayMS(START_DELAY);   // [o o o o o o]

    // Start the robot moving forward
    MotorsDrive((uint8_t)BASE_SPEED, (uint8_t)BASE_SPEED);

    // Main control loop
    while(1) {
        // Current reading
        sensor_mask = 0;
        for(uint8_t i = 0; i < 6; i++)              // Read all sensors then 
            if(ADCRead(i) > g_line_threshold)       // Convert readings to a bitmask
                sensor_mask |= (uint8_t)(1U << i);  // Bit i is SET when sensor i sees the line

        // State machine
        switch(state) {
            // When robot is on line
            case STATE_FOLLOWING: {
                LEDS(sensor_mask);                  // LEDs showing what the sensor currently sees

                // If robot loses line...
                if(sensor_mask == 0){
                    // If line was to the side, then transition to STATE_LOST immediately
                    if(g_last_error > 45 || g_last_error < -45) {
                        state = STATE_LOST;
                        g_lost_counter = 0;

                    // Otherwise, probably just broken line and coast forward within grace period
                    } else {
                        g_lost_counter++;           // Change to STATE_LOST after grace period
                        if(g_lost_counter >= LOST_LINE_TIME) {
                            state = STATE_LOST;
                            g_lost_counter = 0;
                        } else                      // Coast forward: keeping PID and motor values the same
                            MotorsDrive((int16_t)BASE_SPEED, (int16_t)BASE_SPEED);
                    }
                    break;
                }

                // Otherwise robot is in line
                g_lost_counter = 0;

                // PID integer computation
                int16_t error = PIDError(sensor_mask);
                int16_t derivative = error - g_last_error;
                g_integral += error;
                g_integral = (int16_t) CLAMP(g_integral, INTEGRAL_MIN, INTEGRAL_MAX);

                int16_t pid = (int16_t)(
                    (((int32_t)KP * error) >> 4) +          // Equivalent to dividing by 16
                    (((int32_t)KI * g_integral) >> 4) +
                    (((int32_t)KD * derivative) >> 4)
                );

                g_last_error = error;

                // Set individual motor speeds
                int16_t left_spd  = (int16_t)BASE_SPEED - pid;
                        left_spd  = (int16_t)CLAMP(left_spd,  -PWM_DUTY_CAP, PWM_DUTY_CAP);
                        if(left_spd < 0) left_spd = (int16_t)(left_spd / REVERSE_SCALE);
                
                int16_t right_spd = (int16_t)BASE_SPEED + pid;
                        right_spd = (int16_t)CLAMP(right_spd, -PWM_DUTY_CAP, PWM_DUTY_CAP);
                        if(right_spd < 0) right_spd = (int16_t)(right_spd / REVERSE_SCALE);
                
                MotorsDrive(left_spd, right_spd);
                break;
            }

            // When robot is not on line
            case STATE_LOST: {
                // If line is found again
                if(sensor_mask != 0) {
                    g_integral = 0;     // Reset integral on re-acquire
                    state = STATE_FOLLOWING;
                    break;
                }

                // Otherwise, robot is still lost
                LEDS(0x3F);             // Indicate lost state by turning on all LEDs

                if(g_last_error < 0)    // If line was just to the left, then spin left
                    MotorsDrive(-(int16_t)((uint8_t)(RECOVERY_SPEED / REVERSE_SCALE)), (int16_t)RECOVERY_SPEED);
                                        // Otherwise, line was just to the right and then spin right
                else                    // or if center, then spins right by convention
                    MotorsDrive((int16_t)RECOVERY_SPEED, -(int16_t)((uint8_t)(RECOVERY_SPEED / REVERSE_SCALE)));

                break;
            }

            // Else panic!
            default:
                MotorsStop();
                break;
        }
    }
}

// Compute weighted-average position error from sensor ADC readings
// Negative = line is left, Positive = line is right
int16_t PIDError(uint8_t sensor_mask) {
    int32_t weighted_sum = 0;
    uint8_t count = 0;          // Number of active sensors

    // Accumulate weighted position of each sensor that detects the line
    for(uint8_t i = 0; i < 6; i++) {
        if(sensor_mask & (1U << i)) {
            weighted_sum += (int32_t)SENSOR_WEIGHT[i];
            count++;
        }
    }

    // Hold last known error when line is lost
    if(count == 0)
        return g_last_error;    

    // Return weighted average
    return (int16_t)(weighted_sum / (int32_t)count);
}

// Reads a single analog channel (0-7)
// Returns 10-bit ADC result (0-1023), right-justified
uint16_t ADCRead(uint8_t channel) {
    // Select channel
    ADCON0 = (ADCON0 & 0b11000001) | ((uint8_t)(channel << 3) & 0b00111000);

    __delay_us(20);                 // Acquisition time

    ADCON0bits.GO_DONE = 1;         // Start conversion
    while(ADCON0bits.GO_DONE);      // Wait for conversion to finish

    // Right-justified result
    return ((uint16_t)(ADRESH << 8) | ADRESL);
}

// Drive both motors with signed speeds
// Positive = forward, negative = reverse, zero = brake
// Magnitude is clamped to PWM_DUTY_CAP
void MotorsDrive(int16_t left_speed, int16_t right_speed) {
    // Left motor
    if(left_speed > 0) {
        SetMotorDirection(MOTOR_LEFT, DIR_FORWARD);
        SetMotorSpeed(MOTOR_LEFT, (uint8_t)CLAMP(left_speed, 0, PWM_DUTY_CAP));
    } else if(left_speed < 0) {
        SetMotorDirection(MOTOR_LEFT, DIR_REVERSE);
        SetMotorSpeed(MOTOR_LEFT, (uint8_t)CLAMP(-left_speed, 0, PWM_DUTY_CAP));
    } else {
        SetMotorDirection(MOTOR_LEFT, DIR_BRAKE);
        SetMotorSpeed(MOTOR_LEFT, 0);
    }

    // Right motor
    if(right_speed > 0) {
        SetMotorDirection(MOTOR_RIGHT, DIR_FORWARD);
        SetMotorSpeed(MOTOR_RIGHT, (uint8_t)CLAMP(right_speed, 0, PWM_DUTY_CAP));
    } else if(right_speed < 0) {
        SetMotorDirection(MOTOR_RIGHT, DIR_REVERSE);
        SetMotorSpeed(MOTOR_RIGHT, (uint8_t)CLAMP(-right_speed, 0, PWM_DUTY_CAP));
    } else {
        SetMotorDirection(MOTOR_RIGHT, DIR_BRAKE);
        SetMotorSpeed(MOTOR_RIGHT, 0);
    }
}

// Set direction of an individual motor (independent of speed)
void SetMotorDirection(MotorID motor, MotorDir dir) {
    if (motor == MOTOR_LEFT){
        switch(dir) {
            case DIR_FORWARD: MOTOR_FORWARD(AIN1, AIN2); break;
            case DIR_REVERSE: MOTOR_REVERSE(AIN1, AIN2); break;
            case DIR_BRAKE:   MOTOR_BRAKE(AIN1, AIN2);   break;
            case DIR_COAST:
            default:          MOTOR_COAST(AIN1, AIN2);   break;
        }
    } else {
        switch(dir) {
            case DIR_FORWARD: MOTOR_FORWARD(BIN1, BIN2); break;
            case DIR_REVERSE: MOTOR_REVERSE(BIN1, BIN2); break;
            case DIR_BRAKE:   MOTOR_BRAKE(BIN1, BIN2);   break;
            case DIR_COAST:
            default:          MOTOR_COAST(BIN1, BIN2);   break;
        }
    }
}

// Set speed of an individual motor (independent of direction)
void SetMotorSpeed(MotorID motor, uint8_t speed) {
    uint8_t clamp = (speed > PWM_DUTY_CAP) ? (uint8_t)PWM_DUTY_CAP : speed;

    if (motor == MOTOR_LEFT)    CCPR1L = clamp;
    else                        CCPR2L = clamp;
}

// Brake both motors
void MotorsStop(void) {
    SetMotorDirection(MOTOR_LEFT,  DIR_BRAKE);
    SetMotorDirection(MOTOR_RIGHT, DIR_BRAKE);
    SetMotorSpeed(MOTOR_LEFT,  0);
    SetMotorSpeed(MOTOR_RIGHT, 0);
}

// Software delay supporting values > 255
void inline DelayMS(uint16_t ms) {
    while(ms--)
        __delay_ms(1);
}