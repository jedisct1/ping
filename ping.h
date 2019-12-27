/* Jedi/Sector One */

#define NEED_ENVIRONMENT

#define BONI_SUPPORT 1
#define BIGBOOL_SUPPORT 0
#define ALLBONI_SUPPORT 0
#define JOYSTICK_SUPPORT 1

#define MAXBALLS 50

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#ifndef __linux__
# include <sys/nearptr.h>
# include <dpmi.h>
#endif

#include "rgo.h"
#include "xymode.h"
#include "sprites.h"
#include "palette.h"
#include "terrains.h"

#define SCREEN_MIDDLE (SCREEN_WIDTH / 2)
#define FILET_GAP 4
#define BONUS_WIDTH 24
#define BONUS_HEIGHT 24
#define BONUS_MOVE 8
#define ROND_WIDTH 20
#define ROND_HEIGHT 20

typedef struct BonusCouple_ {
    void (*sprite) (unsigned char *const where, const int deca);
    void (*load) (register unsigned char *where, const ptrdiff_t offset);
} BonusCouple;

typedef enum Iscotched_ {
    ISD_SCOTCHED, ISD_NOTSCOTCHED, ISD_DECOLE,
    ISD_LEFTSCOTCHED, ISD_RIGHTSCOTCHED
} Iscotched;

typedef enum BallSize_ {
    BAE_NORMAL, BAE_TINY, BAE_MIDDLE,
#if BIGBOOL_SUPPORT
    BAE_BIG,
#endif
    BAE_COEUR1, BAE_COEUR2, BAE_COEUR3, BAE_COEUR4,
    NUMBER_OF_COEURS = BAE_COEUR4 - BAE_COEUR1 + 1,
    NUMBER_OF_BALLKINDS = BAE_COEUR1
} BallSize;

typedef struct BallList_ {
    int width, height;
    BonusCouple couple;
} BallList;

typedef struct Ball_ {
    int enabled;
    unsigned char *addr;
    int x, y;
    int addx, addy;
    BallSize size;
    int width, height;
    BonusCouple couple;
#if BONI_SUPPORT
    Iscotched iscotched;
    int dontstop;
#endif
} Ball;

typedef struct SpriteSave_ {
    int enabled;
    unsigned char *addr;
    ptrdiff_t offset;
} SpriteSave;

typedef struct BallSave_ {
    int enabled;
    unsigned char *addr;
    ptrdiff_t offset;
    void (*oldLoadBall) (register unsigned char *where,
			 const ptrdiff_t offset);
} BallSave;

#if BONI_SUPPORT

typedef enum BonusType_ {
    BOE_MULTIBALL, BOE_BALLSIZE, BOE_RAQSIZE, BOE_RAQSPEED,
# if ALLBONI_SUPPORT
    BOE_INERTIE,
    BOE_WALL,
# endif
    BOE_GLUE, BOE_BALLWAY,
# if ALLBONI_SUPPORT
    BOE_GRAVITY,
# endif
    BOE_ANGLE, BOE_DOWNSPEED,
    BOE_TIR, BOE_NOLIMIT, BOE_SURPRISE,
    NUMBER_OF_BONI
} BonusType;

typedef enum BonusRecycler_ {
    BOR_KEEP, BOR_ONEPOINT, BOR_IMMED
} BonusRecycler;

#if 0
typedef enum BonusCumulative_ {
    BC_NOCUMULATIVE, BC_CUMULATIVE
} BonusCumulative;
#endif

typedef enum RaqType_ {
    RAE_NORMAL, RAE_BIG, RAE_HORIZONTAL,
    RAE_BISOU1, RAE_BISOU2,
    NUMBER_OF_RAQTYPES = RAE_BISOU1
} RaqType;

typedef struct RaqList_ {
    int width, height;
    BonusCouple couple;
} RaqList;

typedef struct Bonus_ {
    int enabled;
    BonusCouple couple;
    unsigned char *addr;
    int x, y;
    BonusType type;
} Bonus;

typedef struct BonusBack_ {
    unsigned char *addr;
    int x, y;
} BonusBack;

typedef struct BonusRond_ {
    int enabled;
    unsigned char *addr;
    BonusType type;
    Christelle *phasis;
    int timeout;
    int x, y;
} BonusRond;

typedef enum Downspeed_ {
    DOD_NORMAL, DOD_DOWNSPEED, DOD_UPSPEED
} Downspeed;

#endif

typedef struct Raq_ {
    unsigned char *addr;
    int x, y;
    int addx, addy;
    int width, height;
    int acutance;
    BonusCouple couple;
    RaqType type;
#if BONI_SUPPORT
    BonusRond *bonusRond;
    Iscotched iscotched;
    Downspeed downspeed;
    unsigned char hasGlue;
    unsigned char hasNoLimit;
    unsigned char hasLazer;
#endif
} Raq;

#if BONI_SUPPORT
typedef struct BonusList_ {
# if 0
    BonusType type;
# endif
    BonusRecycler recycler;
    BonusCouple couple;
    void (*enableBonus) (Raq * const raq);
    void (*disableBonus) (Raq * const raq);
# if 0
    BonusCumulative cumulative;
# endif
} BonusList;
#endif

typedef struct LazerSave_ {
    unsigned char *lazerAddr;
    ptrdiff_t offset;
    size_t lazerLen;
} LazerSave;

typedef struct Screen_ {
    BallSave oldBall[MAXBALLS];
    SpriteSave oldRaq1, oldRaq2;
    void (*oldLoadRaq1) (register unsigned char *where,
			 const ptrdiff_t offset);
    void (*oldLoadRaq2) (register unsigned char *where,
			 const ptrdiff_t offset);
#if BONI_SUPPORT
    SpriteSave oldBonus;
    SpriteSave oldBonusBack;
    SpriteSave oldRond1, oldRond2;
    LazerSave oldLazer;
#endif
} Screen;

typedef enum Phasis_ {
    PHS_NORMAL, PHS_BISOU
} Phasis;

#define HIPHOP(X) extern void enableBonus_##X(Raq * const raq); \
extern void disableBonus_##X(Raq * const raq)
#define HOPHIP(X) enableBonus_##X, disableBonus_##X
#define TITEL(X) { sprite_bonus##X, load_bonus##X }

HIPHOP(multiball);
HIPHOP(ballsize);
HIPHOP(raqsize);
HIPHOP(raqspeed);
#if ALLBONI_SUPPORT
HIPHOP(inertie);
HIPHOP(wall);
#endif
HIPHOP(glue);
HIPHOP(ballway);
#if ALLBONI_SUPPORT
HIPHOP(gravity);
#endif
HIPHOP(angle);
HIPHOP(downspeed);
HIPHOP(tir);
HIPHOP(nolimit);
HIPHOP(surprise);

#ifndef DEFINE_GLOBALS__
extern
#endif
const BonusList bonusList[]
#ifdef DEFINE_GLOBALS__
#define BT(X)
#define BU(X)
#define BtAnd
#define BuAnd
    = {
    {BT(BOE_MULTIBALL) BtAnd BOR_IMMED, TITEL(0),
     HOPHIP(multiball) BuAnd BU(BC_NOCUMULATIVE)},
    {BT(BOE_BALLSIZE) BtAnd BOR_IMMED, TITEL(1),
     HOPHIP(ballsize) BuAnd BU(BC_NOCUMULATIVE)},
    {BT(BOE_RAQSIZE) BtAnd BOR_KEEP, TITEL(2),
     HOPHIP(raqsize) BuAnd BU(BC_NOCUMULATIVE)},
    {BT(BOE_RAQSPEED) BtAnd BOR_KEEP, TITEL(3),
     HOPHIP(raqspeed) BuAnd BU(BC_CUMULATIVE)},
#if ALLBONI_SUPPORT
    {BT(BOE_INERTIE) BtAnd BOR_KEEP, TITEL(4),
     HOPHIP(inertie) BuAnd BU(BC_CUMULATIVE)},
    {BT(BOE_WALL) BtAnd BOR_KEEP, TITEL(5),
     HOPHIP(wall) BuAnd BU(BC_NOCUMULATIVE)},
#endif
    {BT(BOE_GLUE) BtAnd BOR_KEEP, TITEL(6),
     HOPHIP(glue) BuAnd BU(BC_CUMULATIVE)},
    {BT(BOE_BALLWAY) BtAnd BOR_IMMED, TITEL(7),
     HOPHIP(ballway) BuAnd BU(BC_CUMULATIVE)},
#if ALLBONI_SUPPORT
    {BT(BOE_GRAVITY) BtAnd BOR_KEEP, TITEL(8),
     HOPHIP(gravity) BuAnd BU(BC_NOCUMULATIVE)},
#endif
    {BT(BOE_ANGLE) BtAnd BOR_ONEPOINT, TITEL(9),
     HOPHIP(angle) BuAnd BU(BC_CUMULATIVE)},
    {BT(BOE_DOWNSPEED) BtAnd BOR_ONEPOINT, TITEL(10),
     HOPHIP(downspeed) BuAnd BU(BC_CUMULATIVE)},
    {BT(BOE_TIR) BtAnd BOR_KEEP, TITEL(11),
     HOPHIP(tir) BuAnd BU(BC_NOCUMULATIVE)},
    {BT(BOE_NOLIMIT) BtAnd BOR_KEEP, TITEL(12),
     HOPHIP(nolimit) BuAnd BU(BC_CUMULATIVE)},
    {BT(BOE_SURPRISE) BtAnd BOR_IMMED, TITEL(13),
     HOPHIP(surprise) BuAnd BU(BC_NOCUMULATIVE)}
}
#endif
;

#define BAYON(X1, Y1, X2, Y2) ((X2) - (X1) + 1), ((Y2) - (Y1) + 1)
#define BAYO(X) { sprite_##X, load_##X }

#ifndef DEFINE_GLOBALS__
extern
#endif
const RaqList raqList[]
#ifdef DEFINE_GLOBALS__
    = {
    { /*NORMAL*/ BAYON(12, 8, 19, 39), BAYO(normRaq)},
    { /*BIG*/ BAYON(20, 8, 27, 56), BAYO(bigRaq)},
    { /*HORI*/ BAYON(12, 0, 43, 7), BAYO(horiRaq)},
    { /*BISOU1 */ BAYON(227, 16, 269, 61), BAYO(bisou1)},
    { /*BISOU2 */ BAYON(271, 16, 313, 61), BAYO(bisou2)}
}
#endif
;

#ifndef DEFINE_GLOBALS__
extern
#endif
const BallList ballList[]
#ifdef DEFINE_GLOBALS__
    = {
    { /*NORMAL*/ BAYON(128, 0, 135, 7), BAYO(normBool)},
    { /*TINY*/ BAYON(136, 0, 137, 1), BAYO(tinyBool)},
    { /*MIDDLE*/ BAYON(108, 0, 127, 19), BAYO(midBool)},
# if BIGBOOL_SUPPORT
    { /*BIG*/ BAYON(44, 0, 107, 63), BAYO(bigBool)},
# endif
    { /*COEUR1 */ BAYON(85, 90, 91, 93), BAYO(coeur1)},
    { /*COEUR2 */ BAYON(102, 90, 110, 95), BAYO(coeur2)},
    { /*COEUR3 */ BAYON(120, 90, 130, 97), BAYO(coeur3)},
    { /*COEUR3 */ BAYON(84, 103, 98, 113), BAYO(coeur4)}
}
#endif
;

#ifndef DEFINE_GLOBALS__
extern
#endif
Screen screen[2];

#ifndef DEFINE_GLOBALS__
extern Screen *curscreen;
#else
Screen *curscreen = &screen[0];
#endif

#ifndef DEFINE_GLOBALS__
extern int curscrn;
#else
int curscrn = 0;
#endif

#ifndef DEFINE_GLOBALS__
extern
#endif
unsigned char *screenSave, *screenSave2;

#ifndef DEFINE_GLOBALS__
extern
#endif
Raq raq1, raq2;

#ifndef DEFINE_GLOBALS__
extern
#endif
Ball ball[MAXBALLS];

#ifndef DEFINE_GLOBALS__
extern
#endif
int numberOfBalls
#ifdef DEFINE_GLOBALS__
    = 1
#endif
    ;

#ifndef DEFINE_GLOBALS__
extern
#endif
int score1, score2;

#ifndef DEFINE_GLOBALS__
extern
#endif
Bonus bonus;

#ifndef DEFINE_GLOBALS__
extern
#endif
BonusBack bonusBack;

#ifndef DEFINE_GLOBALS__
extern
#endif
BonusRond bonusRond1, bonusRond2;

#ifndef DEFINE_GLOBALS__
extern
#endif
unsigned char cheatMode;

#ifndef DEFINE_GLOBALS__
extern
#endif
Phasis phasis
#ifdef DEFINE_GLOBALS__
    = PHS_NORMAL
#endif
    ;

#ifndef DEFINE_GLOBALS__
extern
#endif
Phasis terrainPhasis
#ifdef DEFINE_GLOBALS__
    = PHS_NORMAL
#endif
    ;

#ifndef DEFINE_GLOBALS__
extern
#endif
Phasis requestedPhasis
#ifdef DEFINE_GLOBALS__
    = PHS_NORMAL
#endif
    ;

#ifndef DEFINE_GLOBALS__
extern
#endif
unsigned char simpleGame;

#if JOYSTICK_SUPPORT
#ifndef DEFINE_GLOBALS__
extern
#endif
unsigned char joy1, joy2;
#endif
