#include "rgo.h"

#ifdef DEFINE_SOUND_POINTERS__
#define EXTERN
#define INITIALIZE(A) A
#define MM_FRAGSIZE "8"
#else
#define EXTERN extern
#define INITIALIZE(A)
#endif

#ifndef __linux__
# define SPL_PATH "sounds\\"
#else
# define SPL_PATH "sounds/"
#endif

#ifndef __linux__
# define ODYSEE(DISCO, THEQUE) EXTERN const char * const SPL_##DISCO \
     INITIALIZE(= SPL_PATH #THEQUE ".spl")
#else
# define ODYSEE(DISCO, THEQUE) EXTERN const char * const SPL_##DISCO \
     INITIALIZE(= SPL_PATH #THEQUE ".wav")
#endif

ODYSEE(rebond, boing);
ODYSEE(rebond2, posevere);
ODYSEE(frappe, debouche);
ODYSEE(frappe2, marteau);
ODYSEE(frappe3, ah);
ODYSEE(clapclap, clapclap);
ODYSEE(debut_match, rosalie);
ODYSEE(engagement, tiretank);
ODYSEE(avant_engagement, coq);
ODYSEE(avant_engagement2, heyeu);
ODYSEE(avant_engagement3, oh_no__2);
ODYSEE(avant_engagement4, casse_1);
ODYSEE(avant_engagement5, rir22);
ODYSEE(get_bonus, caisse);
ODYSEE(got_bonus, coucou);
ODYSEE(end_bonus, tcin);
ODYSEE(alea1, j_dassin);
ODYSEE(alea2, lalala);
ODYSEE(alea3, fanfar1);
ODYSEE(alea4, chiens);
ODYSEE(alea5, rire1);
ODYSEE(alea6, beat11);
ODYSEE(bfork, boom2);
ODYSEE(descotche, wizzzz);
ODYSEE(bip, bip);
ODYSEE(glue, glue);
ODYSEE(lazer, lazerjeu);
ODYSEE(softzak, softzak);
ODYSEE(endmatch, jalou);

#define MAX_VOLUME 32

EXTERN void (*sound_bye) (void);
EXTERN void (*sound_boing) (const int l, const int r);
EXTERN void (*sound_frappe) (const int l, const int r);
EXTERN void (*sound_debut_match) (void);
EXTERN void (*sound_engagement) (void);
EXTERN void (*sound_clapclap) (void);
EXTERN void (*sound_avant_engagement) (const int l, const int r);
EXTERN void (*sound_get_bonus) (const int l, const int r);
EXTERN void (*sound_got_bonus) (const int l, const int r);
EXTERN void (*sound_end_bonus) (const int l, const int r);
EXTERN void (*sound_alea) (void);
EXTERN void (*sound_bfork) (void);
EXTERN void (*sound_descotche) (const int l, const int r);
EXTERN void (*sound_bip) (void);
EXTERN void (*sound_glue) (void);
EXTERN void (*sound_lazer) (const int l, const int r);
EXTERN void (*sound_softzak) (void);
EXTERN void (*sound_endmatch) (void);

#ifdef __linux__
EXTERN int getModulePos(void);
EXTERN int initMikmod(void);
EXTERN void closeMikmod(void);
EXTERN int startmod(const char *name);
EXTERN void endmod(void);
EXTERN int ismikok(void);
#endif

typedef enum Conquete_ {
    MAY_DISABLE_INTERRUPTS, CANT_DISABLE_INTERRUPTS
} Conquete;

extern Conquete sound_select_card(void) RGONOP;
