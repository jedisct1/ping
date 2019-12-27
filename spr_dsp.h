/* Jedi/Sector One */

#define LOAD_PLANE(A)
#define LOAD_WRITEB(A,B)
#define LOAD_WRITEL(A,B)

#ifndef CHOUCROUTE_DEFINED__
#define CHOUCROUTE_DEFINED__
static const int choucroute[] = {
    WPLANE0, RPLANE0, WPLANE1, RPLANE1, WPLANE2, RPLANE2, WPLANE3, RPLANE3,
    WPLANE0, RPLANE0, WPLANE1, RPLANE1, WPLANE2, RPLANE2, WPLANE3, RPLANE3
};
#endif

#define INIT const int * const peinture = &choucroute[deca * 2];
#define PLANE(X) \
readPlane(peinture[X * 2 + 1]); writePlane(peinture[X * 2]); \
if (X + deca == 4) where++
#define SPRITEWRITEB(X, Y, Z) * (unsigned char *) \
(where + Y * SCREEN_WIDTH_IN_BYTES + X) = (unsigned char) Z
#define SPRITEWRITEW(X, Y, Z) * (unsigned short *) \
(where + Y * SCREEN_WIDTH_IN_BYTES + X) = (unsigned short) Z
#define SPRITEWRITEL(X, Y, Z) * (unsigned long *) \
(where + Y * SCREEN_WIDTH_IN_BYTES + X) = (unsigned long) Z
#define SPRITEANDL(X, Y, Z) { \
   unsigned long * const youpi = \
   (unsigned long * const) (where + Y * SCREEN_WIDTH_IN_BYTES + X); \
   *youpi &= (unsigned long) Z; \
}
#define SPRITEORL(X, Y, Z) { \
   unsigned long * const youpi = \
   (unsigned long * const) (where + Y * SCREEN_WIDTH_IN_BYTES + X); \
   *youpi |= (unsigned long) Z; \
}
#define EXTRA(X, Y)
