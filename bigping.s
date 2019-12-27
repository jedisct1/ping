/* Jedi/Sector One */

.text
#ifndef __linux__
.globl _bigPing
#else
.globl bigPing
#endif
	.align 4
#ifndef __linux__
_bigPing:
#else
bigPing:
#endif
	.include "inc/bigping.inc"
