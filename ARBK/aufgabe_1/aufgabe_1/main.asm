;
; aufgabe_1.asm
;
; Created: 24.10.2022 18:40:08
; Author : Raoul Duke
;

;.include "m8def.inc"

.org 0x000

start:
	ldi r16 , LOW(RAMEND) ; LOW-Byte highest RAM Adress
	out SPL, r16
	ldi r16, HIGH(RAMEND) ; HIGH-Byte highest RAM Adress
	out SPH, r16

	; load R17 with value for BREQ (Branch if equal s.45)
	ldi r17, 0b00000000

	; set Data Direction Registers
	ldi r16, 0b11111111
	out DDRD, r16

	ldi r16, 0b00000011
	out DDRB, r16

main:
	
	; activates the fist led
	ldi r16, 0b00000001
	out PORTD, r16
	rcall delay

loopa:	
	lsl r16 ; logical shift left -> wird mit 0 aufgefüllt von rechts
	out PORTD, r16
	rcall delay
	cp r16,r17 ; compares to registers and branches if they are equal
	breq equal ; branch equal
	rjmp loopa ; when not equl jump back to loop
											
equal:
	ldi r16, 0b0000001
	out PORTB, r16
	rcall delay
	lsl r16
	out PORTB, r16
	rcall delay
	lsr r16
	out PORTB, r16
	rcall delay
	lsr r16
	out PORTB, r16

	ldi r16, 0b10000000
	out PORTD, r16
	rcall delay

loopb:
	lsr r16
	out PORTD, r16
	rcall delay
	cp r16, r17
	breq end
	rjmp loopb

end:
	rjmp main ; returns to start to create endless loop

delay:
	ldi  r18, 11
    ldi  r19, 38
    ldi  r20, 94
L1: dec  r20
    brne L1
    dec  r19
    brne L1
    dec  r18
    brne L1
    rjmp PC+1
	ret