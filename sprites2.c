/* Jedi/Sector One */

#include "ping.h"

#include "spr_dsp.h"

void sprite_normBool(unsigned char *where, const int deca)
{
#include "inc/normbool.inc"
}

void sprite_tinyBool(unsigned char *where, const int deca)
{
#include "inc/tinybool.inc"
}

void sprite_midBool(unsigned char *where, const int deca)
{
#include "inc/midbool.inc"
}

#if BIGBOOL_SUPPORT
void sprite_bigBool(unsigned char *where, const int deca)
{
#include "inc/bigbool.inc"
}
#endif

/*                                                                          */


#include "spr_load.h"

void load_normBool(register unsigned char *where, const ptrdiff_t offset)
{
#include "inc/normbool.inc"
}

void load_tinyBool(register unsigned char *where, const ptrdiff_t offset)
{
#include "inc/tinybool.inc"
}

void load_midBool(register unsigned char *where, const ptrdiff_t offset)
{
#include "inc/midbool.inc"
}

#if BIGBOOL_SUPPORT
void load_bigBool(register unsigned char *where, const ptrdiff_t offset)
{
#include "inc/bigbool.inc"
}
#endif
