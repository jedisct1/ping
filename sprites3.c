/* Jedi/Sector One */

#include "ping.h"

#include "spr_dsp.h"

void sprite_coeur1(unsigned char *where, const int deca)
{
#include "inc/coeur1.inc"
}

void sprite_coeur2(unsigned char *where, const int deca)
{
#include "inc/coeur2.inc"
}

void sprite_coeur3(unsigned char *where, const int deca)
{
#include "inc/coeur3.inc"
}

void sprite_coeur4(unsigned char *where, const int deca)
{
#include "inc/coeur4.inc"
}

void sprite_bisou1(unsigned char *where, const int deca)
{
#include "inc/bisou2.inc"
}

void sprite_bisou2(unsigned char *where, const int deca)
{
#include "inc/bisou1.inc"
}



/*                                                                          */



#include "spr_load.h"

void load_coeur1(register unsigned char *where, const ptrdiff_t offset)
{
#include "inc/coeur1.inc"
}

void load_coeur2(register unsigned char *where, const ptrdiff_t offset)
{
#include "inc/coeur2.inc"
}

void load_coeur3(register unsigned char *where, const ptrdiff_t offset)
{
#include "inc/coeur3.inc"
}

void load_coeur4(register unsigned char *where, const ptrdiff_t offset)
{
#include "inc/coeur4.inc"
}

void load_bisou1(register unsigned char *where, const ptrdiff_t offset)
{
#include "inc/bisou2.inc"
}

void load_bisou2(register unsigned char *where, const ptrdiff_t offset)
{
#include "inc/bisou1.inc"
}
