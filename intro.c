/* Jedi/Sector One */

#define DEFINE_INTRO_GLOBALS__
#define MOD_END_BREAK 6
#ifndef __linux__
# define PONG_MOD "sounds\\a-pong1.mod"
#else
# define PONG_MOD "sounds/a-pong1.mod"
#endif

#include "ping.h"
#include "keyboard.h"
#include "bigping.h"
#include "miniping.h"
#include "fondu.h"
#include "crew.h"
#include "font.h"
#include "screxfnt.h"
#include "intro.h"
#include "mikjedi.h"
#include "txt.h"
#if JOYSTICK_SUPPORT
#include "joystick.h"
#endif
#ifdef __linux__
# include <string.h>
#endif

#ifdef __linux__
# include "sound/sound.h"
# define mp_sngpos getModulePos()
#endif

static unsigned char hasmod;
static unsigned char scrollit;
static unsigned char shortIntro;

static const int redhot[] = {
    WPLANE0, WPLANE1, WPLANE2, WPLANE3
};

static __inline__ void screx(void)
{
    static const unsigned char *scrextxtpnt = scrextxt;
    static const unsigned char *screxfntpnt = screxfnt;
    static unsigned char scrbuf[SCREEN_WIDTH * SCREXFNT_HEIGHT];
    static unsigned char txtphasis;
    static int z;

    if (scrollit == 0) {
	return;
    }

    memmove(scrbuf, scrbuf + 2, SCREEN_WIDTH * SCREXFNT_HEIGHT - 2);

    if (txtphasis == 0) {
	txtphasis = (SCREXFNT_WIDTH / 2) - 1;
	if ((z = *scrextxtpnt) == STOPCAR) {
	    z = *(scrextxtpnt = scrextxt);
	}
	scrextxtpnt++;
	screxfntpnt = screxfnt + (z * SCREXFNT_ONECAR);
    } else {
	txtphasis--;
	screxfntpnt += (SCREXFNT_HEIGHT * 2);
    }

    *((unsigned short *) (scrbuf + (SCREEN_WIDTH * 1 - 2))) =
	*((const unsigned short *) (screxfntpnt));
    *((unsigned short *) (scrbuf + (SCREEN_WIDTH * 2 - 2))) =
	*((const unsigned short *) (screxfntpnt + 2));
    *((unsigned short *) (scrbuf + (SCREEN_WIDTH * 3 - 2))) =
	*((const unsigned short *) (screxfntpnt + 4));
    *((unsigned short *) (scrbuf + (SCREEN_WIDTH * 4 - 2))) =
	*((const unsigned short *) (screxfntpnt + 6));
    *((unsigned short *) (scrbuf + (SCREEN_WIDTH * 5 - 2))) =
	*((const unsigned short *) (screxfntpnt + 8));
    *((unsigned short *) (scrbuf + (SCREEN_WIDTH * 6 - 2))) =
	*((const unsigned short *) (screxfntpnt + 10));
    *((unsigned short *) (scrbuf + (SCREEN_WIDTH * 7 - 2))) =
	*((const unsigned short *) (screxfntpnt + 12));
    *((unsigned short *) (scrbuf + (SCREEN_WIDTH * 8 - 2))) =
	*((const unsigned short *) (screxfntpnt + 14));

    {
#define MEDLEY (SCREEN_WIDTH_IN_BYTES * (SCREEN_HEIGHT - SCREXFNT_HEIGHT))

	register unsigned char *arg = screenSave + MEDLEY;
	register unsigned char *arg2 = phybase + MEDLEY;
	register unsigned char *scrbufPnt = scrbuf;
	int t;

	writePlane(WPLANE0);
	t = SCREEN_WIDTH * SCREXFNT_HEIGHT / 4;
	do {
	    *arg2 = *arg = *scrbufPnt;
	    arg++;
	    arg2++;
	    scrbufPnt += 4;
	    t--;
	} while (t != 0);

	scrbufPnt = scrbuf + 1;
	arg = screenSave + SCREEN_LENGTH_IN_BYTES + MEDLEY;
	arg2 = phybase + MEDLEY;
	writePlane(WPLANE1);
	t = SCREEN_WIDTH * SCREXFNT_HEIGHT / 4;
	do {
	    *arg2 = *arg = *scrbufPnt;
	    arg++;
	    arg2++;
	    scrbufPnt += 4;
	    t--;
	} while (t != 0);

	scrbufPnt = scrbuf + 2;
	arg = screenSave + SCREEN_LENGTH_IN_BYTES * 2 + MEDLEY;
	arg2 = phybase + MEDLEY;
	writePlane(WPLANE2);
	t = SCREEN_WIDTH * SCREXFNT_HEIGHT / 4;
	do {
	    *arg2 = *arg = *scrbufPnt;
	    arg++;
	    arg2++;
	    scrbufPnt += 4;
	    t--;
	} while (t != 0);

	scrbufPnt = scrbuf + 3;
	arg = screenSave + SCREEN_LENGTH_IN_BYTES * 3 + MEDLEY;
	arg2 = phybase + MEDLEY;
	writePlane(WPLANE3);
	t = SCREEN_WIDTH * SCREXFNT_HEIGHT / 4;
	do {
	    *arg2 = *arg = *scrbufPnt;
	    arg++;
	    arg2++;
	    scrbufPnt += 4;
	    t--;
	} while (t != 0);

#if 0
	memcpy(screenSave2 + MEDLEY, screenSave + MEDLEY,
	       SCREEN_WIDTH * SCREXFNT_HEIGHT / 4);
	memcpy(screenSave2 + SCREEN_LENGTH_IN_BYTES + MEDLEY,
	       screenSave + SCREEN_LENGTH_IN_BYTES + MEDLEY,
	       SCREEN_WIDTH * SCREXFNT_HEIGHT / 4);
	memcpy(screenSave2 + SCREEN_LENGTH_IN_BYTES * 2 + MEDLEY,
	       screenSave + SCREEN_LENGTH_IN_BYTES * 2 + MEDLEY,
	       SCREEN_WIDTH * SCREXFNT_HEIGHT / 4);
	memcpy(screenSave2 + SCREEN_LENGTH_IN_BYTES * 3 + MEDLEY,
	       screenSave + SCREEN_LENGTH_IN_BYTES * 3 + MEDLEY,
	       SCREEN_WIDTH * SCREXFNT_HEIGHT / 4);
#endif
    }
}

static void dspCar(const int car, const ptrdiff_t offset) RGO;
static void dspCar(const int car, const ptrdiff_t offset)
{
    const unsigned char *ophelie = font + car * (FONT_WIDTH * FONT_HEIGHT);
    signed char x, y, z = 3;

    do {
	x = (FONT_WIDTH / 4) - 1;
	do {
	    y = (FONT_HEIGHT - 1);
	    do {
		screenSave2[offset + x + y * SCREEN_WIDTH_IN_BYTES +
			    z * SCREEN_LENGTH_IN_BYTES] = *ophelie;
		ophelie++;
		y--;
	    } while (y >= 0);
	    x--;
	} while (x >= 0);
	z--;
    } while (z >= 0);
}

static void dspTxt(const unsigned char *epicier, const int x,
		   const int y) RGO;
static void dspTxt(const unsigned char *epicier, const int x, const int y)
{
    ptrdiff_t offset = y *
	(SCREEN_WIDTH_IN_BYTES * (FONT_HEIGHT + FONT_YSPACE)) + (x << 1);
    int car;

    while ((car = *epicier) != STOPCAR) {
	dspCar(car, offset);
	offset += (FONT_WIDTH / 4);
	epicier++;
    }
}

static __inline__ size_t funnystrlen(const unsigned char *const patouch)
    RGOPERATOR;
static __inline__ size_t funnystrlen(const unsigned char *const patouch)
{
    register const unsigned char *wouala = patouch;

    while (*wouala != STOPCAR) {
	wouala++;
    }

    return (size_t) (wouala - patouch);
}

static __inline__ void centerTxt(const unsigned char *boulanger,
				 const int y) RGO;
static __inline__ void centerTxt(const unsigned char *boulanger,
				 const int y)
{
    dspTxt(boulanger, (SCREEN_WIDTH >> 4) - funnystrlen(boulanger), y);
}

static void dspArrows(const int y) RGO;
static void dspArrows(const int y)
{
    const ptrdiff_t offset = y *
	((FONT_HEIGHT + FONT_YSPACE) * SCREEN_WIDTH_IN_BYTES);

    dspCar(RIGHTARROW_IN_FONT, offset);
    dspCar(LEFTARROW_IN_FONT, offset + ((SCREEN_WIDTH - FONT_WIDTH) / 4));
}

static void clrArrows(const int y) RGO;
static void clrArrows(const int y)
{
    const ptrdiff_t offset = y *
	((FONT_HEIGHT + FONT_YSPACE) * SCREEN_WIDTH_IN_BYTES);

    dspCar(SPACE_IN_FONT, offset);
    dspCar(SPACE_IN_FONT, offset + ((SCREEN_WIDTH - FONT_WIDTH) / 4));
}

static void clrPart(void) RGONOP;
static void clrPart(void)
{
    memset(screenSave2 + (MINIPING_HEIGHT * SCREEN_WIDTH_IN_BYTES),
	   0, (SCREEN_HEIGHT - MINIPING_HEIGHT) * SCREEN_WIDTH_IN_BYTES);
    memset(screenSave2 + (MINIPING_HEIGHT * SCREEN_WIDTH_IN_BYTES) +
	   SCREEN_LENGTH_IN_BYTES, 0,
	   (SCREEN_HEIGHT - MINIPING_HEIGHT) * SCREEN_WIDTH_IN_BYTES);
    memset(screenSave2 + (MINIPING_HEIGHT * SCREEN_WIDTH_IN_BYTES) +
	   SCREEN_LENGTH_IN_BYTES * 2, 0,
	   (SCREEN_HEIGHT - MINIPING_HEIGHT) * SCREEN_WIDTH_IN_BYTES);
    memset(screenSave2 + (MINIPING_HEIGHT * SCREEN_WIDTH_IN_BYTES) +
	   SCREEN_LENGTH_IN_BYTES * 3, 0,
	   (SCREEN_HEIGHT - MINIPING_HEIGHT) * SCREEN_WIDTH_IN_BYTES);
    MD_Update();
}

static void swapScreens(void) RGONOP;
static void swapScreens(void)
{
    MD_Update();
    vsync();
    curscrn ^= 1;
    setPage(curscrn);
    curscreen = &screen[curscrn];

    screx();
}

static void loadBulles(void) RGONOP;
static void loadBulles(void)
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

static __inline__ void initBulles(void)
{
    const BulleList *flip;
    Ball *epinard = ball;
    int t = MAXBALLS;

    numberOfBalls = 1;

    do {
	epinard->enabled = 1;
	epinard->addx = (rand() % 4) - 2;
	epinard->addy = -(rand() & 1) - 1;
	epinard->size = t % NUMBER_OF_BULLES;
	flip = &bulleList[epinard->size];

	epinard->width = flip->width;
	epinard->height = flip->height;
	epinard->couple.load = flip->couple.load;
	epinard->couple.sprite = flip->couple.sprite;

	epinard->x = (rand() % (SCREEN_WIDTH - epinard->width));
	epinard->y = SCREEN_HEIGHT;
	epinard->addr = phybase + screenOffset(epinard->x, epinard->y);

	epinard++;
	t--;
    } while (t != 0);
}

static void moveBulles(void) RGONOP;
static void moveBulles(void)
{
    BallSave *cahouette = curscreen->oldBall;
    Ball *zeBall = ball;
    int t = numberOfBalls;
    int kowabunga;

    while (t != 0) {
	if (zeBall->enabled != 0) {
	    t--;

	    zeBall->x += zeBall->addx;
	    zeBall->y += zeBall->addy;

	    if (zeBall->x < 0) {
		zeBall->x = 0;
		zeBall->addx = (rand() & 3) + 1;
	    }
	    if (zeBall->x > (SCREEN_WIDTH - zeBall->width)) {
		zeBall->x = (SCREEN_WIDTH - zeBall->width);
		zeBall->addx = -(rand() & 3) - 1;
	    }
	    if (zeBall->y < 0) {
		zeBall->y = 0;
		zeBall->addy = (rand() & 3) + 1;
	    }
	    if (zeBall->y > (SCREEN_HEIGHT - zeBall->height)) {
		zeBall->y = (SCREEN_HEIGHT - zeBall->height);
		zeBall->addy = -(rand() & 3) - 1;
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

    zeBall = &ball[rand() % MAXBALLS];
    zeBall->x = (rand() % (SCREEN_WIDTH - zeBall->width));
    zeBall->y = SCREEN_HEIGHT;
    zeBall->addy = -(rand() & 3) - 1;

    if (numberOfBalls != MAXBALLS && (zeBall->x & 15) == 0) {
	numberOfBalls++;
    }
}

static __inline__ void dspMiniPing(void)
{
    memset(screenSave2, 0, SCREEN_LENGTH_IN_BYTES * 4);
    MD_Update();
    memcpy(screenSave2, miniPing, MINIPING_ONEPLANE);
    memcpy(screenSave2 + SCREEN_LENGTH_IN_BYTES,
	   miniPing + MINIPING_ONEPLANE, MINIPING_ONEPLANE);
    memcpy(screenSave2 + SCREEN_LENGTH_IN_BYTES * 2,
	   miniPing + MINIPING_ONEPLANE * 2, MINIPING_ONEPLANE);
    memcpy(screenSave2 + SCREEN_LENGTH_IN_BYTES * 3,
	   miniPing + MINIPING_ONEPLANE * 3, MINIPING_ONEPLANE);
}

#define BIGPING_DOWN (((SCREEN_HEIGHT - 200) / 2) * SCREEN_WIDTH_IN_BYTES)

static __inline__ void dspBigPing(void)
{
    unsigned char *const screenSave_ = screenSave + BIGPING_DOWN;

    memcpy(screenSave_, bigPing, BIGPING_ONEPLANE);
    memcpy(screenSave_ + SCREEN_LENGTH_IN_BYTES,
	   bigPing + BIGPING_ONEPLANE, BIGPING_ONEPLANE);
    memcpy(screenSave_ + SCREEN_LENGTH_IN_BYTES * 2,
	   bigPing + BIGPING_ONEPLANE * 2, BIGPING_ONEPLANE);
    memcpy(screenSave_ + SCREEN_LENGTH_IN_BYTES * 3,
	   bigPing + BIGPING_ONEPLANE * 3, BIGPING_ONEPLANE);

    MD_Update();
    xsput(screenSave, 0);
    MD_Update();
    memcpy(screenSave2, screenSave, SCREEN_LENGTH_IN_BYTES * 4);
    MD_Update();
    copyPage(0, 1);
}

#define FADE_HEIGHT 16

static void fade(const unsigned char yabul, const int youhou_) RGO;
static void fade(const unsigned char yabul, const int youhou_)
{
    const unsigned short *fondupnt = fondu;
    int youhou;
    int plane;
    ptrdiff_t offset, offset2;
    unsigned short soul;
    int love;

    for (;;) {
	swapScreens();
	if (yabul != 0) {
	    loadBulles();
	}
	youhou = youhou_;
	do {
	    if ((soul = *fondupnt) == 65535) {
		goto blablabla;
	    }
	    plane = soul & 3;
	    offset = soul >> 4;
	    offset2 = offset + plane * SCREEN_LENGTH_IN_BYTES;
	    writePlane(redhot[plane]);
	    love = 15 - 1;
	    for (;;) {
		logbase[offset] = phybase[offset] = screenSave[offset2] =
		    screenSave2[offset2];
		love--;
		if (love == 0) {
		    break;
		}
		offset += (SCREEN_WIDTH_IN_BYTES * FADE_HEIGHT);
		offset2 += (SCREEN_WIDTH_IN_BYTES * FADE_HEIGHT);
	    }
	    fondupnt++;
	    youhou--;
	} while (youhou != 0);
	if (yabul != 0) {
	    moveBulles();
	}
    }
  blablabla:
    if (yabul != 0) {
	moveBulles();
    }
}

#define CREW1_DOWN (((SCREEN_HEIGHT - CREW1_HEIGHT) / 2) * SCREEN_WIDTH_IN_BYTES)
#define CREW2_DOWN (((SCREEN_HEIGHT - CREW2_HEIGHT) / 2) * SCREEN_WIDTH_IN_BYTES)

static __inline__ void logocrew(void)
{
    unsigned char *screenSave2_ = screenSave2 + CREW1_DOWN;

    memset(screenSave, 0, SCREEN_LENGTH_IN_BYTES * 4);
    memset(screenSave2, 0, SCREEN_LENGTH_IN_BYTES * 4);

    memcpy(screenSave2_, crew1, CREW1_ONEPLANE);
    memcpy(screenSave2_ + SCREEN_LENGTH_IN_BYTES, crew1 + CREW1_ONEPLANE,
	   CREW1_ONEPLANE);
    memcpy(screenSave2_ + SCREEN_LENGTH_IN_BYTES * 2,
	   crew1 + CREW1_ONEPLANE * 2, CREW1_ONEPLANE);
    memcpy(screenSave2_ + SCREEN_LENGTH_IN_BYTES * 3,
	   crew1 + CREW1_ONEPLANE * 3, CREW1_ONEPLANE);

    setpalcrew();
    fade(0, NORMAL_FADE);

    screenSave2_ = screenSave2 + CREW2_DOWN;
    memset(screenSave2, 0, SCREEN_LENGTH_IN_BYTES * 4);

    memcpy(screenSave2_, crew2, CREW2_ONEPLANE);
    memcpy(screenSave2_ + SCREEN_LENGTH_IN_BYTES, crew2 + CREW2_ONEPLANE,
	   CREW2_ONEPLANE);
    memcpy(screenSave2_ + SCREEN_LENGTH_IN_BYTES * 2,
	   crew2 + CREW2_ONEPLANE * 2, CREW2_ONEPLANE);
    memcpy(screenSave2_ + SCREEN_LENGTH_IN_BYTES * 3,
	   crew2 + CREW2_ONEPLANE * 3, CREW2_ONEPLANE);

    fade(0, NORMAL_FADE);

    if (mp_sngpos != 0) {
	MD_Update();
	do {
	    vsync();
	    MD_Update();
	} while (mp_sngpos < MOD_END_BREAK);
    }
}

#define BIGPING_DELAY (50 * 4)

unsigned char intro(void)
{
    int yar;
    int ymin, ymax;
    int t;
    MenuKind menuKind;
    unsigned char zetouch, oldtouch;
#if JOYSTICK_SUPPORT
    unsigned char *joy = NULL;
#endif

    hasmod = startmod(PONG_MOD);

    if (shortIntro == 0) {
	vsync();
	setblack();
	xmode();
	setblack();
	phybase = getphybase(1);
	xclear(phybase);
	phybase = getphybase(0);
	xclear(phybase);
	vsync();
	setPage(0);
	vsync();

	MD_Update();
	logocrew();
	MD_Update();
    }

    vsync();
    setblack();
    MD_Update();
    phybase = getphybase(1);
    xclear(phybase);
    MD_Update();
    phybase = getphybase(0);
    xclear(phybase);
    vsync();
    MD_Update();
    setPage(0);
    vsync();

    if (shortIntro == 0) {
	dspBigPing();
    } else {
	memset(screenSave, 0, SCREEN_LENGTH_IN_BYTES * 4);
	MD_Update();
	memset(screenSave2, 0, SCREEN_LENGTH_IN_BYTES * 4);
    }
    MD_Update();
    dspMiniPing();
    MD_Update();

    initBulles();
    MD_Update();

    vsync();
    setpal();
    MD_Update();

    scrollit = 1;

    if (shortIntro == 0) {
	t = BIGPING_DELAY;
	do {
	    swapScreens();
	    loadBulles();
	    moveBulles();
	    t--;
	} while (t != 0);

	shortIntro = 1;
    }

    fade(1, NORMAL_FADE);

    oldtouch = keyget();

  biscotte0:

    menuKind = MED_MAIN;
    yar = MENU1_YMIN;
    ymin = MENU1_YMIN;
    ymax = MENU1_YMAX;

  biscotte:

    {
	const int y = MENU1_YMIN;

	centerTxt(page1, y);
	centerTxt(page2, y + 1);
	centerTxt(page3, y + 2);
	centerTxt(page4, y + 3);
	centerTxt(page5, y + 4);
	centerTxt(page6, y + 5);
    }

  blowmymind:

    dspArrows(yar);

    fade(1, SPEEDY_FADE);

  hiphop:

    for (;;) {
	swapScreens();
	loadBulles();
	moveBulles();
	zetouch = keyget();
	if (zetouch != oldtouch) {
	    oldtouch = zetouch;
	    switch (zetouch) {
	    case KEY_RELEASE(KEY_SPACE):
		goto coeur;
	    case 0xd0:
		clrArrows(yar);
		if (yar == ymax) {
		    yar = ymin;
		} else {
		    yar++;
		}
		dspArrows(yar);
		fade(1, SPEEDY_FADE);
		break;
	    case 0xc8:
		clrArrows(yar);
		if (yar == ymin) {
		    yar = ymax;
		} else {
		    yar--;
		}
		dspArrows(yar);
		fade(1, SPEEDY_FADE);
	    }
	}
    }
  coeur:

    if (menuKind == MED_MAIN) {
	switch (yar) {
	case MENU1_REALPING:
	    simpleGame = 0;
	    goto magda;
	case MENU1_NORMALPONG:
	    simpleGame = 1;
	    goto magda;
	case MENU1_SOLITARYPING:
	    simpleGame = 2;
	    goto magda;
	case MENU1_EXIT:
	    if (hasmod == 0) {
		endmod();
	    }
	    return 1;
	case MENU1_INFO:
	    {
		clrPart();
		swapScreens();
		loadBulles();
		moveBulles();
		{
		    const int y = MENUINF_YMIN;

		    centerTxt(info1, y);
		    centerTxt(info2, y + 1);
		    centerTxt(info3, y + 2);
		    centerTxt(info4, y + 3);
		}
		fade(1, SPEEDY_FADE);

		for (;;) {
		    swapScreens();
		    loadBulles();
		    moveBulles();
		    zetouch = keyget();
		    if (zetouch != oldtouch) {
			oldtouch = zetouch;
			if (zetouch == KEY_RELEASE(KEY_SPACE)) {
			    break;
			}
		    }
		}
		clrPart();
		swapScreens();
		loadBulles();
		moveBulles();
	    }
	    break;
	case MENU1_CONFIG:
	    {
	      degdegdeg:
		clrPart();
		swapScreens();
		loadBulles();
		moveBulles();
		{
		    const int y = MENUCFG_YMIN;

		    centerTxt(cfg1, y);
		    centerTxt(cfg2, y + 1);
		    centerTxt(cfg3, y + 2);
		}
		menuKind = MED_CFG;
		yar = ymin = MENUCFG_YMIN;
		ymax = MENUCFG_YMAX;
		goto blowmymind;
	    }
	}
	goto biscotte;
    } else if (menuKind == MED_CFG) {
	clrPart();
	swapScreens();
	loadBulles();
	moveBulles();
	switch (yar) {
	case MENUCFG_LEFT:
#if JOYSTICK_SUPPORT
	    joy = &joy1;
#endif
	  chuimalheureux:
	    {
		const int y = MENUCTRL_YMIN;

		centerTxt(ctrl1, y);
		centerTxt(ctrl2, y + 1);
		centerTxt(ctrl3, y + 2);
	    }
	    menuKind = MED_CTRL;
	    yar = ymin = MENUCTRL_YMIN;
	    ymax = MENUCTRL_YMAX;
	    goto blowmymind;
	    break;
	case MENUCFG_RIGHT:
#if JOYSTICK_SUPPORT
	    joy = &joy2;
#endif
	    goto chuimalheureux;
	    break;
	default:
	    goto biscotte0;
	}
    } else if (menuKind == MED_CTRL) {
#if JOYSTICK_SUPPORT
	switch (yar) {
	case MENUCTRL_KEYBOARD:
	    *joy = 0;
	    break;

	case MENUCTRL_JOYSTICK:
	    *joy = 1;
	    {
		clrPart();
		swapScreens();
		loadBulles();
		moveBulles();

		initialise_joystick();

		{
		    const int y = MENUCALIBRATE_YMIN;

		    centerTxt(cal11, y);
		    centerTxt(cal12, y + 1);
		    centerTxt(cal13, y + 2);
		    centerTxt(cal14, y + 3);
		    centerTxt(cal15, y + 4);
		}
		fade(1, SPEEDY_FADE);

		for (;;) {
		    swapScreens();
		    loadBulles();
		    moveBulles();
		    zetouch = keyget();
		    if (zetouch != oldtouch) {
			oldtouch = zetouch;
			if (zetouch == KEY_RELEASE(KEY_SPACE)) {
			    break;
			}
		    }
		}
		calibrate_joystick_tl();
		clrPart();
		swapScreens();
		loadBulles();
		moveBulles();

		{
		    const int y = MENUCALIBRATE_YMIN;

		    centerTxt(cal21, y);
		    centerTxt(cal22, y + 1);
		    centerTxt(cal23, y + 2);
		    centerTxt(cal24, y + 3);
		    centerTxt(cal25, y + 4);
		}
		fade(1, SPEEDY_FADE);

		for (;;) {
		    swapScreens();
		    loadBulles();
		    moveBulles();
		    zetouch = keyget();
		    if (zetouch != oldtouch) {
			oldtouch = zetouch;
			if (zetouch == KEY_RELEASE(KEY_SPACE)) {
			    break;
			}
		    }
		}
		calibrate_joystick_br();
	    }
	    break;

	case MENUCTRL_HAPPYSTICK:
	    centerTxt(nohappy, NOSTICK_YMIN);
	    fade(1, SPEEDY_FADE);
	    goto hiphop;
	}
#endif
	goto degdegdeg;
    }

  magda:
    if (hasmod == 0) {
	endmod();
    }
    vsync();

    return 0;
}
