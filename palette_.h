/* Jedi/Sector One */

#ifndef PALETTE_DEFINED__
#define PALETTE_DEFINED__
static unsigned char pal[] = {
#if 0
    0, 0, 7, 63, 63, 63, 60, 53, 45, 58, 43, 28,
    55, 35, 13, 53, 27, 0, 44, 16, 0, 36, 8, 0,
    28, 2, 0, 20, 0, 0, 18, 4, 18, 10, 1, 10,
    13, 8, 41, 0, 0, 14, 63, 58, 41, 63, 51, 33,
    63, 41, 26, 63, 28, 18, 63, 12, 11, 50, 6, 5,
    37, 1, 1, 24, 0, 0
#else
#include "inc/pal.inc"
#endif
};

static unsigned char palcrew[] = {
#include "inc/palcrew.inc"
};
#endif
