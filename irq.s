/* Jedi/Sector One */

.text
.globl _pepsi
        .align 4
_pepsi:
        pushl %eax
	movb $32,%al
	outb %al,$32
	popl %eax
	iret

.text
.globl _cola
        .align 4
_cola:
        iret

