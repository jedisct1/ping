/* Jedi/Sector One */

.text
#ifndef __linux__
.globl _miniPing
#else
.globl miniPing
#endif
	.align 4
#ifndef __linux__
_miniPing:
#else
miniPing:
#endif
	.include "inc/miniping.inc"
