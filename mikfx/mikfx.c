#ifdef __linux__
#include <stdlib.h>
#include <mikmod.h>
#include "sound/sound.h"

static SAMPLE
    * sample_rebond, *sample_rebond2,
    *sample_frappe, *sample_frappe2, *sample_frappe3,
    *sample_clapclap,
    *sample_debut_match,
    *sample_engagement,
    *sample_avant_engagement, *sample_avant_engagement2,
    *sample_avant_engagement3, *sample_avant_engagement4,
    *sample_avant_engagement5, *sample_get_bonus, *sample_got_bonus,
    *sample_end_bonus, *sample_alea1, *sample_alea2, *sample_alea3,
    *sample_alea4, *sample_alea5, *sample_alea6, *sample_bfork,
    *sample_descotche, *sample_bip, *sample_glue, *sample_lazer,
    *sample_softzak, *sample_endmatch;

#define RANDSPL(S) ((SAMPLE *[]) S) [ random() % ((sizeof ((SAMPLE *[]) S)) / (sizeof (SAMPLE *))) ]
#define OR_ ,

int mikfx_init(void)
{
    static void poisson(const char *const fil, SAMPLE ** gs,
			const unsigned char needa) {
	(void) needa;
	*gs = Sample_Load(fil);
    }

    if (ismikok() == 0) {
	return -1;
    }
#define WHOHO(HEXIUM, CLOWN) poisson(SPL_##HEXIUM, &sample_##HEXIUM, CLOWN);
#define WAV 1
#define RAW 0

    WHOHO(rebond, RAW);
    WHOHO(rebond2, RAW);
    WHOHO(frappe, RAW);
    WHOHO(frappe2, RAW);
    WHOHO(frappe3, RAW);
    WHOHO(engagement, RAW);
    WHOHO(get_bonus, RAW);
    WHOHO(got_bonus, RAW);
    WHOHO(end_bonus, RAW);
    WHOHO(bfork, RAW);
    WHOHO(descotche, RAW);
    WHOHO(bip, RAW);
    WHOHO(glue, RAW);
    WHOHO(lazer, RAW);
    WHOHO(avant_engagement, RAW);
    WHOHO(debut_match, RAW);

    WHOHO(avant_engagement2, RAW);
    WHOHO(avant_engagement3, RAW);
    WHOHO(avant_engagement4, RAW);
    WHOHO(avant_engagement5, RAW);
    WHOHO(clapclap, RAW);
    WHOHO(softzak, RAW);
    WHOHO(endmatch, RAW);
    WHOHO(alea1, RAW);
    WHOHO(alea2, RAW);
    WHOHO(alea3, RAW);
    WHOHO(alea4, RAW);
    WHOHO(alea5, RAW);
    WHOHO(alea6, RAW);

    MikMod_DisableOutput();
    MikMod_SetNumVoices(-1, 16);
    MikMod_EnableOutput();

    return 0;
}

#undef WHOHO
#define WHOHO(HEXIUM, CLOWN) Sample_Free(sample_##HEXIUM)

void mikfx_bye(void)
{
    WHOHO(rebond, RAW);
    WHOHO(rebond2, RAW);
    WHOHO(frappe, RAW);
    WHOHO(frappe2, RAW);
    WHOHO(frappe3, RAW);
    WHOHO(engagement, RAW);
    WHOHO(get_bonus, RAW);
    WHOHO(got_bonus, RAW);
    WHOHO(end_bonus, RAW);
    WHOHO(bfork, RAW);
    WHOHO(descotche, RAW);
    WHOHO(bip, RAW);
    WHOHO(glue, RAW);
    WHOHO(lazer, RAW);
    WHOHO(avant_engagement, RAW);
    WHOHO(debut_match, RAW);

    WHOHO(avant_engagement2, RAW);
    WHOHO(avant_engagement3, RAW);
    WHOHO(avant_engagement4, RAW);
    WHOHO(avant_engagement5, RAW);
    WHOHO(clapclap, RAW);
    WHOHO(softzak, RAW);
    WHOHO(endmatch, RAW);
    WHOHO(alea1, RAW);
    WHOHO(alea2, RAW);
    WHOHO(alea3, RAW);
    WHOHO(alea4, RAW);
    WHOHO(alea5, RAW);
    WHOHO(alea6, RAW);
}

static void play_stereo_sample(SAMPLE * const sample,
			       const int l, const int r) RGO;
static void play_stereo_sample(SAMPLE * const sample,
			       const int l, const int r)
{
    if (sample != NULL) {
	sample->flags &= ~SF_LOOP;
	{
	    const int v = Sample_Play(sample, 0, 0);
	    Voice_SetPanning(v,
			     128 - (l * 128) / MAX_VOLUME +
			     (r * 127) / MAX_VOLUME);
	    MikMod_Update();
	}
    }
}

static void play_sample(SAMPLE * const sample) RGO;
static void play_sample(SAMPLE * const sample)
{
    if (sample != NULL) {
	sample->flags &= ~SF_LOOP;
	{
	    const int v = Sample_Play(sample, 0, 0);
	    Voice_SetPanning(v, rand() % 256);
	    MikMod_Update();
	}
    }
}

static void play_looping_sample(SAMPLE * const sample) RGO;
static void play_looping_sample(SAMPLE * const sample)
{
    if (sample != NULL) {
	sample->loopstart = 0;
	sample->loopend = sample->length;
	sample->flags |= SF_LOOP;
	{
	    const int v = Sample_Play(sample, 0, 0);
	    Voice_SetPanning(v, rand() % 256);
	    MikMod_Update();
	}
    }
}

void mikfx_boing(const int l, const int r)
{
    play_stereo_sample(RANDSPL( {
			       sample_rebond OR_ sample_rebond2}), l, r);
}

void mikfx_frappe(const int l, const int r)
{
    play_stereo_sample(RANDSPL( {
			       sample_frappe OR_ sample_frappe2 OR_
			       sample_frappe3}), l, r);
}

void mikfx_debut_match(void)
{
    play_sample(sample_debut_match);
}

void mikfx_clapclap(void)
{
    play_sample(sample_clapclap);
}

void mikfx_engagement(void)
{
    play_sample(sample_engagement);
}

void mikfx_avant_engagement(const int l, const int r)
{
    play_stereo_sample(RANDSPL( {
			       sample_avant_engagement OR_
			       sample_avant_engagement2 OR_
			       sample_avant_engagement3 OR_
			       sample_avant_engagement4 OR_
			       sample_avant_engagement5}), l, r);
}

void mikfx_get_bonus(const int l, const int r)
{
    play_stereo_sample(sample_get_bonus, l, r);
}

void mikfx_got_bonus(const int l, const int r)
{
    play_stereo_sample(sample_got_bonus, l, r);
}

void mikfx_end_bonus(const int l, const int r)
{
    play_stereo_sample(sample_end_bonus, l, r);
}

void mikfx_alea(void)
{
    play_looping_sample(RANDSPL( {
				sample_alea1 OR_ sample_alea2 OR_
				sample_alea3 OR_ sample_alea4 OR_
				sample_alea5 OR_ sample_alea6 OR_
				sample_debut_match}));
}

void mikfx_bfork(void)
{
    play_sample(sample_bfork);
}

void mikfx_descotche(const int l, const int r)
{
    play_stereo_sample(sample_descotche, l, r);
}

void mikfx_bip(void)
{
    play_sample(sample_bip);
}

void mikfx_glue(void)
{
    play_sample(sample_glue);
}

void mikfx_lazer(const int l, const int r)
{
    play_stereo_sample(sample_lazer, l, r);
}

void mikfx_softzak(void)
{
    play_looping_sample(sample_softzak);
}

void mikfx_endmatch(void)
{
    play_sample(sample_endmatch);
}
#endif
