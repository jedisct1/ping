/* Jedi/Sector One */

#define DEFINE_GLOBALS__
#define NEED_TRADITIONAL_NEARPTR 0
#define DISABLE_INTERRUPTS 1

#define SHOW_VBL 0
#define FUNNY_POS 0
#define FUNNY_SPEED 0
#define CAN_PUSH_BALL 1
#define ACCELERATION_DELAY 42
#define LOW_ACCELERATION_DELAY 64
#define ACUTANCE 2
#define HIGH_ACUTANCE 1
#define LOW_ACUTANCE 3
#define SERVICE_ACUTANCE (24 / (ACUTANCE * 2))
#define INITIAL_RAQSPEED_X 4
#define INITIAL_RAQSPEED_Y 4
#define BOOSTED_RAQSPEED_X 6
#define BOOSTED_RAQSPEED_Y 6
#define IA_RAQSPEED_X 5
#define IA_RAQSPEED_Y 5
#define INITIAL_BALLSPEED_X 2
#define INITIAL_BALLSPEED_Y 1
#define MAX_BALLSPEED_X 8
#define FORCED_BALLSPEED_X (MAX_BALLSPEED_X / 2)
#define NEW_BALLSPEED_X 8
#define NEW_BALLSPEED_Y 4
#define BALL_SPEED_FOR_CLAPS (MAX_BALLSPEED_X / 2)
#define SOUND_FRAPPE_DELAY 12
#define NOLIMIT_GAP 120
#define RAQMOVE_GAP 4

#define MAXPOINTS 15

#define BONUS_CHANCES (1024*0+320)
#define BONUS_MINWAIT 64
#define BONUS_TIMEOUT 30
#define ALEASOUND_CHANCES 1280
#define ALEASOUND_DELAY 256

#define DOWNSPEED_X 1

#define ROND_XGAP 8
#define ROND_YGAP ROND_XGAP
#define ROND_Y (SCREEN_HEIGHT - ROND_HEIGHT - ROND_YGAP)
#define ROND_XL ROND_XGAP
#define ROND_XR (SCREEN_WIDTH - ROND_WIDTH - ROND_XGAP)

#define LAZER_COLOR 38
#define LAZER_DELAY 128
#define LAZER_BLOCK 42

#define SOUNDENDMATCH_DELAY 80
#define SOUNDENDMATCH_DELAY2 160

#if NEED_TRADITIONAL_NEARPTR == 0
#include "crt0init.h"
#endif
#ifndef __linux__
# include <sys/segments.h>
#endif
#include "ping.h"
#include "keyboard.h"
#include "score.h"
#include "intersec.h"
#include "sound/sound.h"
#if JOYSTICK_SUPPORT
#include "joystick.h"
#endif
#include "irq.h"
#include "intro.h"
#include <time.h>

#define KIKI_LEFT 0
#define KIKI_RIGHT 1
static unsigned char kikigo = KIKI_LEFT;

#define INTERRUPT_KEY 9
static unsigned char irq_redirected;
#ifndef __linux__
static __dpmi_paddr shitMaker;
#endif

static int sound_frappe_delay;

#if BONI_SUPPORT
static int bonusWait;
static int aleasoundWait;
static int lazerWait1, lazerWait2;
static int isBlocked1, isBlocked2;
#endif

static unsigned char sfx_enabled;
