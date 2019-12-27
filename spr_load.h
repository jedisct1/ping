/* Jedi/Sector One */

#undef INIT
#define INIT \
unsigned char * const screenSave_ = screenSave + offset; \
register unsigned char *buffer

#undef LOAD_PLANE
#define LOAD_PLANE(X) { \
   if (X == 0) writePlane(WPLANE0); \
   else if (X == 1) writePlane(WPLANE1); \
   else if (X == 2) writePlane(WPLANE2); \
   else writePlane(WPLANE3); \
   buffer = screenSave_ + SCREEN_LENGTH_IN_BYTES * (X); \
}
#undef PLANE
#define PLANE(X)
#undef SPRITEWRITEB
#define SPRITEWRITEB(X, Y, Z)
#undef SPRITEWRITEW
#define SPRITEWRITEW(X, Y, Z)
#undef SPRITEWRITEL
#define SPRITEWRITEL(X, Y, Z)
#undef SPRITEANDL
#define SPRITEANDL(X, Y, Z)
#undef SPRITEORL
#define SPRITEORL(X, Y, Z)

#undef LOAD_WRITEB
#define LOAD_WRITEB(X, Y) \
* (unsigned char *) (where + Y * SCREEN_WIDTH_IN_BYTES + X) = \
* (unsigned char *) (buffer + Y * SCREEN_WIDTH_IN_BYTES + X);

#undef LOAD_WRITEL
#define LOAD_WRITEL(X, Y) \
* (unsigned long *) (where + Y * SCREEN_WIDTH_IN_BYTES + X) = \
* (unsigned long *) (buffer + Y * SCREEN_WIDTH_IN_BYTES + X);
