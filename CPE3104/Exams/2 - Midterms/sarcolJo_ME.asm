
; Sarcol, Joshua S

; High Level Implementation:
;   Wait until a button is pressed
;   If so, grab the state of the dip switches
;   Perform relevant arithmetic operation
;   Display result
;   Repeat forever

ORG 100H

.data
PORTA EQU 0A8H          ; 2 7-segment displays in BCD format
                        ; MSN => Tens digit
                        ; LSN => Ones digit
PORTB EQU 0AAH          ; 2 4-bit dip switches in Binary
                        ; MSN => Operand 1
                        ; LSN => Operand 2
PORTC EQU 0ACH          ; 4 push buttons
                        ; 0000_0001B => Division
                        ; 0000_0010B => Multiplication
                        ; 0000_0100B => Subtraction
                        ; 0000_1000B => Addition
COM_REG EQU 0AEH        ; Command Register
                        ; 1000_1011B (08BH)


UF_IND EQU 0CCH         ; Pattern if number is negative
OF_IND EQU 0DDH         ; Pattern if number is over 99

.code
; Set-up
    ; Program the 8255
    MOV DX, COM_REG
    MOV AL, 08BH
    OUT DX, AL
    
    ; Display 0 on the 7-segments
    MOV DX, PORTA
    MOV AL, 045H
    OUT DX, AL

main_loop:
; Wait until a button is pressed
    MOV DX, PORTC
    IN AL, DX
    
    TEST AL, 0FH        ; If zero
    JZ main_loop        ; Then back to main loop
    
    MOV CH, AL

; If so, grab the state of the dip switches
    MOV DX, PORTB
    IN AL, DX
    
    ; Separate the numbers into two separate registers
    MOV BX, AX
    AND AL, 0F0H
    MOV CL, 4
    SHR AL, CL          ; AL => First operand
    AND BL, 00FH        ; BL => Second operand
            
; Perform relevant arithmetic operation
    CMP CH, 00000001B
    JE div_arith
    
    CMP CH, 00000010B
    JE mul_arith
    
    CMP CH, 00000100B
    JE sub_arith
    
    CMP CH, 00001000B
    JE add_arith
    
    JMP main_loop

; Final arithmetic result is in AL    
div_arith:
    CMP BL, 0H
    JE div_by_zero
    
    MOV AH, 0
    DIV BL
    MOV AH, 0
    JMP disp_digits
    
mul_arith:
    MUL BL
    JMP disp_digits  
      
sub_arith:
    SUB AL, BL
    JMP disp_digits
    
add_arith:
    ADD AL, BL
    JMP disp_digits
    
; Display result
disp_digits:
    MOV DX, PORTA
    
    ; If result is negative (CF = 1), then display underflow
    JNC not_negative
        MOV AL, UF_IND
        OUT DX, AL
        JMP main_loop    
    not_negative:
    
    ; If result is over 99, then display overflow
    CMP AL, 99
    JNA not_overflow
    div_by_zero:
        MOV DX, PORTA
        MOV AL, OF_IND
        OUT DX, AL
        JMP main_loop        
    not_overflow:
    
    ; Otherwise display result normally
    ; Should be in BCD
    MOV AH, 0
    MOV BL, 10          ; AL => Tens digit      
    DIV BL              ; AH => Ones digit
    
    MOV CL, 4
    SHL AL, CL
    OR AL, AH
    
    OUT DX, AL
       

; Repeat forever
JMP main_loop






