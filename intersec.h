/* Jedi/Sector One */

/* This computes if two areas intersect with each other. The macro was needed
* because GCC 2.7.2 was not able to optimize properly the inline statement.
* I also tried compound statements and the __attribute__ ((__const__)) feature,
* but noppe, GCC made a basic inlining and test the return value from the
* stack just after setting it. This is a tiny cycle loosage, but I can't stand
* such a stupid loosage. My conclusion is that integrating an inlined function
* in a test is a bad idea if the stack is involved due to a default of
* registers, as the current release of GCC is not able to optimize the link
* between the inlined function and the caller.
* I left the intersect() function as it can always be useful if the arguments
* aren't simple lvalues, but this is a general rule for any macro. If just the
* macro is used, the function won't be linked, so there will be no stupid
* space loosage.
* 
* BUT ... WHAT ARE YOU DOING HERE ? Go ahead sucker, don't try to rip this
* piece of source code ! RIPPING IS LAME ! Learn by yourself and forget code
* ripping, libraries and so on, it's so LAME, LAME, LAME !             - Jedi.
*/

#define INTERSECT(x1, y1, x2, y2, X1, Y1, X2, Y2) \
((((((X1) >= (x1) || (X2) >= (x1)) && ((X1) <= (x2) || (X2) <= (x2)     ) && \
(   ((Y1) >= (y1) && (Y1) <= (y2)) || ((Y2) >= (y1) && (Y2) <= (y2)))   ) || \
(   ((Y1) >= (y1) || (Y2) >= (y1)) && ((Y1) <= (y2) || (Y2) <= (y2)     ) && \
(   ((X1) >= (x1) && (X1) <= (x2)) || ((X2) >= (x1) && (X2) <= (x2))))))) || 0

extern __inline__ int intersect(const int x1, const int y1,
				const int x2, const int y2,
				const int X1, const int Y1,
				const int X2, const int Y2)
{
    return INTERSECT(x1, y1, x2, y2, X1, Y1, X2, Y2) ? : 0;
}
