; CPE 3104 - MICROPROCESSORS
; Group 4   Tue Thu 4:30 PM - 7:30 PM LBCEAC2 TC
; Sarcol, Joshua S      BS CpE - 3      2025/12/04
; PRE-FINAL EXAMINATION

; High Level Implementation
; Set-up
;   PORT5 8255 PPI
;   PORT6 8253 PIT
;   PORT7 8259 PIC
;   IV Tables
;   LCD initialization
; Foreground Loop
;   Display Current status (set/running/paused)
;   Display Time (minutes:seconds)
;
; When clock triggers
;   If not [started], then do nothing
;   Else, then retrigger clock and continue
;   If [running], decrement timer
;   Else do nothing   
;
; When keypad is pressed
;   If not [started] then
;       If number then set [minutes]
;       If '*' then [started] = 1 and [running] = 1, then start clock
;   Else do nothing
;
; When button is pressed
;   If not [started] then do nothing
;   Else toggle [running]


DATA    SEGMENT
        ORG 01000H
; Constants
    PORT5_COM_REG   EQU 06EH        ; 8255 Command Register
    PORT5_PROGRAM   EQU 089H        ; 10001 001 (89H)
    LCD_BUS         EQU 068H        ; LCD Data bus
    LCD_CNTRL       EQU 06AH        ; LCD Control lines
                                    ; ---E ---R
    LCD1            EQU 038H        ; Function Set
                                    ; 001 1 1 0 00 (38H)
    LCD2            EQU 00CH        ; Display ON/OFF
                                    ; 00001 1 0 0 (0CH)
    LCD3            EQU 001H        ; Clear Display
                                    ; 0000 0001 (01H)
    LCD4            EQU 018H        ; Cursor/Display Shift
                                    ; 0001 1 0 00 (18H)
    LINE2           EQU 0C0H        ; LCD DDRAM addresses
    LINE3           EQU 094H                                                                                                                                       
    KPD_DATA        EQU 06CH        ; Keypad Data output
    
    PORT6_COM_REG   EQU 076H        ; 8253 Command Register
    PORT6_PROGRAM   EQU 038H        ; 00 11 100 0 (38H)
    CLOCK_BUS       EQU 070H        ; Clk0
    CLOCK_LSB       EQU 0F4H        ; 2000Hz (07D0H)
    CLOCK_MSB       EQU 001H        ; 500Hz  (01F4H)
    
    PIC0            EQU 078H        ; 01 111 00 0 (78H)
    PIC1            EQU 07AH        ; 01 111 01 0 (7AH)
    ICW1            EQU 013H        ; 0001 0 0 1 1 (13H)
    ICW2            EQU 080H        ; 10000 xxx (80H - 87H)
                                    ; So start of IVT is 80H*4 + 200H
    ICW4            EQU 003H        ; 000 0 00 1 1 (03H)
    OCW1            EQU 0F8H        ; 1111 1000 (F8H)
    
    DELAY_FOR       EQU 00300H      ; Artificial delay                               
    
; Variables
    ; LCD Default text
    SET_TEXT    DB "      SET TIMER     "
    RUN_TEXT    DB "   TIME IS TICKING  "
    PAUSE_TEXT  DB "   TIME IS PAUSED   "
    ZERO_TIMER  DB "        00:00       "
                      
    ; State variables
    ISSTARTED   DB 0                ; 1 when * is pressed
                                    ; 0 when finished
    ISRUNNING   DB 0                ; 1 when not paused
                                    ; 0 when button is pressed
                                    
    ; Actual variables that hold the time
    MINUTES     DB 0
    SECONDS     DB 0                                    
                                                                                     

; Data tables
KEYPRESS    DB 01H, 02H, 03H, 0FH
            DB 04H, 05H, 06H, 0FH
            DB 07H, 08H, 09H, 0FH
            DB 0AH, 0FH, 0FH, 0FH        
    
DATA    ENDS

STACK   SEGMENT PARA STACK
    DW 64 DUP(?)
TOS DW ?
STACK   ENDS


; When clock triggers
HANDLE0 SEGMENT
ISR0    PROC FAR
        ORG 02000H
        ASSUME CS:HANDLE0, DS:DATA, SS:STACK
CLI
PUSHF
PUSH AX
PUSH BX
PUSH CX
PUSH DX
PUSH SI

;   If not [started], then do nothing
    CMP ISSTARTED, 1
    JNE end_isr0
    
;   Else, then retrigger clock and continue
    MOV DX, CLOCK_BUS
    MOV AL, CLOCK_LSB
    OUT DX, AL
    
    MOV AL, CLOCK_MSB
    OUT DX, AL

;   If [running], decrement timer
    CMP ISRUNNING, 1
    JNE end_isr0
    
    CMP SECONDS, 0
    JNE second_decrement
    ; If x:00 then
        CMP MINUTES, 0
        JNE minute_decrement
        ; If 0:00 then end timer        
        MOV ISRUNNING, 0
        MOV ISSTARTED, 0
        JMP end_isr0
            
    second_decrement:
        DEC SECONDS
        JMP end_isr0 
    
    minute_decrement:
        DEC MINUTES
        MOV SECONDS, 59    

;   Else do nothing
    end_isr0:
POP SI
POP DX
POP CX
POP BX
POP AX
POPF    
IRET
ISR0    ENDP
HANDLE0 ENDS

; When keypad is pressed
HANDLE1 SEGMENT
ISR1    PROC FAR
        ORG 03000H
        ASSUME CS:HANDLE1, DS:DATA, SS:STACK
CLI
PUSHF
PUSH AX
PUSH BX
PUSH CX
PUSH DX
PUSH SI
;   If not [started] then
    CMP ISSTARTED, 0
    JNE end_isr1
    
    MOV DX, KPD_DATA
    IN AL, DX
    
    MOV SI, OFFSET KEYPRESS
    XOR BX, BX
    MOV BL, AL
    
    XOR AX, AX
    MOV AL, [BX + SI]        
    
;       If number then set [minutes] 
    CMP AL, 09H
    JBE minute_set
        
;       If '*' then [started] = 1 and [running] = 1, then start clock
    CMP AL, 0AH
    JE start_clock

;   Else do nothing    
    JMP end_isr1

    
    minute_set:
        MOV MINUTES, AL   
    JMP end_isr1
    
    start_clock:
        MOV ISSTARTED, 1
        MOV ISRUNNING, 1
        
    MOV DX, CLOCK_BUS
    MOV AL, CLOCK_LSB
    OUT DX, AL
    
    MOV AL, CLOCK_MSB
    OUT DX, AL        


    end_isr1:
POP SI
POP DX
POP CX
POP BX
POP AX
POPF    
IRET
ISR1    ENDP
HANDLE1 ENDS

; When button is pressed
HANDLE2 SEGMENT
ISR2    PROC FAR
        ORG 04000H
        ASSUME CS:HANDLE2, DS:DATA, SS:STACK
CLI
PUSHF
PUSH AX
PUSH BX
PUSH CX
PUSH DX
PUSH SI
;   If not [started] then do nothing
;    CMP ISSTARTED, 1
;    JNE end_isr2  

;   Else toggle [running]
    NOT [ISRUNNING]
    
    MOV DX, CLOCK_BUS
    MOV AL, CLOCK_LSB
    OUT DX, AL
    
    MOV AL, CLOCK_MSB
    OUT DX, AL    

    end_isr2:
POP SI
POP DX
POP CX
POP BX
POP AX
POPF    
IRET
ISR2    ENDP
HANDLE2 ENDS

CODE    SEGMENT PUBLIC 'CODE'
        ORG 05000H
        ASSUME CS:CODE, DS:DATA, SS:STACK
START:
; Set-up
    CLI                             ; Disable interrupts
    
;   PORT5 8255 PPI
    MOV DX, PORT5_COM_REG
    MOV AL, PORT5_PROGRAM
    OUT DX, AL
    
;   PORT6 8253 PIT
    MOV DX, PORT6_COM_REG
    MOV AL, PORT6_PROGRAM
    OUT DX, AL
    
;   PORT7 8259 PIC
    MOV DX, PIC0
    MOV AL, ICW1
    OUT DX, AL
    
    MOV DX, PIC1
    MOV AL, ICW2
    OUT DX, AL
    
    MOV AL, ICW4
    OUT DX, AL
    
    MOV AL, OCW1
    OUT DX, AL

;   IV Tables
    XOR AX, AX
    MOV ES, AX
    
    MOV AX, OFFSET ISR0
    MOV [ES:200H], AX
    MOV AX, SEG ISR0
    MOV [ES:202H], AX
    
    MOV AX, OFFSET ISR1
    MOV [ES:204H], AX
    MOV AX, SEG ISR1
    MOV [ES:206H], AX    

    MOV AX, OFFSET ISR2
    MOV [ES:208H], AX
    MOV AX, SEG ISR2
    MOV [ES:20AH], AX
        
;   LCD initialization
    MOV AL, LCD1
    CALL LCD_INST
    
    MOV AL, LCD2
    CALL LCD_INST
    
    MOV AL, LCD3
    CALL LCD_INST
    
    MOV AL, LCD4
    CALL LCD_INST
    
    MOV SI, OFFSET SET_TEXT
    MOV DI, LINE2
    CALL LCD_LINE
    
    MOV SI, OFFSET ZERO_TIMER
    MOV DI, LINE3
    CALL  LCD_LINE

    STI                             ; Enable interrupts
    
; Foreground Loop
foreground_loop:
;   Display Current status (set/running/paused)

    MOV DI, LINE2

    CMP ISSTARTED, 1
    JNE not_started
        ; started:
            CMP ISRUNNING, 1
            JNE not_running
            ; running:
                MOV SI, OFFSET RUN_TEXT
                JMP header_end
            not_running:
                MOV SI, OFFSET PAUSE_TEXT
                JMP header_end    
        not_started:    
                MOV SI, OFFSET SET_TEXT
    
    header_end:
    CALL LCD_LINE
    
;   Display Time (minutes:seconds)
    MOV AL, LINE3 + 9
    CALL LCD_INST
    
    MOV AL, [MINUTES]
    ADD AL, '0'
    CALL LCD_DATA
    
    MOV AL, ':'
    CALL LCD_DATA
    
    XOR AX, AX
    MOV AL, [SECONDS]
    MOV BX, 10                      ; AH = Ones
    DIV BL                          ; AL = Tens
    
    ADD AL, '0'
    CALL LCD_DATA
    
    MOV AL, AH
    ADD AL, '0'
    CALL LCD_DATA
    
JMP foreground_loop

HLT

; LCD Instruction byte helper routine
; AL - Instruction to be sent
LCD_INST:
PUSH AX
PUSH DX
    MOV DX, LCD_BUS
    OUT DX, AL
    
    MOV DX, LCD_CNTRL
    MOV AL, 010H                    ; E = 1, RS = 0
    OUT DX, AL          
    
    CALL DELAY
    
    MOV AL, 000H                    ; E = 1, RS = 0
    OUT DX, AL          
POP DX
POP AX
RET

; LCD Data byte helper routine
; AL - Data to be sent
LCD_DATA:
PUSH AX
PUSH DX
    MOV DX, LCD_BUS
    OUT DX, AL
    
    MOV DX, LCD_CNTRL
    MOV AL, 011H                    ; E = 1, RS = 1
    OUT DX, AL          
    
    CALL DELAY
    
    MOV AL, 001H                    ; E = 1, RS = 1
    OUT DX, AL          
POP DX
POP AX
RET

; LCD Line display helper routine
; SI - Address of string (use OFFSET)
; DI - LCD DDRAM address (lower nibble)
LCD_LINE:
PUSH AX
PUSH CX
    MOV AX, DI
    CALL LCD_INST
    
    MOV CX, 20
    char_display:
        MOV AL, [SI]
        CALL LCD_DATA
        
        INC SI        
    LOOP char_display     
POP CX
POP AX
RET


; Artificial delay
DELAY:
PUSH CX
    MOV CX, DELAY_FOR
    _delay_in:
    NOP
    LOOP _delay_in 
POP CX
RET
CODE    ENDS
        END START

  
  