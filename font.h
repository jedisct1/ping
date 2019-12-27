#ifndef DEFINE_FONT__
extern
#endif
const unsigned char font[]
#ifdef DEFINE_FONT__
    = {
# include "inc/font.inc"
}
#endif
;

#define ZERO_IN_FONT 26
#define RIGHTARROW_IN_FONT 47
#define LEFTARROW_IN_FONT 49
#define SPACE_IN_FONT 50
#define FONT_WIDTH 16
#define FONT_HEIGHT 16
