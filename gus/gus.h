#include "gus/drv_gus.h"

#define GUS_INIT_NUMBER_OF_VOICES 14
#define GUS_MAX_NUMBER_OF_VOICES 14
#define GUS_MAX_VOLUME 3800

extern int gus_init(void);
extern void gus_bye(void);
extern void gus_boing(const int l, const int r);
extern void gus_frappe(const int l, const int r);
extern void gus_debut_match(void);
extern void gus_engagement(void);
extern void gus_clapclap(void);
extern void gus_avant_engagement(const int l, const int r);
extern void gus_get_bonus(const int l, const int r);
extern void gus_got_bonus(const int l, const int r);
extern void gus_end_bonus(const int l, const int r);
extern void gus_alea(void);
extern void gus_bfork(void);
extern void gus_descotche(const int l, const int r);
extern void gus_bip(void);
extern void gus_glue(void);
extern void gus_lazer(const int l, const int r);
extern void gus_softzak(void);
extern void gus_endmatch(void);
