#define DEFINE_SOUND_POINTERS__

#include <stdlib.h>
#include <stdio.h>
#include "rgo.h"
#include "sound/sound.h"
#ifndef __linux__
# include "sb/sb.h"
# include "gus/gus.h"
#else
# include "mikfx/mikfx.h"
#endif

#define POPOP(A) sound_##A = gus_##A
#define ROBERT(A) sound_##A = sb_##A
#define SILENCE(A) sound_##A = no_sound;
#define SILENCE2(A) sound_##A = no_sound2;

static void no_sound(void)
{

}

static void no_sound2(const int l, const int r)
{
    (void) l;
    (void) r;
}

Conquete sound_select_card(void)
{
#ifndef __linux__
#if 0
    puts("\n"
	 "-=)> BIDAS SOUND SYSTEM 1.0 - (C)oderite Jedi/Sector One <(=-"
	 "\n"
	 "   .:.     Because MIDAS is great but ripping suxx     .:.\n");
#endif
    if (gus_init() == 0) {
	POPOP(bye);
	POPOP(boing);
	POPOP(frappe);
	POPOP(debut_match);
	POPOP(engagement);
	POPOP(clapclap);
	POPOP(avant_engagement);
	POPOP(get_bonus);
	POPOP(got_bonus);
	POPOP(end_bonus);
	POPOP(alea);
	POPOP(bfork);
	POPOP(descotche);
	POPOP(bip);
	POPOP(glue);
	POPOP(lazer);
	POPOP(softzak);
	POPOP(endmatch);

	return MAY_DISABLE_INTERRUPTS;
    } else if (sb_init() == 0) {
	ROBERT(bye);
	ROBERT(boing);
	ROBERT(frappe);
	ROBERT(debut_match);
	ROBERT(engagement);
	ROBERT(clapclap);
	ROBERT(avant_engagement);
	ROBERT(get_bonus);
	ROBERT(got_bonus);
	ROBERT(end_bonus);
	ROBERT(alea);
	ROBERT(bfork);
	ROBERT(descotche);
	ROBERT(bip);
	ROBERT(glue);
	ROBERT(lazer);
	ROBERT(softzak);
	ROBERT(endmatch);

	return CANT_DISABLE_INTERRUPTS;
    }
#endif

#ifdef __linux__
# define DAISY(A) sound_##A = mikfx_##A
    if (mikfx_init() == 0) {
	DAISY(bye);
	DAISY(boing);
	DAISY(frappe);
	DAISY(debut_match);
	DAISY(engagement);
	DAISY(clapclap);
	DAISY(avant_engagement);
	DAISY(get_bonus);
	DAISY(got_bonus);
	DAISY(end_bonus);
	DAISY(alea);
	DAISY(bfork);
	DAISY(descotche);
	DAISY(bip);
	DAISY(glue);
	DAISY(lazer);
	DAISY(softzak);
	DAISY(endmatch);

	return CANT_DISABLE_INTERRUPTS;
    }
#endif

    SILENCE(bye);
    SILENCE2(boing);
    SILENCE2(frappe);
    SILENCE(debut_match);
    SILENCE(engagement);
    SILENCE(clapclap);
    SILENCE2(avant_engagement);
    SILENCE2(get_bonus);
    SILENCE2(got_bonus);
    SILENCE2(end_bonus);
    SILENCE(alea);
    SILENCE(bfork);
    SILENCE2(descotche);
    SILENCE(bip);
    SILENCE(glue);
    SILENCE2(lazer);
    SILENCE(softzak);
    SILENCE(endmatch);

    return MAY_DISABLE_INTERRUPTS;
}

#ifdef __linux__
#include <mikmod.h>

static unsigned char mikok;
static MODULE *module;

void MD_Update(void)
{
    static int z = 0;

    if (z == 0) {
	z = 0;
	if (Player_Active()) {
	    MikMod_Update();
	}
    } else {
	z--;
    }
}

int initMikmod(void)
{
    MikMod_RegisterAllDrivers();
    MikMod_RegisterAllLoaders();
    md_mode =
	DMODE_16BITS | DMODE_STEREO | DMODE_SOFT_MUSIC | DMODE_SOFT_SNDFX;
    md_device = MikMod_DriverFromAlias("oss");
    if (MikMod_Init("buffer=8")) {
	MikMod_Exit();
	return -1;
    }
    MikMod_SetNumVoices(8, 16);
    mikok++;

    return 0;
}

void closeMikmod(void)
{
    if (mikok != 0) {
	MikMod_Exit();
    }
}

int startmod(const char *name)
{
    if (mikok != 0) {
	module = Player_Load(name, 8, 0);
	if (module != NULL) {
	    module->wrap = 1;
	    Player_Start(module);
	}
	MikMod_Update();
	return 0;
    }

    return -1;
}

void endmod(void)
{
    if (mikok != 0 && module != NULL) {
	Player_Stop();
	Player_Free(module);
	module = NULL;
    }
}

int getModulePos(void)
{
    if (mikok != 0 && module != NULL) {
	return (int) module->sngpos;
    }
    return 0;
}

int ismikok(void)
{
    if (mikok != 0) {
	return 1;
    }
    return 0;
}

#endif
