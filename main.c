/* Jedi/Sector One */

#include "main.h"
#ifdef __linux__
# include <vgakeyboard.h>
# include <mikmod.h>
#endif

static void action(Raq * const raq) RGO;

static void resetNoBonus(void) RGONOP;
static void resetNoBonus(void)
{
    const RaqList *flip;

    if (phasis == PHS_NORMAL) {
	raq1.type = RAE_NORMAL;
	flip = &raqList[RAE_NORMAL];
    } else {
	raq2.type = RAE_NORMAL;
	flip = &raqList[RAE_BISOU1];
    }

    raq1.couple.load = flip->couple.load;
    raq1.couple.sprite = flip->couple.sprite;
    raq1.width = flip->width;
    raq1.height = flip->height;
    raq1.addx = INITIAL_RAQSPEED_X;
    raq1.addy = INITIAL_RAQSPEED_Y;
    raq1.acutance = ACUTANCE;
    raq1.iscotched = ISD_NOTSCOTCHED;
    raq1.hasGlue = raq1.hasNoLimit = raq1.hasLazer = 0;
    raq1.downspeed = DOD_NORMAL;

    if (phasis == PHS_BISOU) {
	flip = &raqList[RAE_BISOU2];
    }

    raq2.couple.load = flip->couple.load;
    raq2.couple.sprite = flip->couple.sprite;
    raq2.width = flip->width;
    raq2.height = flip->height;
    raq2.addx = INITIAL_RAQSPEED_X;
    if (simpleGame == 2) {
	raq2.addy = BOOSTED_RAQSPEED_Y;
    } else {
	raq2.addy = INITIAL_RAQSPEED_Y;
    }
    raq2.acutance = ACUTANCE;
    raq2.iscotched = ISD_NOTSCOTCHED;
    raq2.hasGlue = raq2.hasNoLimit = raq2.hasLazer = 0;
    raq2.downspeed = DOD_NORMAL;
}

static void resetSpritesPos(void) RGONOP;
static void resetSpritesPos(void)
{
    const BallList *flip;
    Ball *epinard = ball;
    int t = MAXBALLS;

    if (phasis == PHS_NORMAL) {
	numberOfBalls = 1;
    } else {
	numberOfBalls = NUMBER_OF_COEURS;
    }

    raq1.x = 0;
    raq1.y = (SCREEN_HEIGHT - raq1.height) >> 1;
    raq1.addr = phybase + screenOffset(raq1.x, raq1.y);
    raq2.x = SCREEN_WIDTH - raq2.width;
    raq2.y = (SCREEN_HEIGHT - raq2.height) >> 1;
    raq2.addr = phybase + screenOffset(raq2.x, raq2.y);

    do {
	epinard->enabled = 0;
#if FUNNY_SPEED
	do {
	    epinard->addx = (rand() % 10) - 5;
	    epinard->addy = (rand() % 8) - 4;
	} while (epinard->addx == 0 || epinard->addy == 0);
#else
	epinard->addx = 0;
	if ((rand() & 1) == 0) {
	    epinard->addy = 2;
	} else {
	    epinard->addy = -2;
	}
#endif
	if (phasis == PHS_NORMAL) {
	    epinard->size = BAE_NORMAL;
	} else {
	    epinard->size = BAE_COEUR1 + (t % NUMBER_OF_COEURS);
	}
	flip = &ballList[epinard->size];
	epinard->iscotched = ISD_NOTSCOTCHED;

	epinard->width = flip->width;
	epinard->height = flip->height;
	epinard->couple.load = flip->couple.load;
	epinard->couple.sprite = flip->couple.sprite;

#if FUNNY_POS
	epinard->x = (rand() % (SCREEN_WIDTH - epinard->width));
	epinard->y = (rand() % (SCREEN_HEIGHT - epinard->height));
#else
	epinard->x = (SCREEN_WIDTH - epinard->width) >> 1;
# if 0
	epinard->y = (SCREEN_HEIGHT - epinard->height) >> 1;
# else
	epinard->y = (rand() % (SCREEN_HEIGHT - epinard->height));
# endif
#endif
	epinard->addr = phybase + screenOffset(epinard->x, epinard->y);

	epinard++;
	t--;
    } while (t != 0);

    ball[0].enabled = 1;
    if (phasis == PHS_BISOU) {
	ball[1].enabled = ball[2].enabled = ball[3].enabled = 1;
    }
#if BONI_SUPPORT
    bonus.enabled = 0;
    if (cheatMode == 0) {
	bonusWait = (rand() % BONUS_CHANCES);
    } else {
	bonusWait = 1;
    }
    if (bonusList[bonusRond1.type].recycler == BOR_ONEPOINT) {
	if (bonusRond1.enabled != 0) {
	    bonusList[bonusRond1.type].disableBonus(&raq1);
	}
	bonusRond1.enabled = 0;
	bonusRond1.timeout = BONUS_TIMEOUT;
    }
    if (bonusList[bonusRond2.type].recycler == BOR_ONEPOINT) {
	if (bonusRond2.enabled != 0) {
	    bonusList[bonusRond2.type].disableBonus(&raq2);
	}
	bonusRond2.enabled = 0;
	bonusRond2.timeout = BONUS_TIMEOUT;
    }
#endif
}

static __inline__ void kbdtrap(void)
{
#ifndef __linux__
    __dpmi_paddr addr;

    __dpmi_get_protected_mode_interrupt_vector(INTERRUPT_KEY, &shitMaker);
    addr.selector = _my_cs();
    addr.offset32 = (unsigned long) pepsi;
    irq_redirected = ~irq_redirected;
    __dpmi_set_protected_mode_interrupt_vector(INTERRUPT_KEY, &addr);
#else
    keyboard_init();
#endif
}

static __inline__ void checkTree(void)
{
    FILE *fp;

    if ((fp = fopen(SPL_rebond, "rb")) == NULL) {
	fputs
	    ("  Sorry but either some files are missing, either you extracted the game\n"
	     "without its directories. You should have a subdirectory called "
	     SPL_PATH "\n"
	     "in the current path. Erase these files and uncompress the game properly with\n"
	     "a correct tree. With PKUNZIP under DOS, a correct command line would look like:\n"
	     "\n\t\tPKUNZIP -D PING.ZIP\n\n"
	     "  Please try anew to enjoy dis junky game.", stderr);
	exit(EXIT_FAILURE);
    }
    fclose(fp);
}

static __inline__ void init(void)
{
    time_t mortel;

#if NEED_TRADITIONAL_NEARPTR
    if (__djgpp_nearptr_enable() == 0) {
	fputs("Sorry but I can't switch into flat memory mode", stderr);
	exit(EXIT_FAILURE);
    }
#endif

    time(&mortel);
    srand((unsigned int) (mortel & 0x7fff));

    checkTree();
    kbdtrap();

#ifdef __linux__
    xmode();
#endif

    phybase = getphybase(1);
    xclear(phybase);
    phybase = getphybase(0);
    xclear(phybase);

    if ((screenSave =
	 (unsigned char *) malloc(SCREEN_LENGTH_IN_BYTES * 4)) == NULL) {
      phreeyourmind:
	fputs("Oh no ! More memory !", stderr);
	exit(EXIT_FAILURE);
    }
    if ((screenSave2 =
	 (unsigned char *) malloc(SCREEN_LENGTH_IN_BYTES * 4)) == NULL) {
	goto phreeyourmind;
    }

    vsync();
    setblack();

#ifdef __linux__
    initMikmod();
#endif
}

static __inline__ void initGame(void)
{
    vsync();
    setblack();
    xmode();
    setblack();
    setPage(0);
    if (sound_select_card() == MAY_DISABLE_INTERRUPTS) {
#ifndef __linux__
	disable();
#endif
    }
    sfx_enabled = 1;

    numberOfBalls = 1;
    score1 = score2 = 0;
    cheatMode = 0;
    phasis = terrainPhasis = requestedPhasis = PHS_NORMAL;

    bonusRond1.enabled = 0;
    bonusRond1.x = ROND_XL;
    raq1.bonusRond = &bonusRond1;
    bonusRond2.enabled = 0;
    bonusRond2.x = ROND_XR;
    raq2.bonusRond = &bonusRond2;
    resetSpritesPos();
    terrain1();
    vsync();
    setpal();
    if ((rand() & 1) != 0) {
	kikigo = KIKI_RIGHT;
    }
}

static __inline__ void bye(void)
{
    if (irq_redirected == 0) {
#ifndef __linux__
	enable();
#endif
    } else {
#ifndef __linux__
	__dpmi_set_protected_mode_interrupt_vector(INTERRUPT_KEY,
						   &shitMaker);
#endif
    }
    if (sfx_enabled != 0) {
	sound_bye();
    }
#if NEED_TRADITIONAL_NEARPTR
    __djgpp_nearptr_disable();
#endif
    txtmode();
    puts("Diz was <<Ping!>> - (C)oderite Sector One & Fantasy.\n"
         "ftp://ftp.c9x.org/pub/ping/");
}

static __inline__ void swapScreens(void)
{
    setbackground(0, 0, 7);
    vsync();
    curscrn ^= 1;
    setPage(curscrn);
    curscreen = &screen[curscrn];
#if SHOW_VBL
    setbackground(4, 4, 11);
#endif
    if (sound_frappe_delay != 0) {
	sound_frappe_delay--;
    }
#ifdef __linux__
    MikMod_Update();
#endif
}

static __inline__ void goup1(void)
{
    if ((raq1.y -= raq1.addy) < 0) {
	raq1.y = 0;
    }
}

static __inline__ void godown1(void)
{
    if ((raq1.y += raq1.addy) > (SCREEN_HEIGHT - raq1.height)) {
	raq1.y = SCREEN_HEIGHT - raq1.height;
    }
}

static __inline__ void goleft1(void)
{
    if ((raq1.x -= raq1.addx) < 0) {
	raq1.x = 0;
    }
}

static __inline__ void goright1(void)
{
    int rigolo = SCREEN_MIDDLE - FILET_GAP - raq1.width;

    if (raq1.hasNoLimit != 0) {
	rigolo = SCREEN_WIDTH - NOLIMIT_GAP - raq1.width - raq2.width;
    }
    if ((raq1.x += raq1.addx) > rigolo) {
	raq1.x = rigolo;
    }
}

static __inline__ void goup2(void)
{
    if ((raq2.y -= raq2.addy) < 0) {
	raq2.y = 0;
    }
}

static __inline__ void godown2(void)
{
    if ((raq2.y += raq2.addy) > (SCREEN_HEIGHT - raq2.height)) {
	raq2.y = SCREEN_HEIGHT - raq2.height;
    }
}

static __inline__ void goleft2(void)
{
    int rigolo = SCREEN_MIDDLE + FILET_GAP;

    if (raq2.hasNoLimit != 0) {
	rigolo = NOLIMIT_GAP + raq1.width;
    }
    if ((raq2.x -= raq2.addx) < rigolo) {
	raq2.x = rigolo;
    }
}

static __inline__ void goright2(void)
{
    if ((raq2.x += raq2.addx) > (SCREEN_WIDTH - raq2.width)) {
	raq2.x = SCREEN_WIDTH - raq2.width;
    }
}

typedef enum PointState_ {
    POE_NONE, POE_LEFT, POE_RIGHT
} PointState;

#if BONI_SUPPORT

static __inline__ void addBalls(int ballsToAdd,
				const BallSize ballSize) RGO;
static __inline__ void addBalls(int ballsToAdd, const BallSize ballSize)
{
    const BallList *const flip = &ballList[ballSize];
    Ball *epinard = ball;
    int t = MAXBALLS;

    sound_bfork();

    do {
	if (epinard->enabled == 0) {
	    epinard->enabled = 1;
	    epinard->x = (SCREEN_WIDTH - epinard->width) >> 1;
	    epinard->y = (rand() % (SCREEN_HEIGHT - epinard->height));
	    epinard->addr = phybase + screenOffset(epinard->x, epinard->y);
	    epinard->size = ballSize;
	    epinard->iscotched = ISD_NOTSCOTCHED;

	    epinard->width = flip->width;
	    epinard->height = flip->height;
	    epinard->couple.load = flip->couple.load;
	    epinard->couple.sprite = flip->couple.sprite;

	    do {
		epinard->addx =
		    (rand() % (NEW_BALLSPEED_X * 2)) - NEW_BALLSPEED_X;
		epinard->addy =
		    (rand() % (NEW_BALLSPEED_Y * 2)) - NEW_BALLSPEED_Y;
	    } while (epinard->addx == 0 || epinard->addy == 0);
	    numberOfBalls++;
	    ballsToAdd--;
	    if (ballsToAdd == 0) {
		break;
	    }
	}
	epinard++;
	t--;
    } while (t != 0);
}

static __inline__ void sgbonus(const Raq * const raq) RGO;
static __inline__ void sgbonus(const Raq * const raq)
{
    const int jk = raq->x * MAX_VOLUME / (SCREEN_WIDTH - BONUS_WIDTH);
    sound_got_bonus(MAX_VOLUME - jk, jk);
}

void enableBonus_multiball(Raq * const raq)
{
    int caroline;

    (void) raq;

    switch (rand() & 3) {
    case 0:
	caroline = 3;
	break;
    case 1:
	caroline = 10;
	break;
    default:
	caroline = MAXBALLS;
    }
    addBalls(caroline, BAE_NORMAL);
}
void disableBonus_multiball(Raq * const raq)
{
    (void) raq;
}

void enableBonus_ballsize(Raq * const raq)
{
    const BallList *flip;
    Ball *epinard = ball;
    int t = MAXBALLS;
    int ballsToAdd = numberOfBalls;
    BallSize ballSize;

    (void) raq;
    sound_glue();

    do {
	if (epinard->enabled != 0) {
	    epinard->addr = phybase + screenOffset(epinard->x, epinard->y);
	    do {
		ballSize = rand() % NUMBER_OF_BALLKINDS;
	    } while (epinard->size == ballSize);
	    epinard->size = ballSize;

	    flip = &ballList[ballSize];

	    epinard->x += ((epinard->width - flip->width) >> 1);
	    epinard->y += ((epinard->height - flip->height) >> 1);

	    epinard->width = flip->width;
	    epinard->height = flip->height;
	    epinard->couple.load = flip->couple.load;
	    epinard->couple.sprite = flip->couple.sprite;

	    ballsToAdd--;
	    if (ballsToAdd == 0) {
		break;
	    }
	}
	epinard++;
	t--;
    } while (t != 0);
}
void disableBonus_ballsize(Raq * const raq)
{
    (void) raq;
}

void enableBonus_raqsize(Raq * const raq)
{
    const RaqList *flip;
    RaqType raqType;

    sound_bip();
    do {
	raqType = rand() % NUMBER_OF_RAQTYPES;
    } while (raqType == raq->type);
    flip = &raqList[raqType];
    raq->type = raqType;
    raq->couple.load = flip->couple.load;
    raq->couple.sprite = flip->couple.sprite;

    raq->x += ((raq->width - flip->width) >> 1);
    raq->y += ((raq->height - flip->height) >> 1);

    raq->width = flip->width;
    raq->height = flip->height;

    if (raq->x < 0) {
	raq->x = 0;
    }
    if (raq->x > (SCREEN_WIDTH - raq->width)) {
	raq->x = SCREEN_WIDTH - raq->width;
    }
    if (raq->y < 0) {
	raq->y = 0;
    }
    if (raq->y > (SCREEN_HEIGHT - raq->height)) {
	raq->y = SCREEN_HEIGHT - raq->height;
    }
}
void disableBonus_raqsize(Raq * const raq)
{
    const RaqList *const flip = &raqList[RAE_NORMAL];

    sound_bip();
    raq->type = RAE_NORMAL;
    raq->couple.load = flip->couple.load;
    raq->couple.sprite = flip->couple.sprite;
    raq->width = flip->width;
    raq->height = flip->height;
}

void enableBonus_raqspeed(Raq * const raq)
{
    sgbonus(raq);
    raq->addx = BOOSTED_RAQSPEED_X;
    raq->addy = BOOSTED_RAQSPEED_Y;
}
void disableBonus_raqspeed(Raq * const raq)
{
    raq->addx = INITIAL_RAQSPEED_X;
    raq->addy = INITIAL_RAQSPEED_Y;
}

void enableBonus_inertie(Raq * const raq)
{
    sgbonus(raq);
}
void disableBonus_inertie(Raq * const raq)
{
    (void) raq;
}

void enableBonus_wall(Raq * const raq)
{
    sgbonus(raq);
}
void disableBonus_wall(Raq * const raq)
{
    (void) raq;
}

void enableBonus_glue(Raq * const raq)
{
    sgbonus(raq);
    raq->hasGlue = 1;
}

void disableBonus_glue(Raq * const raq)
{
    if (simpleGame == 2) {
	action(raq);
    }
    raq->hasGlue = 0;
}

void enableBonus_ballway(Raq * const raq)
{
    Ball *epinard = ball;
    int skudz = numberOfBalls;

    sgbonus(raq);

    do {
	if (epinard->enabled != 0) {
	    epinard->addx = -epinard->addx;
	    skudz--;
	}
	epinard++;
    } while (skudz != 0);
}
void disableBonus_ballway(Raq * const raq)
{
    (void) raq;
}

void enableBonus_gravity(Raq * const raq)
{
    sgbonus(raq);
}
void disableBonus_gravity(Raq * const raq)
{
    (void) raq;
}

void enableBonus_angle(Raq * const raq)
{
    sgbonus(raq);
    raq->acutance = HIGH_ACUTANCE;
}
void disableBonus_angle(Raq * const raq)
{
    raq->acutance = ACUTANCE;
}

void enableBonus_downspeed(Raq * const raq)
{
    sgbonus(raq);
    if (raq == &raq1) {
	raq1.downspeed = DOD_UPSPEED;
	raq2.downspeed = DOD_DOWNSPEED;
	raq2.acutance = LOW_ACUTANCE;
    } else {
	raq1.acutance = LOW_ACUTANCE;
	raq1.downspeed = DOD_DOWNSPEED;
	raq2.downspeed = DOD_UPSPEED;
    }
}
void disableBonus_downspeed(Raq * const raq)
{
    (void) raq;

    raq1.downspeed = raq2.downspeed = DOD_NORMAL;
    if (raq1.acutance == LOW_ACUTANCE) {
	raq1.acutance = ACUTANCE;
    }
    if (raq2.acutance == LOW_ACUTANCE) {
	raq2.acutance = ACUTANCE;
    }
}

void enableBonus_tir(Raq * const raq)
{
    sgbonus(raq);
    raq->hasLazer = 1;
}
void disableBonus_tir(Raq * const raq)
{
    raq->hasLazer = 0;
}

void enableBonus_nolimit(Raq * const raq)
{
    sgbonus(raq);
    raq->hasNoLimit = 1;
}
void disableBonus_nolimit(Raq * const raq)
{
    raq->hasNoLimit = 0;
}

void enableBonus_surprise(Raq * const raq)
{
    sgbonus(raq);
    requestedPhasis = PHS_BISOU;
}
void disableBonus_surprise(Raq * const raq)
{
    (void) raq;
}

static void loadBonus(void) RGONOP;
static void loadBonus(void)
{
    if (curscreen->oldBonus.enabled != 0) {
	load_bonusback(curscreen->oldBonusBack.addr,
		       curscreen->oldBonusBack.offset);
	bonus.couple.load(curscreen->oldBonus.addr,
			  curscreen->oldBonus.offset);
	if (bonus.enabled == 0) {
	    curscreen->oldBonus.enabled = 0;
	}
    }
    if (curscreen->oldLazer.lazerAddr != NULL) {
	const unsigned char *const pukka =
	    screenSave + curscreen->oldLazer.offset;
	unsigned char *const lazerAddr = curscreen->oldLazer.lazerAddr;
	const size_t lazerLen = curscreen->oldLazer.lazerLen;


	writePlane(WPLANE0);
	memcpy(lazerAddr, pukka, lazerLen);
	writePlane(WPLANE1);
	memcpy(lazerAddr, pukka + SCREEN_LENGTH_IN_BYTES, lazerLen);
	writePlane(WPLANE2);
	memcpy(lazerAddr, pukka + SCREEN_LENGTH_IN_BYTES * 2, lazerLen);
	writePlane(WPLANE3);
	memcpy(lazerAddr, pukka + SCREEN_LENGTH_IN_BYTES * 3, lazerLen);

	curscreen->oldLazer.lazerAddr = NULL;
    }
}

static void loadRonds(void) RGONOP;
static void loadRonds(void)
{
    if (curscreen->oldRond1.enabled != 0) {
	load_rondback(curscreen->oldRond1.addr,
		      curscreen->oldRond1.offset);
	if (bonusRond1.enabled == 0) {
	    curscreen->oldRond1.enabled = 0;
	}
    }
    if (curscreen->oldRond2.enabled != 0) {
	load_rondback(curscreen->oldRond2.addr,
		      curscreen->oldRond2.offset);
	if (bonusRond2.enabled == 0) {
	    curscreen->oldRond2.enabled = 0;
	}
    }
}

static void dspRond(Raq * const raq, SpriteSave * const oldRond) RGO;
static void dspRond(Raq * const raq, SpriteSave * const oldRond)
{
    BonusRond *const babe = raq->bonusRond;
    int kowabunga;

    if (babe->enabled == 0) {
	return;
    }
    oldRond->enabled = 1;
    if (babe->timeout == 0) {
	babe->timeout = BONUS_TIMEOUT;
	babe->phasis++;
	if (*(babe->phasis) == NULL) {
	    {
		const int jk =
		    babe->x * MAX_VOLUME / (SCREEN_WIDTH - BONUS_WIDTH);
		sound_end_bonus(MAX_VOLUME - jk, jk);
	    }
	    bonusList[babe->type].disableBonus(raq);
	    babe->enabled = 0;
	    return;
	}
    } else {
	babe->timeout--;
    }
#if 1
    if (babe->y > ROND_Y) {
	babe->y--;
    }
#endif
    kowabunga = screenOffset(babe->x, babe->y);
    oldRond->offset = kowabunga;
    babe->addr = phybase + kowabunga;
    oldRond->addr = babe->addr;

    (*(babe->phasis)) (babe->addr, screenShift(babe->x));
}

static void dspBonus(void) RGONOP;
static void dspBonus(void)
{
    typedef struct Kor_ {
	int xmov, ymov;
    } Kor;
    static const Kor derev[] = {
#include "inc/bousin.inc"
    };
    static const Kor *derevpnt = derev;
    static int x, y;
    int kowabunga;

    if (phasis != PHS_NORMAL || simpleGame == 1) {
	return;
    }

    if (lazerWait1 != 0) {
	lazerWait1--;
    }
    if (lazerWait2 != 0) {
	lazerWait2--;
    }
    if (isBlocked1 != 0) {
	isBlocked1--;
    }
    if (isBlocked2 != 0) {
	isBlocked2--;
    }


    if (bonus.enabled == 0) {
	if (bonusWait == 0) {
	    bonus.enabled = 1;
	    do {
		x = (BONUS_WIDTH + BONUS_MOVE) +
		    (rand() %
		     (SCREEN_WIDTH - (BONUS_WIDTH + BONUS_MOVE) * 2));
		y = (BONUS_HEIGHT + BONUS_MOVE) +
		    (rand() %
		     (SCREEN_HEIGHT - (BONUS_HEIGHT + BONUS_MOVE) * 2));
	    } while (INTERSECT
		     (raq1.x - RAQMOVE_GAP, raq1.y - RAQMOVE_GAP,
		      raq1.x + raq1.width + RAQMOVE_GAP,
		      raq1.y + raq1.height + RAQMOVE_GAP, x - BONUS_MOVE,
		      y - BONUS_MOVE, x + BONUS_WIDTH + BONUS_MOVE,
		      y + BONUS_HEIGHT + BONUS_MOVE) != 0
		     || INTERSECT(raq2.x - RAQMOVE_GAP,
				  raq2.y - RAQMOVE_GAP,
				  raq2.x + raq2.width + RAQMOVE_GAP,
				  raq2.y + raq2.height + RAQMOVE_GAP,
				  x - BONUS_MOVE, y - BONUS_MOVE,
				  x + BONUS_WIDTH + BONUS_MOVE,
				  y + BONUS_HEIGHT + BONUS_MOVE) != 0);
	    bonus.x = x;
	    bonus.y = y;
#if 0
	    if (rand() & 1) {
		bonus.type = BOE_TIR;
	    } else {
		bonus.type = BOE_GLUE;
	    }
#else
	    bonus.type = (rand() % NUMBER_OF_BONI);
#endif
	    {
		const BonusCouple *const ouais =
		    &bonusList[bonus.type].couple;

		bonus.couple.sprite = ouais->sprite;
		bonus.couple.load = ouais->load;
	    }

	    {
		const int jk =
		    x * MAX_VOLUME / (SCREEN_WIDTH - BONUS_WIDTH);
		sound_get_bonus(MAX_VOLUME - jk, jk);
	    }

	} else {
	    bonusWait--;
	}
    } else {
	static unsigned char stepin(Raq * const raq) {
	    if (INTERSECT
		(raq->x, raq->y, raq->x + raq->width, raq->y + raq->height,
		 bonus.x, bonus.y, bonus.x + BONUS_WIDTH,
		 bonus.y + BONUS_HEIGHT) != 0) {
		curscreen->oldBonus.enabled = 0;
		bonus.enabled = 0;

		if (cheatMode == 0) {
		    bonusWait = (rand() % BONUS_CHANCES) + BONUS_MINWAIT;
		} else {
		    bonusWait = 1;
		}

		if (bonusList[bonus.type].recycler != BOR_IMMED) {
		    BonusRond *const cornichon = raq->bonusRond;

		    if (cornichon->enabled != 0) {
			bonusList[cornichon->type].disableBonus(raq);
		    } else {
			cornichon->enabled = 1;
		    }
		    cornichon->type = bonus.type;
		    cornichon->phasis = christelle;
		    cornichon->timeout = BONUS_TIMEOUT;
#if 0
		    cornichon->y = ROND_Y;
#else
		    cornichon->y = SCREEN_HEIGHT;
#endif
		}
		bonusList[bonus.type].enableBonus(raq);

		return 1;
	    }

	    return 0;
	}
	if (stepin(&raq1) == 0 && stepin(&raq2) == 0) {
	    curscreen->oldBonus.enabled = 1;

	    bonusBack.x = x + (derevpnt->xmov >> 1);
	    bonusBack.y = y + (derevpnt->ymov >> 1);
	    kowabunga = screenOffset(bonusBack.x, bonusBack.y);
	    curscreen->oldBonusBack.offset = kowabunga;
	    bonusBack.addr = phybase + kowabunga;
	    curscreen->oldBonusBack.addr = bonusBack.addr;
	    sprite_bonusback(bonusBack.addr, screenShift(bonusBack.x));

	    bonus.x = x + derevpnt->xmov;
	    bonus.y = y + derevpnt->ymov;
	    kowabunga = screenOffset(bonus.x, bonus.y);
	    curscreen->oldBonus.offset = kowabunga;
	    bonus.addr = phybase + kowabunga;
	    curscreen->oldBonus.addr = bonus.addr;
	    bonus.couple.sprite(bonus.addr, screenShift(bonus.x));

	    if (derevpnt == &derev[(sizeof derev) / (sizeof derev[0]) - 1]) {
		derevpnt = derev;
	    } else {
		derevpnt++;
	    }
	}
    }
    dspRond(&raq1, &curscreen->oldRond1);
    dspRond(&raq2, &curscreen->oldRond2);
}

#endif

static PointState boingBoing(void) RGONOP;
static PointState boingBoing(void)
{
    static int flipper = ACCELERATION_DELAY;
    BallSave *cahouette = curscreen->oldBall;
    Ball *zeBall = ball;
    int t = numberOfBalls;
    int kowabunga;

    if (aleasoundWait == 0) {
	if (phasis == PHS_BISOU) {
	    sound_softzak();
	} else {
	    sound_alea();
	}
	aleasoundWait = (rand() % ALEASOUND_CHANCES);
    } else {
	aleasoundWait--;
    }

    while (t != 0) {
	if (zeBall->enabled != 0) {
	    t--;

	    zeBall->x += zeBall->addx;
	    zeBall->y += zeBall->addy;

	    if (phasis == PHS_BISOU) {
		typedef struct Kor_ {
		    int xmov, ymov;
		} Kor;
		static const Kor derev[] = {
#include "inc/coeursin.inc"
		};
		static const Kor *derevpnt = derev;

		zeBall->x += derevpnt->xmov;
		zeBall->y += derevpnt->ymov;

		if (derevpnt ==
		    &derev[(sizeof derev) / (sizeof derev[0]) - 1]) {
		    derevpnt = derev;
		} else {
		    derevpnt++;
		}
	    }

	    if (raq1.iscotched == ISD_DECOLE &&
		zeBall->iscotched == ISD_LEFTSCOTCHED) {
		zeBall->iscotched = ISD_NOTSCOTCHED;
		goto toyo1;
	    } else if (zeBall->iscotched == ISD_LEFTSCOTCHED) {
	      stepon1:
		zeBall->x = raq1.x + raq1.width;
		zeBall->y = raq1.y + zeBall->dontstop;
	    } else {
		if (INTERSECT(raq1.x, raq1.y, raq1.x + raq1.width,
			      raq1.y + raq1.height,
			      zeBall->x, zeBall->y,
			      zeBall->x + zeBall->width,
			      zeBall->y + zeBall->height) != 0) {
		    if (raq1.hasGlue != 0) {
			zeBall->iscotched = ISD_LEFTSCOTCHED;
			raq1.iscotched = ISD_SCOTCHED;
			zeBall->dontstop = zeBall->y - raq1.y;
			goto stepon1;
		    }
		    if (sound_frappe_delay == 0) {
			sound_frappe_delay = SOUND_FRAPPE_DELAY;
			sound_frappe(MAX_VOLUME, MAX_VOLUME / 5);
		    }
		  toyo1:
#if CAN_PUSH_BALL
		    zeBall->x = raq1.x + raq1.width;
#endif
		    if (flipper == 0) {
			const int mouchoir = abs(zeBall->addx);

			if (phasis == PHS_NORMAL) {
			    flipper = ACCELERATION_DELAY;
			} else {
			    flipper = LOW_ACCELERATION_DELAY;
			}
			if (mouchoir < MAX_BALLSPEED_X) {
			    zeBall->addx = mouchoir + 1;
			}
		    } else {
			flipper--;
			zeBall->addx = abs(zeBall->addx);
		    }
		    if (raq1.downspeed == DOD_DOWNSPEED) {
			zeBall->addx >>= DOWNSPEED_X;
			if (zeBall->addx == 0) {
			    zeBall->addx = 1;
			}
		    } else if (raq1.downspeed == DOD_UPSPEED) {
			zeBall->addx <<= DOWNSPEED_X;
			if (zeBall->addx > FORCED_BALLSPEED_X) {
			    zeBall->addx = FORCED_BALLSPEED_X;
			}
		    }
		    zeBall->addy =
			(zeBall->y +
			 ((zeBall->height - raq1.height) >> 1) -
			 raq1.y) >> raq1.acutance;
		}
	    }

	    if (raq2.iscotched == ISD_DECOLE &&
		zeBall->iscotched == ISD_RIGHTSCOTCHED) {
		zeBall->iscotched = ISD_NOTSCOTCHED;
		goto toyo2;
	    } else if (zeBall->iscotched == ISD_RIGHTSCOTCHED) {
	      stepon2:
		zeBall->x = raq2.x - zeBall->width;
		zeBall->y = raq2.y + zeBall->dontstop;
	    } else {
		if (INTERSECT(raq2.x, raq2.y, raq2.x + raq2.width,
			      raq2.y + raq2.height,
			      zeBall->x, zeBall->y,
			      zeBall->x + zeBall->width,
			      zeBall->y + zeBall->height) != 0) {
		    if (raq2.hasGlue != 0) {
			zeBall->iscotched = ISD_RIGHTSCOTCHED;
			raq2.iscotched = ISD_SCOTCHED;
			zeBall->dontstop = zeBall->y - raq2.y;
			goto stepon2;
		    }
		    if (sound_frappe_delay == 0) {
			sound_frappe_delay = SOUND_FRAPPE_DELAY;
			sound_frappe(MAX_VOLUME / 5, MAX_VOLUME);
		    }
		  toyo2:
#if CAN_PUSH_BALL
		    zeBall->x = raq2.x - zeBall->width;
#endif
		    if (flipper == 0) {
			const int mouchoir = abs(zeBall->addx);

			if (phasis == PHS_NORMAL) {
			    flipper = ACCELERATION_DELAY;
			} else {
			    flipper = LOW_ACCELERATION_DELAY;
			}
			if (mouchoir < MAX_BALLSPEED_X) {
			    zeBall->addx = -mouchoir - 1;
			}
		    } else {
			flipper--;
			zeBall->addx = -abs(zeBall->addx);
		    }
		    if (raq2.downspeed == DOD_DOWNSPEED) {
			zeBall->addx >>= DOWNSPEED_X;
			if (zeBall->addx == 0) {
			    zeBall->addx = -1;
			}
		    } else if (raq2.downspeed == DOD_UPSPEED) {
			zeBall->addx <<= DOWNSPEED_X;
			if ((-zeBall->addx) > FORCED_BALLSPEED_X) {
			    zeBall->addx = -FORCED_BALLSPEED_X;
			}
		    }
		    zeBall->addy = (zeBall->y +
				    ((zeBall->height - raq2.height) >> 1) -
				    raq2.y) >> raq2.acutance;
		}
	    }
	    if (zeBall->x < 0) {
		zeBall->x = 0;
		zeBall->addx = -zeBall->addx;
#if 1
		zeBall->enabled = 0;
		cahouette->enabled = 0;
		numberOfBalls--;
		if (numberOfBalls == 0) {
		    kikigo = KIKI_RIGHT;
		    return POE_LEFT;
		}
#endif
	    }
	    if (zeBall->x > (SCREEN_WIDTH - zeBall->width)) {
		zeBall->x = (SCREEN_WIDTH - zeBall->width);
		zeBall->addx = -zeBall->addx;
#if 1
		zeBall->enabled = 0;
		cahouette->enabled = 0;
		numberOfBalls--;
		if (numberOfBalls == 0) {
		    kikigo = KIKI_LEFT;
		    return POE_RIGHT;
		}
#endif
	    }
	    if (zeBall->y < 0) {
		const int jk =
		    zeBall->x * MAX_VOLUME / (SCREEN_WIDTH -
					      zeBall->width);

		if (zeBall->iscotched == ISD_NOTSCOTCHED) {
		    sound_boing(MAX_VOLUME - jk, jk);
		}
		zeBall->y = 0;
		zeBall->addy = -zeBall->addy;
	    }
	    if (zeBall->y > (SCREEN_HEIGHT - zeBall->height)) {
		const int jk =
		    zeBall->x * MAX_VOLUME / (SCREEN_WIDTH -
					      zeBall->width);

		if (zeBall->iscotched == ISD_NOTSCOTCHED) {
		    sound_boing(MAX_VOLUME - jk, jk);
		}
		zeBall->y = (SCREEN_HEIGHT - zeBall->height);
		zeBall->addy = -zeBall->addy;
	    }
	    kowabunga = screenOffset(zeBall->x, zeBall->y);
	    cahouette->enabled = 1;
	    cahouette->offset = kowabunga;
	    zeBall->addr = phybase + kowabunga;
	    cahouette->addr = zeBall->addr;
	    cahouette->oldLoadBall = zeBall->couple.load;

	    zeBall->couple.sprite(zeBall->addr, screenShift(zeBall->x));
	}
	cahouette++;
	zeBall++;
    }
    if (raq1.iscotched == ISD_DECOLE) {
	raq1.iscotched = ISD_NOTSCOTCHED;
    }
    if (raq2.iscotched == ISD_DECOLE) {
	raq2.iscotched = ISD_NOTSCOTCHED;
    }

    return POE_NONE;
}

static void loadBalls(void) RGONOP;
static void loadBalls(void)
{
    BallSave *california = curscreen->oldBall;
    BallSave *champignon;
    int t = MAXBALLS - 1;

    do {
	champignon = &california[t];
	if (champignon->enabled != 0) {
	    champignon->oldLoadBall(champignon->addr, champignon->offset);
	}
	t--;
    } while (t >= 0);
}

static __inline__ void slazer(const Raq * const raq) RGO;
static __inline__ void slazer(const Raq * const raq)
{
    const int jk = raq->x * MAX_VOLUME / (SCREEN_WIDTH - BONUS_WIDTH);
    sound_lazer(MAX_VOLUME - jk, jk);
}

static void action(Raq * const raq)
{
    if (raq->iscotched == ISD_SCOTCHED) {
	raq->iscotched = ISD_DECOLE;
	{
	    const int jk =
		raq->x * MAX_VOLUME / (SCREEN_WIDTH - raq->width);
	    sound_descotche(MAX_VOLUME - jk, jk);
	}
    } else if (raq->hasLazer != 0) {
	const int ygrec = raq->y + (raq->height >> 1);

	if (raq == &raq1) {
	    if (lazerWait1 == 0) {
		const int kowabunga =
		    screenOffset(raq1.x + raq1.width, ygrec);
		const int plonka = screenOffset(SCREEN_WIDTH - 1, ygrec);
		ptrdiff_t len;

		if ((len = (plonka - kowabunga)) > 0) {
		    unsigned char *const csa = phybase + kowabunga;

		    writePlane(WPLANE0 | WPLANE1 | WPLANE2 | WPLANE3);
		    memset(csa, LAZER_COLOR, (size_t) len);

		    curscreen->oldLazer.lazerAddr = csa;
		    curscreen->oldLazer.offset = kowabunga;
		    curscreen->oldLazer.lazerLen = (size_t) len;

		    lazerWait1 = LAZER_DELAY;

		    if (ygrec >= raq2.y && ygrec <= raq2.y + raq2.height) {
			isBlocked2 = LAZER_BLOCK;
			sound_glue();
		    } else {
			slazer(&raq1);
		    }
		}
	    }
	} else if (lazerWait2 == 0) {
	    const int kowabunga = screenOffset(raq2.x, ygrec);
	    const int plonka = screenOffset(0, ygrec);
	    ptrdiff_t len;

	    if ((len = (kowabunga - plonka)) > 0) {
		unsigned char *const csa = phybase + plonka;

		writePlane(WPLANE0 | WPLANE1 | WPLANE2 | WPLANE3);
		memset(csa, LAZER_COLOR, (size_t) len);

		curscreen->oldLazer.lazerAddr = csa;
		curscreen->oldLazer.offset = plonka;
		curscreen->oldLazer.lazerLen = (size_t) len;

		lazerWait2 = LAZER_DELAY;

		if (ygrec >= raq1.y && ygrec <= raq1.y + raq1.height) {
		    isBlocked1 = LAZER_BLOCK;
		    sound_glue();
		} else {
		    slazer(&raq2);
		}
	    }
	}
    }
}

static __inline__ void pause(void)
{
    static const unsigned char mimi[] = {
	KEY_E, KEY_M, KEY_I, KEY_L, KEY_I, KEY_E
    };
    const unsigned char *mimipnt = mimi;
    unsigned char key;

    sound_glue();
#ifndef __linux__
    while (key = keyget(), key == KEY_PAUSE);
    while (key = keyget(), key == KEY_RELEASE(KEY_PAUSE));
#else
    MikMod_Update();
    while (keyboard_keypressed(SCANCODE_P) != 0) {
	MikMod_Update();
	vsync();
	keyboard_update();
    }
#endif
    for (;;) {
	key = keyget();
	if (key == KEY_PAUSE) {
	    break;
	}
	if (key == *mimipnt) {
	    if (mimipnt == &mimi[(sizeof mimi) / (sizeof mimi[0]) - 1]) {
		sound_lazer(MAX_VOLUME, MAX_VOLUME);
		cheatMode = 1;
		break;
	    }
	    mimipnt++;
	}
#ifdef __linux__
	vsync();
	MikMod_Update();
#endif
    }
#ifndef __linux__
    while (key = keyget(), key != KEY_RELEASE(KEY_PAUSE));
#else
    while (keyboard_keypressed(SCANCODE_P) == 0) {
	MikMod_Update();
	vsync();
	keyboard_update();
    }
    while (keyboard_keypressed(SCANCODE_P) != 0) {
	MikMod_Update();
	vsync();
	keyboard_update();
    }
#endif
    sound_bip();
}

#define JMKRSTL 4

static void ia(void) RGONOP;
static void ia(void)
{
    static unsigned char gousto = 0;
    static unsigned char lr = 0;
    Ball *zeBall = &ball[0];
    int shake;

    while (zeBall->enabled == 0) {
	zeBall++;
    }
    if (zeBall->y < (raq2.y + JMKRSTL)) {
      mtv1:
	gousto = 1;
	goup2();
    } else if (zeBall->y > (raq2.y + raq2.height - JMKRSTL)) {
      mtv2:
	gousto = 2;
	godown2();
    } else if (gousto == 1) {
	goto mtv1;
    } else if (gousto == 2) {
	goto mtv2;
    }
    if ((zeBall->x + zeBall->width) > raq2.x) {
	lr = 2;
    } else if (((shake = rand()) & 31) == 0) {
	lr = shake % 3;
    }
    if (lr == 1) {
	goleft2();
    } else if (lr == 2) {
	goright2();
    }
}

int main(void)
{
    int kowabunga;
    unsigned char zetouch;
    int yoman;
    PointState ps;

    if (ioperm(0x200, 0x1ff, 1) != 0) {
	perror("ioperm");
	return 1;
    }
    init();

  rego:

    if (intro() != 0) {
	goto taratata;
    }

    initGame();
    resetNoBonus();
    sound_debut_match();
    aleasoundWait = (rand() % ALEASOUND_CHANCES);

  tareum:

    if (phasis != terrainPhasis) {
	if (phasis == PHS_BISOU) {
	    terrain2();
	} else {
	    terrain1();
	}
	terrainPhasis = phasis;
    }
    aleasoundWait += ALEASOUND_DELAY;

    dspScore();

    resetSpritesPos();
    isup1 = isdown1 = isleft1 = isright1 =
	isup2 = isdown2 = isleft2 = isright2 = 0;
    while (zetouch = keydeps(), zetouch != KEY_SPACE
	   && zetouch != KEY_RETURN) {
#if JOYSTICK_SUPPORT
	if (joy1 != 0 || joy2 != 0) {
	    poll_joystick();
	    if ((joy_b1 | joy_b2) != 0) {
		break;
	    }
	}
#endif
	if (zetouch == KEY_ESCAPE) {
	    goto taratata;
	}
	swapScreens();
	curscreen->oldLoadRaq1(curscreen->oldRaq1.addr,
			       curscreen->oldRaq1.offset);
	curscreen->oldLoadRaq2(curscreen->oldRaq2.addr,
			       curscreen->oldRaq2.offset);
	loadBalls();
#if BONI_SUPPORT
	loadRonds();
#endif
	kowabunga = screenOffset(raq1.x, raq1.y);
	curscreen->oldRaq1.offset = kowabunga;
	raq1.addr = phybase + kowabunga;
	curscreen->oldRaq1.addr = raq1.addr;
	curscreen->oldLoadRaq1 = raq1.couple.load;

	kowabunga = screenOffset(raq2.x, raq2.y);
	curscreen->oldRaq2.offset = kowabunga;
	raq2.addr = phybase + kowabunga;
	curscreen->oldRaq2.addr = raq2.addr;
	curscreen->oldLoadRaq2 = raq2.couple.load;

	bonusRond1.timeout = bonusRond2.timeout = BONUS_TIMEOUT;
	dspRond(&raq1, &curscreen->oldRond1);
	dspRond(&raq2, &curscreen->oldRond2);

	boingBoing();
	raq1.couple.sprite(raq1.addr, screenShift(raq1.x));
	raq2.couple.sprite(raq2.addr, screenShift(raq2.x));
    }

    if (phasis == PHS_BISOU) {
	sound_softzak();
    } else {
	sound_engagement();
    }

    {
	int t = numberOfBalls;
	Ball *twenty = ball;

	do {
	    if (kikigo == KIKI_LEFT) {
		twenty->addx = -INITIAL_BALLSPEED_X;
	    } else {
		twenty->addx = INITIAL_BALLSPEED_X;
	    }
	    twenty->addy =
		SERVICE_ACUTANCE - (rand() % (SERVICE_ACUTANCE * 2));
	    twenty++;
	    t--;
	} while (t != 0);
    }

#if 0
#if BONI_SUPPORT
    bonusWait = (rand() % BONUS_CHANCES);
#endif
#endif

    for (;;) {
	swapScreens();
	curscreen->oldLoadRaq1(curscreen->oldRaq1.addr,
			       curscreen->oldRaq1.offset);
	curscreen->oldLoadRaq2(curscreen->oldRaq2.addr,
			       curscreen->oldRaq2.offset);
	loadBalls();
#if BONI_SUPPORT
	loadRonds();
	loadBonus();
#endif

#if BONI_SUPPORT
	dspBonus();
#endif

#if JOYSTICK_SUPPORT
	if (joy1 != 0) {
	    isleft1 = isright1 = isup1 = isdown1 = 0;
	    poll_joystick();
	    if (joy_left != 0) {
		isleft1 = 1;
		isright1 = 0;
	    } else if (joy_right != 0) {
		isright1 = 1;
		isleft1 = 0;
	    }
	    if (joy_up != 0) {
		isup1 = 1;
		isdown1 = 0;
	    } else if (joy_down != 0) {
		isdown1 = 1;
		isup1 = 0;
	    }
	} else if (joy2 != 0) {
	    isleft2 = isright2 = isup2 = isdown2 = 0;
	    poll_joystick();
	    if (joy_left != 0) {
		isleft2 = 1;
		isright2 = 0;
	    } else if (joy_right != 0) {
		isright2 = 1;
		isleft2 = 0;
	    }
	    if (joy_up != 0) {
		isup2 = 1;
		isdown2 = 0;
	    } else if (joy_down != 0) {
		isdown2 = 1;
		isup2 = 0;
	    }
	}
#endif
	if (isBlocked1 == 0) {
	    if (isup1 != 0)
		goup1();
	    else if (isdown1 != 0)
		godown1();
	    if (isleft1 != 0)
		goleft1();
	    else if (isright1 != 0)
		goright1();
	}

	if (isBlocked2 == 0) {
	    if (simpleGame == 2) {
		ia();
	    } else {
		if (isup2 != 0)
		    goup2();
		else if (isdown2 != 0)
		    godown2();
		if (isleft2 != 0)
		    goleft2();
		else if (isright2 != 0)
		    goright2();
	    }
	}

	kowabunga = screenOffset(raq1.x, raq1.y);
	curscreen->oldRaq1.offset = kowabunga;
	raq1.addr = phybase + kowabunga;
	curscreen->oldRaq1.addr = raq1.addr;
	curscreen->oldLoadRaq1 = raq1.couple.load;

	kowabunga = screenOffset(raq2.x, raq2.y);
	curscreen->oldRaq2.offset = kowabunga;
	raq2.addr = phybase + kowabunga;
	curscreen->oldRaq2.addr = raq2.addr;
	curscreen->oldLoadRaq2 = raq2.couple.load;

	raq1.couple.sprite(raq1.addr, screenShift(raq1.x));
	raq2.couple.sprite(raq2.addr, screenShift(raq2.x));

	ps = boingBoing();
	if (ps == POE_LEFT) {
	    score2++;
	    break;
	} else if (ps == POE_RIGHT) {
	    score1++;
	    break;
	}

	switch ((zetouch = keydeps())) {
	case KEY_ESCAPE:
	    goto taratata;
	case KEY_SPACE:
	    action(&raq1);
	    break;
	case KEY_RETURN:
	    if (simpleGame != 2) {
		action(&raq2);
	    }
	    break;
	case KEY_PAUSE:
	    pause();
	}
#if JOYSTICK_SUPPORT
	if (joy1 != 0) {
	    if ((joy_b1 | joy_b2) != 0) {
		action(&raq1);
	    }
	} else if (joy2 != 0 && simpleGame != 2) {
	    if ((joy_b1 | joy_b2) != 0) {
		action(&raq2);
	    }
	}
#endif
	if (simpleGame == 2) {
	    if (raq2.hasLazer != 0) {
		const int muscu = raq1.y + (raq1.height >> 1);

		if (muscu > raq2.y && muscu < (raq2.y + raq2.height)) {
		    action(&raq2);
		}
	    } else if (raq2.hasGlue != 0 && (rand() % 31) == 0) {
		action(&raq2);
	    }
	}
    }
    if (abs(ball[0].addx) >= BALL_SPEED_FOR_CLAPS) {
	sound_clapclap();
    } else {
	if (ps == POE_LEFT) {
	    sound_avant_engagement(MAX_VOLUME, MAX_VOLUME / 8);
	} else {
	    sound_avant_engagement(MAX_VOLUME / 8, MAX_VOLUME);
	}
    }

    yoman = 2;
    do {
	swapScreens();
	curscreen->oldLoadRaq1(curscreen->oldRaq1.addr,
			       curscreen->oldRaq1.offset);
	curscreen->oldLoadRaq2(curscreen->oldRaq2.addr,
			       curscreen->oldRaq2.offset);
	loadBalls();
#if BONI_SUPPORT
	loadRonds();
	loadBonus();
#endif

	kowabunga = screenOffset(raq1.x, raq1.y);
	curscreen->oldRaq1.offset = kowabunga;
	raq1.addr = phybase + kowabunga;
	curscreen->oldRaq1.addr = raq1.addr;
	curscreen->oldLoadRaq1 = raq1.couple.load;

	kowabunga = screenOffset(raq2.x, raq2.y);
	curscreen->oldRaq2.offset = kowabunga;
	raq2.addr = phybase + kowabunga;
	curscreen->oldRaq2.addr = raq2.addr;
	curscreen->oldLoadRaq2 = raq2.couple.load;

	dspRond(&raq1, &curscreen->oldRond1);
	dspRond(&raq2, &curscreen->oldRond2);

	dspScore();
	boingBoing();
	raq1.couple.sprite(raq1.addr, screenShift(raq1.x));
	raq2.couple.sprite(raq2.addr, screenShift(raq2.x));
	yoman--;
    } while (yoman != 0);

    if (score1 == MAXPOINTS || score2 == MAXPOINTS) {
	goto endset;
    }

    if (requestedPhasis != phasis) {
	phasis = requestedPhasis;
	resetNoBonus();
	requestedPhasis = PHS_NORMAL;
    }


    goto tareum;

  endset:
#ifndef __linux__
    delayvbl(SOUNDENDMATCH_DELAY);
#else
    {
	int t = SOUNDENDMATCH_DELAY;
	do {
	    vsync();
	    MikMod_Update();
	    t--;
	} while (t != 0);
    }
#endif
    sound_endmatch();
    while (keyget() == KEY_RELEASE(KEY_SPACE));
#ifndef __linux__
    delayvbl(SOUNDENDMATCH_DELAY2);
#else
    {
	int t = SOUNDENDMATCH_DELAY2;
	do {
	    vsync();
	    MikMod_Update();
	    t--;
	} while (t != 0);
    }
#endif

    sound_bye();
    sfx_enabled = 0;
    goto rego;

  taratata:

    bye();

#ifndef __linux
    while (keyget() == KEY_SPACE);
    while (keyget() == KEY_ESCAPE);
#endif

#ifdef __linux__
    endmod();
#endif
    keyboard_close();

    return EXIT_SUCCESS;
}
