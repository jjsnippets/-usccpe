// CPE 3201 - EMBEDDED SYSTEMS
// Group 4      TTh 7:30 AM - 10:30 AM LB 285 TC
// Cabatas, Art Louise; Cagasan, Mar Joseph; Lao, Karl Vincent; Sarcol, Joshua      BS CpE - 3      2026/05/14
// Pre-Final Examination (CO2)

// Modified from the submission

// Requirements:
// - Use a keypad without a decoder
// - Use a potentiometer as analog input attached to MCUa
// - Display the following information to an LCD attached to MCUb
//   - Analog reading (0 - 5V)
//   - Frequency value is obtained from the previous value rounded up
//   - Count rate is determined from the previous value
// - Pressing '*' will send information from MCUa to MCUb
// - Pressing '#' will pause/resume counting

// Microcontroler files
#include <xc.h>
#include <pic16f877a.h>

// Configuration bits
#pragma config FOSC = XT
#pragma config WDTE = OFF
#pragma config PWRTE = ON
#pragma config BOREN = ON
#pragma config LVP = OFF
#pragma config CPD = OFF
#pragma config WRT = OFF
#pragma config CP = OFF

#define _XTAL_FREQ      4000000UL
#define MAXOVERFLOW     30

void interrupt ISR();
void initLCD();
void instCtrl(unsigned char INST);
void dataCtrl(unsigned char DATA);
void inline dataStr(const char* string);

typedef enum LINES {
    LINE1 = 0x80,
    LINE2 = 0xC0,
    LINE3 = 0x94,
    LINE4 = 0xD4
} LINES;

unsigned char receiveData = 25;
unsigned char readyData = 25;
unsigned char overflowCount = 0;
unsigned char countDisp = 0;

void main(){
    // GPIO set-up
    TRISB = 0x00;               // PORTB as output
    TRISD = 0x00;               // PORTD as output

    // USART Asynchronous Reception
    SPEN = 1;                   // Serial port enable
    SYNC = 0;                   // Asynchronous mode
    BRGH = 1;                   // High speed
    SPBRG = 0x19;               // 9.6Kbaud at 4MH; 0.16% error
    RX9 = 0;                    // 8-bit reception
    RCIE = 1;                   // Enable USART interrupts

    // Timer0
    PS2 = 1; PS1 = 1; PS0 = 1;  // 1:256 Prescaler
    PSA = 0;                    // Presacler to TMR0
    T0CS = 0;                   // Internal instruction clock cycle
    T0IF = 0;                   // Clear flag
    T0IE = 1;                   // Enable TMR0 interrupt

    initLCD();
    instCtrl(LINE1);                // "Voltage: "
    dataStr("Voltage: x.x ");
    instCtrl(LINE2);                // "Frequency: "
    dataStr("Frequency: x ");
    instCtrl(LINE3);                // "Count: "
    dataStr("Count: xx ");

    // Foreground routine
    PEIE = 1;                   // Enable peripheral interrupts
    GIE = 1;                    // Enable all interrupts
    CREN = 1;                   // Start of continuous reception
    while(1) {
        unsigned char ones, deci;

        if(receiveData == 99)       T0IE = 0;   // Pause timer signal
        else if(receiveData == 88)  T0IE = 1;   // Resume timer signal
        else         readyData = receiveData;   // Voltage reading

        // Display Voltage reading
        ones = readyData / 10;           // BCD format
        deci = readyData % 10;

        instCtrl(LINE1 + 9);
        dataCtrl(ones + '0');
        dataCtrl('.');
        dataCtrl(deci + '0');

        // Display Frequency reading
        unsigned char freqDisp = ones;
        if(deci) freqDisp++;

        instCtrl(LINE2 + 11);
        dataCtrl(freqDisp + '0');

        // Display Count reading
        unsigned char safeDiv = (freqDisp == 0) ? 1 : freqDisp;
        if((overflowCount > (MAXOVERFLOW / safeDiv)) && freqDisp){
            countDisp++;        // higher values, faster rate
            if(countDisp > 60)  countDisp = 0;
            overflowCount = 0;
        }
        
        ones = countDisp / 10;
        deci = countDisp % 10;

        instCtrl(LINE3 + 7);
        dataCtrl(ones + '0');
        dataCtrl(deci + '0');
    }
}

void interrupt ISR(){
    if(RCIE && RCIF) {          // When RXREG is full
        receiveData = RCREG;    // Then accept data

    } else if(T0IE && T0IF){    // When Timer0 overflows
        T0IF = 0;
        overflowCount++;        // Then increment overflow counter
    }
}

// Helper function to initialize the LCD
void initLCD(){
    __delay_ms(15);     // ~15ms start-up time
    
    instCtrl(0x38);     // 0011 1000 0x38
                        // 001? ??xx Function set
                        // ---1 ---- 8-bit data transfer
                        // ---- 1--- Dual line display
                        // ---- -0-- 5x7 font size
    
    instCtrl(0x08);     // 0000 1000 0x08
                        // 0000 1??? Display ON/OFF
                        // ---- -0-- Entire display off
                        // ---- --0- Cursor off
                        // ---- ---0 Cursor blinking off
    
    instCtrl(0x01);     // 0000 0001 0x01
                        // 0000 0001 Clear display
    
    instCtrl(0x06);     // 0000 0110 0x06
                        // 0000 01?? Entry mode set
                        // ---- --1- Increment / Move right
                        // ---- ---0 No shifting

    instCtrl(0x0E);     // 0000 1110 0x0E
                        // 0000 1??? Display ON/OFF
                        // ---- -1-- Entire display on
                        // ---- --1- Cursor on
                        // ---- ---0 Cursor blinking off 
}

// Helper function to send an instruction byte to LCD
void instCtrl(unsigned char INST){
    PORTB = INST;       //          Send to LCD
    PORTDbits.RD0 = 0;  // RS = 0   Instruction byte
    PORTDbits.RD1 = 1;  // E = 1    Enable
    __delay_ms(15);     //          Delay
    PORTDbits.RD1 = 0;  // E = 0    Disable
}

// Helper function to send a data byte to LCD
void dataCtrl(unsigned char DATA){
    PORTB = DATA;       //          Send to LCD
    PORTDbits.RD0 = 1;  // RS = 1   Data byte
    PORTDbits.RD1 = 1;  // E = 1    Enable
    __delay_ms(15);     //          Delay
    PORTDbits.RD1 = 0;  // E = 0    Disable
}

// Displays a string of text to the LCD (no wrap-around logic)
void inline dataStr(const char* string) {
    for(int i = 0; string[i] != '\0'; i++)
        dataCtrl(string[i]);
}