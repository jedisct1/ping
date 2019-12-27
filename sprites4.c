/* Jedi/Sector One */

#include "ping.h"

#include "spr_dsp.h"

void sprite_bulle1(unsigned char *where, const int deca)
{
#include "inc/bulle1.inc"
}

void sprite_bulle2(unsigned char *where, const int deca)
{
#include "inc/bulle2.inc"
}

void sprite_bulle3(unsigned char *where, const int deca)
{
#include "inc/bulle3.inc"
}



/*                                                                          */



#include "spr_load.h"

void load_bulle1(register unsigned char *where, const ptrdiff_t offset)
{
#include "inc/bulle1.inc"
}

void load_bulle2(register unsigned char *where, const ptrdiff_t offset)
{
#include "inc/bulle2.inc"
}

void load_bulle3(register unsigned char *where, const ptrdiff_t offset)
{
#include "inc/bulle3.inc"
}
