/* Jedi/Sector One */

#define STOPCAR 255
#define FONT_YSPACE 2

#define NORMAL_FADE 16
#define SPEEDY_FADE 128

#define MENU1_YMIN 6
#define MENU1_REALPING MENU1_YMIN
#define MENU1_NORMALPONG (MENU1_REALPING + 1)
#define MENU1_SOLITARYPING (MENU1_NORMALPONG + 1)
#define MENU1_INFO (MENU1_SOLITARYPING + 1)
#define MENU1_EXIT (MENU1_INFO + 1)
#define MENU1_CONFIG (MENU1_EXIT + 1)
#define MENU1_YMAX MENU1_CONFIG

#define MENUINF_YMIN 7

#define MENUCFG_YMIN 7
#define MENUCFG_LEFT MENUCFG_YMIN
#define MENUCFG_RIGHT (MENUCFG_LEFT + 1)
#define MENUCFG_BACK (MENUCFG_RIGHT + 1)
#define MENUCFG_YMAX MENUCFG_BACK

#define MENUCTRL_YMIN 7
#define MENUCTRL_KEYBOARD MENUCTRL_YMIN
#define MENUCTRL_JOYSTICK (MENUCTRL_KEYBOARD + 1)
#define MENUCTRL_HAPPYSTICK (MENUCTRL_JOYSTICK + 1)
#define MENUCTRL_YMAX MENUCTRL_HAPPYSTICK

#define MENUCALIBRATE_YMIN 7

#define NOSTICK_YMIN 11

#ifdef DEFINE_INTRO_GLOBALS__

typedef enum MenuKind_ {
    MED_MAIN, MED_CFG, MED_CTRL
} MenuKind;

typedef enum BulleSize_ {
    BUE_1, BUE_2, BUE_3, NUMBER_OF_BULLES
} BulleSize;

typedef struct BulleList_ {
    int width, height;
    BonusCouple couple;
} BulleList;

static const BulleList bulleList[] = {
    { /*BULLE1 */ BAYON(230, 1, 242, 13), BAYO(bulle1)},
    { /*BULLE2 */ BAYON(249, 4, 257, 12), BAYO(bulle2)},
    { /*BULLE3 */ BAYON(265, 5, 271, 11), BAYO(bulle3)}
};

#endif

extern unsigned char intro(void) RGONOP;
