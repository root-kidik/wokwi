;hello.asm
;  turns on an LED which is connected to PB5 (digital out 13)

#define PORTB 0x18
#define DDRB 0x17

.global main

main:
	ldi r16,0b00100000
	out DDRB,r16
	out PORTB,r16
Start:
	rjmp Start