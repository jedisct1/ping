/* Jedi/Sector One */

.text
#ifndef __linux__
.globl _texture1
#else
.globl texture1
#endif
	.align 4
#ifndef __linux__	
_texture1:
#else
texture1:
#endif
	.include "inc/back1.inc"
