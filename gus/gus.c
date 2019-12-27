#ifndef __linux__
#include <stdlib.h>
#include "sound/sound.h"
#include "gus/gus.h"

#define MINI_DRAM 512

#define MAX_SAMPLE_SIZE 150000

typedef struct gus_sample_ {
    ULONG begin;
    ULONG end;
    ULONG size;
} gus_sample;

static gus_sample
    sample_rebond, sample_rebond2,
    sample_frappe, sample_frappe2, sample_frappe3,
    sample_clapclap,
    sample_debut_match,
    sample_engagement,
    sample_avant_engagement, sample_avant_engagement2,
    sample_avant_engagement3, sample_avant_engagement4,
    sample_avant_engagement5, sample_get_bonus, sample_got_bonus,
    sample_end_bonus, sample_alea1, sample_alea2, sample_alea3,
    sample_alea4, sample_alea5, sample_alea6, sample_bfork,
    sample_descotche, sample_bip, sample_glue, sample_lazer,
    sample_softzak, sample_endmatch;

static int bermuda = 0;
static unsigned char direct;

#define RANDSPL(S) ((gus_sample *[]) S) \
[ random() % ((sizeof ((gus_sample *[]) S)) / (sizeof (gus_sample *))) ]
#define OR_ ,

static void loadSample(ULONG address, UBYTE * src, ULONG size)
{
    int z = 32;
    unsigned long grospouf = address + size;

    UltraPokeChunk(address, src, size);
    do {
	UltraPoke(grospouf, 0);
	grospouf++;
	z--;
    } while (z != 0);
}

extern __inline__ void design(register unsigned char *zoubida, size_t king)
{
    do {
	*zoubida -= 128;
	zoubida++;
	king--;
    } while (king != 0);
}

int gus_init(void)
{
    FILE *tareum;
    ULONG gusaddress;
    ULONG king;
    unsigned char *pouf = alloca(MAX_SAMPLE_SIZE);

    static void poisson(const char *const fil, gus_sample * gs,
			const unsigned char needa) {
	if ((tareum = fopen(fil, "rb")) == NULL) {
	    gs->begin = NULL;
	} else {
	    fseek(tareum, 0, SEEK_END);
	    king = ftell(tareum);
	    rewind(tareum);
	    fread(pouf, (size_t) king, 1, tareum);
	    fclose(tareum);
	    if (needa == 0) {
		design(pouf, king);
	    }
	    gusaddress = UltraMalloc(king + 32);
	    if (gusaddress != 0) {
		loadSample(gusaddress, pouf, king);
		gs->begin = gusaddress;
		gs->end = gusaddress + king - 1;
		gs->size = king + 32;
	    }
	}
    }

#if 0
    fputs("Probing for a GUS... ", stdout);
#endif
    if (UltraDetect() == 0) {
#if 0
	puts("Noppe :(");
#endif
	return 1;
    }
    UltraOpen(GUS_INIT_NUMBER_OF_VOICES);
    UltraEnableOutput();

    if (UltraSizeDram() > MINI_DRAM) {
	direct = 1;
    }
#if 0
    printf("Found with %u K of RAM, kewl !\n",
	   (unsigned int) UltraSizeDram());
#endif

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

    return 0;
}

#undef WHOHO
#define WHOHO(HEXIUM, CLOWN) UltraFree(sample_##HEXIUM.size, sample_##HEXIUM.begin);

void gus_bye(void)
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

    UltraClose();
}

extern __inline__ void play_init(void)
{
    UltraSelectVoice(bermuda);
    UltraSetFrequency(11000);
    UltraSetVolume(GUS_MAX_VOLUME);
}

static void play_stereo_sample(const gus_sample * const sample,
			       const int l, const int r) RGO;
static void play_stereo_sample(const gus_sample * const sample,
			       const int l, const int r)
{
    if (sample->begin != 0) {
	play_init();
	UltraSetBalance(8 - (l * 8) / MAX_VOLUME + (r * 7) / MAX_VOLUME);
	UltraStartVoice(sample->begin, sample->begin, sample->end, 0);
	bermuda = (bermuda + 1) % GUS_MAX_NUMBER_OF_VOICES;
    }
}

static void play_sample(const gus_sample * const sample) RGO;
static void play_sample(const gus_sample * const sample)
{
    if (sample->begin != 0) {
	play_init();
	UltraSetBalance(5 + (rand() % 7));
	UltraStartVoice(sample->begin, sample->begin, sample->end, 0);
	bermuda = (bermuda + 1) % GUS_MAX_NUMBER_OF_VOICES;
    }
}

static void play_looping_sample(const gus_sample * const sample) RGO;
static void play_looping_sample(const gus_sample * const sample)
{
    if (sample->begin != 0) {
	play_init();
	UltraSetBalance(6 + (rand() % 5));
	UltraStartVoice(sample->begin, sample->begin, sample->end, 8);
	bermuda = (bermuda + 1) % GUS_MAX_NUMBER_OF_VOICES;
    }
}

void gus_boing(const int l, const int r)
{
    play_stereo_sample(RANDSPL( {
			       &sample_rebond OR_ & sample_rebond2}), l,
		       r);
}

void gus_frappe(const int l, const int r)
{
    play_stereo_sample(RANDSPL( {
			       &sample_frappe OR_ & sample_frappe2 OR_
			       & sample_frappe3}), l, r);
}

void gus_debut_match(void)
{
    play_sample(&sample_debut_match);
}

void gus_clapclap(void)
{
    play_sample(&sample_clapclap);
}

void gus_engagement(void)
{
    play_sample(&sample_engagement);
}

void gus_avant_engagement(const int l, const int r)
{
    play_stereo_sample(RANDSPL( {
			       &sample_avant_engagement OR_
			       & sample_avant_engagement2 OR_ &
			       sample_avant_engagement3 OR_ &
			       sample_avant_engagement4 OR_ &
			       sample_avant_engagement5}), l, r);
}

void gus_get_bonus(const int l, const int r)
{
    play_stereo_sample(&sample_get_bonus, l, r);
}

void gus_got_bonus(const int l, const int r)
{
    play_stereo_sample(&sample_got_bonus, l, r);
}

void gus_end_bonus(const int l, const int r)
{
    play_stereo_sample(&sample_end_bonus, l, r);
}

void gus_alea(void)
{
    play_looping_sample(RANDSPL( {
				&sample_alea1 OR_ & sample_alea2 OR_
				& sample_alea3 OR_ & sample_alea4 OR_ &
				sample_alea5 OR_ & sample_alea6 OR_ &
				sample_debut_match}));
}

void gus_bfork(void)
{
    play_sample(&sample_bfork);
}

void gus_descotche(const int l, const int r)
{
    play_stereo_sample(&sample_descotche, l, r);
}

void gus_bip(void)
{
    play_sample(&sample_bip);
}

void gus_glue(void)
{
    play_sample(&sample_glue);
}

void gus_lazer(const int l, const int r)
{
    play_stereo_sample(&sample_lazer, l, r);
}

void gus_softzak(void)
{
    play_looping_sample(&sample_softzak);
}

void gus_endmatch(void)
{
    play_sample(&sample_endmatch);
}
#endif
