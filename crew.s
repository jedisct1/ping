/* Jedi/Sector One */

.text
#ifndef __linux__
.globl _crew1
#else
.globl crew1
#endif
	.align 4
#ifndef __linux__
_crew1:
#else
crew1:
#endif
	.include "inc/crew1.inc"

#ifndef __linux__
.globl _crew2
#else
.globl crew2
#endif
	.align 4
#ifndef __linux__	
_crew2:
#else
crew2:
#endif
	.include "inc/crew2.inc"
