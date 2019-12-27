#ifndef __linux__
#include <stdlib.h>
#include <stdio.h>
#include "rgo.h"
#include "sound/sound.h"
#include "sb/sb.h"

static sb_sample
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

static sb_status sb_stat;

#define RANDSPL(S) ((sb_sample *[]) S) \
[ random() % ((sizeof ((sb_sample *[]) S)) / (sizeof (sb_sample *))) ]
#define OR_ ,

int sb_init(void)
{
#if 0
    fputs("Probing for a Sound Blaster...", stdout);
#endif
    if ((sb_stat = sb_install_driver(11000)) != SB_SUCCESS) {
#if 0
	puts("Yapa.");
#endif
	return 1;
    }
#if 0
    puts("Yeah.");
#endif

#define WHOHO(HEXIUM, CLOWN) \
   sample_##HEXIUM = sb_load_sample(SPL_##HEXIUM, _SB_##CLOWN)

    WHOHO(rebond, RAW);
    WHOHO(rebond2, RAW);
    WHOHO(frappe, RAW);
    WHOHO(frappe2, RAW);
    WHOHO(frappe3, RAW);
    WHOHO(clapclap, RAW);
    WHOHO(debut_match, RAW);
    WHOHO(engagement, RAW);
    WHOHO(avant_engagement, RAW);
    WHOHO(avant_engagement2, RAW);
    WHOHO(avant_engagement3, RAW);
    WHOHO(avant_engagement4, RAW);
    WHOHO(avant_engagement5, RAW);
    WHOHO(get_bonus, RAW);
    WHOHO(got_bonus, RAW);
    WHOHO(end_bonus, RAW);
    WHOHO(alea1, RAW);
    WHOHO(alea2, RAW);
    WHOHO(alea3, RAW);
    WHOHO(alea4, RAW);
    WHOHO(alea5, RAW);
    WHOHO(alea6, RAW);
    WHOHO(bfork, RAW);
    WHOHO(descotche, RAW);
    WHOHO(bip, RAW);
    WHOHO(glue, RAW);
    WHOHO(lazer, RAW);
    WHOHO(softzak, RAW);
    WHOHO(endmatch, RAW);

    return 0;
}

void sb_bye(void)
{
    if (sb_stat != SB_SUCCESS) {
	return;
    }
#define FRI(ZONE) sb_free_sample(sample_##ZONE)

    FRI(rebond);
    FRI(rebond2);
    FRI(frappe);
    FRI(frappe2);
    FRI(frappe3);
    FRI(engagement);
    FRI(clapclap);
    FRI(debut_match);
    FRI(avant_engagement);
    FRI(avant_engagement2);
    FRI(avant_engagement3);
    FRI(avant_engagement4);
    FRI(avant_engagement5);
    FRI(get_bonus);
    FRI(got_bonus);
    FRI(end_bonus);
    FRI(alea1);
    FRI(alea2);
    FRI(alea3);
    FRI(alea4);
    FRI(alea5);
    FRI(alea6);
    FRI(bfork);
    FRI(descotche);
    FRI(bip);
    FRI(glue);
    FRI(lazer);
    FRI(softzak);
    FRI(endmatch);

    sb_uninstall_driver();
}

static void play_sample(sb_sample * const sample)
{
    if (sb_stat == SB_SUCCESS) {
	const int ouargl = rand() % (MAX_VOLUME / 2);

	if ((ouargl & 1) != 0) {
	    sample->left_volume = MAX_VOLUME - ouargl;
	    sample->right_volume = ouargl;
	} else {
	    sample->left_volume = ouargl;
	    sample->right_volume = MAX_VOLUME - ouargl;
	}
	sb_mix_sample(sample);
    }
}

static __inline__ void play_stereo_sample(sb_sample * const sample,
					  const int l, const int r)
{
    if (sb_stat == SB_SUCCESS) {
	sample->left_volume = l;
	sample->right_volume = r;
	sb_mix_sample(sample);
    }
}

void sb_boing(const int l, const int r)
{
    play_stereo_sample(RANDSPL( {
			       sample_rebond OR_ sample_rebond2}), l, r);
}

void sb_frappe(const int l, const int r)
{
    play_stereo_sample(RANDSPL( {
			       sample_frappe OR_ sample_frappe2 OR_
			       sample_frappe3}), l, r);
}

void sb_debut_match(void)
{
    play_sample(sample_debut_match);
}

void sb_clapclap(void)
{
    play_sample(sample_clapclap);
}

void sb_engagement(void)
{
    play_sample(sample_engagement);
}

void sb_avant_engagement(const int l, const int r)
{
    play_stereo_sample(RANDSPL( {
			       sample_avant_engagement OR_
			       sample_avant_engagement2 OR_
			       sample_avant_engagement3 OR_
			       sample_avant_engagement4 OR_
			       sample_avant_engagement5}), l, r);
}

void sb_get_bonus(const int l, const int r)
{
    play_stereo_sample(sample_get_bonus, l, r);
}

void sb_got_bonus(const int l, const int r)
{
    play_stereo_sample(sample_got_bonus, l, r);
}

void sb_end_bonus(const int l, const int r)
{
    play_stereo_sample(sample_end_bonus, l, r);
}

void sb_alea(void)
{
    play_sample(RANDSPL( {
			sample_alea1 OR_ sample_alea2 OR_ sample_alea3 OR_
			sample_alea4 OR_ sample_alea5 OR_ sample_alea6 OR_
			sample_debut_match}));
}

void sb_bfork(void)
{
    play_sample(sample_bfork);
}

void sb_descotche(const int l, const int r)
{
    play_stereo_sample(sample_descotche, l, r);
}

void sb_bip(void)
{
    play_sample(sample_bip);
}

void sb_glue(void)
{
    play_sample(sample_glue);
}

void sb_lazer(const int l, const int r)
{
    play_stereo_sample(sample_lazer, l, r);
}

void sb_softzak(void)
{
    play_sample(sample_softzak);
}

void sb_endmatch(void)
{
    play_sample(sample_endmatch);
}
#endif
