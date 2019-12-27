/* Jedi/Sector One */

#include "ping.h"

#include "spr_dsp.h"

void sprite_normRaq(unsigned char *where, const int deca)
{
#include "inc/normraq.inc"
}

void sprite_bigRaq(unsigned char *where, const int deca)
{
#include "inc/bigraq.inc"
}

void sprite_horiRaq(unsigned char *where, const int deca)
{
#include "inc/horiraq.inc"
}



#if BONI_SUPPORT

void sprite_bonus0(unsigned char *where, const int deca)
{
#include "inc/bonus0.inc"
}

void sprite_bonus1(unsigned char *where, const int deca)
{
#include "inc/bonus1.inc"
}

void sprite_bonus2(unsigned char *where, const int deca)
{
#include "inc/bonus2.inc"
}

void sprite_bonus3(unsigned char *where, const int deca)
{
#include "inc/bonus3.inc"
}

#if ALLBONI_SUPPORT
void sprite_bonus4(unsigned char *where, const int deca)
{
#include "inc/bonus4.inc"
}

void sprite_bonus5(unsigned char *where, const int deca)
{
#include "inc/bonus5.inc"
}
#endif

void sprite_bonus6(unsigned char *where, const int deca)
{
#include "inc/bonus6.inc"
}

void sprite_bonus7(unsigned char *where, const int deca)
{
#include "inc/bonus7.inc"
}

#if ALLBONI_SUPPORT
void sprite_bonus8(unsigned char *where, const int deca)
{
#include "inc/bonus8.inc"
}
#endif

void sprite_bonus9(unsigned char *where, const int deca)
{
#include "inc/bonus9.inc"
}

void sprite_bonus10(unsigned char *where, const int deca)
{
#include "inc/bonus10.inc"
}

void sprite_bonus11(unsigned char *where, const int deca)
{
#include "inc/bonus11.inc"
}

void sprite_bonus12(unsigned char *where, const int deca)
{
#include "inc/bonus12.inc"
}

void sprite_bonus13(unsigned char *where, const int deca)
{
#include "inc/bonus13.inc"
}

void sprite_bonusback(unsigned char *where, const int deca)
{
#include "inc/bonusbck.inc"
}




void sprite_rond0(unsigned char *where, const int deca)
{
#include "inc/rond0.inc"
}
void sprite_rond1(unsigned char *where, const int deca)
{
#include "inc/rond1.inc"
}
void sprite_rond2(unsigned char *where, const int deca)
{
#include "inc/rond2.inc"
}
void sprite_rond3(unsigned char *where, const int deca)
{
#include "inc/rond3.inc"
}
void sprite_rond4(unsigned char *where, const int deca)
{
#include "inc/rond4.inc"
}
void sprite_rond5(unsigned char *where, const int deca)
{
#include "inc/rond5.inc"
}
void sprite_rond6(unsigned char *where, const int deca)
{
#include "inc/rond6.inc"
}
void sprite_rond7(unsigned char *where, const int deca)
{
#include "inc/rond7.inc"
}
void sprite_rond8(unsigned char *where, const int deca)
{
#include "inc/rond8.inc"
}
void sprite_rond9(unsigned char *where, const int deca)
{
#include "inc/rond9.inc"
}
void sprite_rond10(unsigned char *where, const int deca)
{
#include "inc/rond10.inc"
}
void sprite_rond11(unsigned char *where, const int deca)
{
#include "inc/rond11.inc"
}
void sprite_rond12(unsigned char *where, const int deca)
{
#include "inc/rond12.inc"
}
void sprite_rond13(unsigned char *where, const int deca)
{
#include "inc/rond13.inc"
}
void sprite_rond14(unsigned char *where, const int deca)
{
#include "inc/rond14.inc"
}
void sprite_rond15(unsigned char *where, const int deca)
{
#include "inc/rond15.inc"
}
void sprite_rond16(unsigned char *where, const int deca)
{
#include "inc/rond16.inc"
}
void sprite_rond17(unsigned char *where, const int deca)
{
#include "inc/rond17.inc"
}
void sprite_rond18(unsigned char *where, const int deca)
{
#include "inc/rond18.inc"
}
void sprite_rond19(unsigned char *where, const int deca)
{
#include "inc/rond19.inc"
}
void sprite_rond20(unsigned char *where, const int deca)
{
#include "inc/rond20.inc"
}
void sprite_rond21(unsigned char *where, const int deca)
{
#include "inc/rond21.inc"
}
void sprite_rond22(unsigned char *where, const int deca)
{
#include "inc/rond22.inc"
}
void sprite_rond23(unsigned char *where, const int deca)
{
#include "inc/rond23.inc"
}
void sprite_rond24(unsigned char *where, const int deca)
{
#include "inc/rond24.inc"
}
void sprite_rond25(unsigned char *where, const int deca)
{
#include "inc/rond25.inc"
}
void sprite_rond26(unsigned char *where, const int deca)
{
#include "inc/rond26.inc"
}
void sprite_rond27(unsigned char *where, const int deca)
{
#include "inc/rond27.inc"
}
void sprite_rond28(unsigned char *where, const int deca)
{
#include "inc/rond28.inc"
}
void sprite_rond29(unsigned char *where, const int deca)
{
#include "inc/rond29.inc"
}
void sprite_rond30(unsigned char *where, const int deca)
{
#include "inc/rond30.inc"
}
void sprite_rond31(unsigned char *where, const int deca)
{
#include "inc/rond31.inc"
}

#endif



/*                                                                          */



#include "spr_load.h"

void load_normRaq(register unsigned char *where, const ptrdiff_t offset)
{
#include "inc/normraq.inc"
}

void load_bigRaq(register unsigned char *where, const ptrdiff_t offset)
{
#include "inc/bigraq.inc"
}

void load_horiRaq(register unsigned char *where, const ptrdiff_t offset)
{
#include "inc/horiraq.inc"
}




#if BONI_SUPPORT

void load_bonus0(register unsigned char *where, const ptrdiff_t offset)
{
#include "inc/bonus0.inc"
}

void load_bonus1(register unsigned char *where, const ptrdiff_t offset)
{
#include "inc/bonus1.inc"
}

void load_bonus2(register unsigned char *where, const ptrdiff_t offset)
{
#include "inc/bonus2.inc"
}

void load_bonus3(register unsigned char *where, const ptrdiff_t offset)
{
#include "inc/bonus3.inc"
}

#if ALLBONI_SUPPORT
void load_bonus4(register unsigned char *where, const ptrdiff_t offset)
{
#include "inc/bonus4.inc"
}

void load_bonus5(register unsigned char *where, const ptrdiff_t offset)
{
#include "inc/bonus5.inc"
}
#endif

void load_bonus6(register unsigned char *where, const ptrdiff_t offset)
{
#include "inc/bonus6.inc"
}

void load_bonus7(register unsigned char *where, const ptrdiff_t offset)
{
#include "inc/bonus7.inc"
}

#if ALLBONI_SUPPORT
void load_bonus8(register unsigned char *where, const ptrdiff_t offset)
{
#include "inc/bonus8.inc"
}
#endif
void load_bonus9(register unsigned char *where, const ptrdiff_t offset)
{
#include "inc/bonus9.inc"
}

void load_bonus10(register unsigned char *where, const ptrdiff_t offset)
{
#include "inc/bonus10.inc"
}

void load_bonus11(register unsigned char *where, const ptrdiff_t offset)
{
#include "inc/bonus11.inc"
}

void load_bonus12(register unsigned char *where, const ptrdiff_t offset)
{
#include "inc/bonus12.inc"
}

void load_bonus13(register unsigned char *where, const ptrdiff_t offset)
{
#include "inc/bonus13.inc"
}

void load_bonusback(register unsigned char *where, const ptrdiff_t offset)
{
#include "inc/bonusbck.inc"
}

void load_rondback(register unsigned char *where, const ptrdiff_t offset)
{
#include "inc/rond0.inc"
}

#endif
