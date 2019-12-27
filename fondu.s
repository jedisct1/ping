/* Jedi/Sector One */

.text
#ifndef __linux__
.globl _fondu
#else
.globl fondu
#endif
	.align 4
#ifndef __linux__
_fondu:
#else
fondu:
#endif
	.include "inc/fondu.inc"
