/* Jedi/Sector One */

.text
#ifndef __linux__
.globl _screxfnt
#else
.globl screxfnt
#endif
	.align 4
#ifndef __linux__
_screxfnt:
#else
screxfnt:
#endif
	.include "inc/screxfnt.inc"
