RRISC
=====

Registers:
4 general purposes available: R0, R1, R2, R3
1 special register: PC (not directly accesible)

Constant Values:
Use the character "V" followed by a natural number (e.g. V13)

Instructions:
nop	(no args)	Do nothing this cycle
00			PC += 1

halt	(no args)	Stop the processor by keeping PC the same
01			(do nothing)

memset	r1, r2, v1	Set r2+v1 to r1
02	4b  4b  8b	PC += 2

memld	r1, r2, v1	Set r1 to r2+v1
03	4b  4b  8b	PC += 2

regset	v1, r1, i4	Set r1 to v1
04	8b  4b	4b	PC += 2

add	r1, r2		Set r2 to r1+r2
05	4b  4b		PC += 1

sub	r1, r2		Set r2 to r1-r2
06	4b  4b		PC += 1

jmp	v1		Set PC to v1
07	8b		PC += 1

jz	r1, i4, v1	If r1 = 0 then set PC to v1
08	4b  4b  8b	PC += 2

jp	r1, i4, v1	If r1 > 0 then set PC to v1
09	4b  4b  8b	PC += 2

Legend:
vX is a value with index X
rX is a register with index X
iX is for padding, ignore X bits
