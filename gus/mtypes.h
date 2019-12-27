#ifndef MTYPES_H
#define MTYPES_H

#ifdef DJGPP
#include <sys/nearptr.h>
#include <go32.h>
#include <dpmi.h>
#endif


/*
	MikMod atomic types:
	====================
*/

typedef char SBYTE;		/* has to be 1 byte signed */
typedef unsigned char UBYTE;	/* has to be 1 byte unsigned */
typedef short SWORD;		/* has to be 2 bytes signed */
typedef unsigned short UWORD;	/* has to be 2 bytes unsigned */
typedef long SLONG;		/* has to be 4 bytes signed */
typedef unsigned long ULONG;	/* has to be 4 bytes unsigned */
typedef int BOOL;		/* doesn't matter.. 0=FALSE, <>0 true */


#ifdef __WATCOMC__
#define inportb(x) inp(x)
#define outportb(x,y) outp(x,y)
#define inport(x) inpw(x)
#define outport(x,y) outpw(x,y)
#define disable() _disable()
#define enable() _enable()
#endif
#ifdef DJGPP
#define outport(x,y) outportw(x,y)
#define inport(x) inportw(x)
#ifndef enable
#define enable() asm("sti");
#define disable() asm("cli");
#endif
#endif

#endif
