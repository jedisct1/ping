/* Jedi/Sector One */

#ifndef __linux__
# include <pc.h>
#else
# include <vgakeyboard.h>
#endif

static int isup1, isdown1, isleft1, isright1,
    isup2, isdown2, isleft2, isright2;

enum {
    KEY_ESCAPE = 129,
    KEY_SPACE = 57,
    KEY_RETURN = 28,
    KEY_P = 25,
    KEY_PAUSE = KEY_P,
    KEY_I = 23,
    KEY_E = 18,
    KEY_L = 38,
    KEY_M = 39
};

#ifndef __linux__
#define KEY_RELEASE(X) ((X) | 128)
#else
#define KEY_RELEASE(X) (X)
#endif

#ifndef __linux__

extern __inline__ unsigned char keyget(void)
{
    return inportb(0x60U);
}

extern __inline__ unsigned char keydeps(void)
{
    unsigned char got;

    do {
	got = keyget();
    } while (got == 0xe0);
    switch (got) {
    case 0x11:
	isup1 = 1;
    case 0xad:
	isdown1 = 0;
	break;
    case 0x2d:
	isdown1 = 1;
    case 0x91:
	isup1 = 0;
	break;
    case 0x1e:
	isleft1 = 1;
    case 0xa0:
	isright1 = 0;
	break;
    case 0x20:
	isright1 = 1;
    case 0x9e:
	isleft1 = 0;
	break;
    case 0x48:
	isup2 = 1;
    case 0xd0:
	isdown2 = 0;
	break;
    case 0x50:
	isdown2 = 1;
    case 0xc8:
	isup2 = 0;
	break;
    case 0x4b:
	isleft2 = 1;
    case 0xcd:
	isright2 = 0;
	break;
    case 0x4d:
	isright2 = 1;
    case 0xcb:
	isleft2 = 0;
    };

    return got;
}

#else

extern __inline__ unsigned char keyget(void)
{
    char *got;

    keyboard_update();
    got = keyboard_getstate();
    if (got[SCANCODE_CURSORBLOCKUP] != 0) {
	return 0xc8;
    } else if (got[SCANCODE_CURSORBLOCKDOWN] != 0) {
	return 0xd0;
    }
    if (got[SCANCODE_ESCAPE] != 0) {
	return KEY_ESCAPE;
    }
    if (got[SCANCODE_SPACE] != 0) {
	return KEY_RELEASE(KEY_SPACE);
    }
    if (got[SCANCODE_ENTER] != 0) {
	return KEY_RETURN;
    }
    if (got[SCANCODE_P] != 0) {
	return KEY_RELEASE(KEY_P);
    }
    if (got[SCANCODE_E] != 0) {
	return KEY_E;
    }
    if (got[SCANCODE_M] != 0) {
	return KEY_M;
    }
    if (got[SCANCODE_I] != 0) {
	return KEY_I;
    }
    if (got[SCANCODE_L] != 0) {
	return KEY_L;
    }

    return 0;
}

extern __inline__ unsigned char keydeps(void)
{
    char *got;

    keyboard_update();
    got = keyboard_getstate();
    isup1 = isdown1 = isleft1 = isright1 = 0;
    if (got[SCANCODE_W] != 0) {
	isup1 = 1;
    } else if (got[SCANCODE_X] != 0) {
	isdown1 = 1;
    }
    if (got[SCANCODE_A] != 0) {
	isleft1 = 1;
    } else if (got[SCANCODE_D] != 0) {
	isright1 = 1;
    }
    isup2 = isdown2 = isleft2 = isright2 = 0;
    if (got[SCANCODE_CURSORBLOCKUP] != 0) {
	isup2 = 1;
    } else if (got[SCANCODE_CURSORBLOCKDOWN] != 0) {
	isdown2 = 1;
    }
    if (got[SCANCODE_CURSORBLOCKLEFT] != 0) {
	isleft2 = 1;
    } else if (got[SCANCODE_CURSORBLOCKRIGHT] != 0) {
	isright2 = 1;
    }
    if (got[SCANCODE_ESCAPE] != 0) {
	return KEY_ESCAPE;
    }
    if (got[SCANCODE_SPACE] != 0) {
	return KEY_RELEASE(KEY_SPACE);
    }
    if (got[SCANCODE_ENTER] != 0) {
	return KEY_RETURN;
    }
    if (got[SCANCODE_P] != 0) {
	return KEY_RELEASE(KEY_P);
    }

    return 0;
}

#endif
