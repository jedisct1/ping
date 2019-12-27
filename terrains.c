/* Jedi/Sector One */

#include "ping.h"
#include "textures.h"

static void initRaqSaveOne(Screen * scr) RGO;
static void initRaqSaveOne(Screen * scr)
{
    int t = (MAXBALLS - 1);

    scr->oldRaq1.addr = phybase;
    scr->oldRaq1.offset = 0;
    scr->oldRaq2.addr = phybase;
    scr->oldRaq2.offset = 0;
    scr->oldLoadRaq1 = scr->oldLoadRaq2 = load_normRaq;

    scr->oldLazer.lazerAddr = NULL;

    do {
	scr->oldBall[t].enabled = 0;
	scr->oldBall[t].addr = phybase;
	scr->oldBall[t].offset = 0;
	scr->oldBall[t].oldLoadBall = load_normBool;
	t--;
    } while (t >= 0);

#if BONI_SUPPORT
    scr->oldBonus.enabled = 0;
#endif
}

static __inline__ void initRaqSave(void)
{
    initRaqSaveOne(&screen[0]);
    initRaqSaveOne(&screen[1]);
}

void terrain2(void)
{
    const unsigned long fl = 0x1e1e1e1eUL;
    const unsigned short f = 0x1e1eU;
    unsigned char *z;
    unsigned long *zl = (unsigned long *) screenSave2;
    int t = SCREEN_HEIGHT;

    memset(screenSave2, 0, SCREEN_LENGTH_IN_BYTES * 4);

    {
	const unsigned char *texturepnt;
	int y;
	int popo = (SCREEN_HEIGHT / TEXTURE1_HEIGHT);


	z = screenSave2;
	do {
	    texturepnt = texture1;
	    y = TEXTURE1_HEIGHT;
	    do {
		memcpy(z, texturepnt, TEXTURE1_WIDTH_IN_BYTES);
		memcpy(z + TEXTURE1_WIDTH_IN_BYTES, texturepnt,
		       TEXTURE1_WIDTH_IN_BYTES);
		memcpy(z + TEXTURE1_WIDTH_IN_BYTES * 2, texturepnt,
		       TEXTURE1_WIDTH_IN_BYTES);
		memcpy(z + TEXTURE1_WIDTH_IN_BYTES * 3, texturepnt,
		       TEXTURE1_WIDTH_IN_BYTES);

		memcpy(z + SCREEN_LENGTH_IN_BYTES,
		       texturepnt + TEXTURE1_ONEPLANE,
		       TEXTURE1_WIDTH_IN_BYTES);
		memcpy(z + SCREEN_LENGTH_IN_BYTES +
		       TEXTURE1_WIDTH_IN_BYTES,
		       texturepnt + TEXTURE1_ONEPLANE,
		       TEXTURE1_WIDTH_IN_BYTES);
		memcpy(z + SCREEN_LENGTH_IN_BYTES +
		       TEXTURE1_WIDTH_IN_BYTES * 2,
		       texturepnt + TEXTURE1_ONEPLANE,
		       TEXTURE1_WIDTH_IN_BYTES);
		memcpy(z + SCREEN_LENGTH_IN_BYTES +
		       TEXTURE1_WIDTH_IN_BYTES * 3,
		       texturepnt + TEXTURE1_ONEPLANE,
		       TEXTURE1_WIDTH_IN_BYTES);

		memcpy(z + SCREEN_LENGTH_IN_BYTES * 2,
		       texturepnt + TEXTURE1_ONEPLANE * 2,
		       TEXTURE1_WIDTH_IN_BYTES);
		memcpy(z + SCREEN_LENGTH_IN_BYTES * 2 +
		       TEXTURE1_WIDTH_IN_BYTES,
		       texturepnt + TEXTURE1_ONEPLANE * 2,
		       TEXTURE1_WIDTH_IN_BYTES);
		memcpy(z + SCREEN_LENGTH_IN_BYTES * 2 +
		       TEXTURE1_WIDTH_IN_BYTES * 2,
		       texturepnt + TEXTURE1_ONEPLANE * 2,
		       TEXTURE1_WIDTH_IN_BYTES);
		memcpy(z + SCREEN_LENGTH_IN_BYTES * 2 +
		       TEXTURE1_WIDTH_IN_BYTES * 3,
		       texturepnt + TEXTURE1_ONEPLANE * 2,
		       TEXTURE1_WIDTH_IN_BYTES);

		memcpy(z + SCREEN_LENGTH_IN_BYTES * 3,
		       texturepnt + TEXTURE1_ONEPLANE * 3,
		       TEXTURE1_WIDTH_IN_BYTES);
		memcpy(z + SCREEN_LENGTH_IN_BYTES * 3 +
		       TEXTURE1_WIDTH_IN_BYTES,
		       texturepnt + TEXTURE1_ONEPLANE * 3,
		       TEXTURE1_WIDTH_IN_BYTES);
		memcpy(z + SCREEN_LENGTH_IN_BYTES * 3 +
		       TEXTURE1_WIDTH_IN_BYTES * 2,
		       texturepnt + TEXTURE1_ONEPLANE * 3,
		       TEXTURE1_WIDTH_IN_BYTES);
		memcpy(z + SCREEN_LENGTH_IN_BYTES * 3 +
		       TEXTURE1_WIDTH_IN_BYTES * 3,
		       texturepnt + TEXTURE1_ONEPLANE * 3,
		       TEXTURE1_WIDTH_IN_BYTES);

		z += SCREEN_WIDTH_IN_BYTES;
		texturepnt += TEXTURE1_WIDTH_IN_BYTES;
		y--;
	    } while (y != 0);
	    popo--;
	} while (popo != 0);
    }

    t = SCREEN_HEIGHT;
    z = screenSave2;
    do {
	*z = z[SCREEN_WIDTH_IN_BYTES - 1 + SCREEN_LENGTH_IN_BYTES * 3] =
	    0x1e;
	*(unsigned short *) (z + 39) =
	    *(unsigned short *) (z + SCREEN_LENGTH_IN_BYTES + 39) =
	    *(unsigned short *) (z + SCREEN_LENGTH_IN_BYTES * 2 + 39) =
	    *(unsigned short *) (z + SCREEN_LENGTH_IN_BYTES * 3 + 39) = f;
	z += SCREEN_WIDTH_IN_BYTES;
	t--;
    } while (t != 0);
    t = SCREEN_WIDTH_IN_BYTES / 4;
    do {
	zl[(SCREEN_WIDTH_IN_BYTES * (SCREEN_HEIGHT - 1)) / 4] =
	    zl[(SCREEN_WIDTH_IN_BYTES * (SCREEN_HEIGHT - 1)) / 4 +
	       SCREEN_LENGTH_IN_BYTES / 4] =
	    zl[(SCREEN_WIDTH_IN_BYTES * (SCREEN_HEIGHT - 1)) / 4 +
	       (SCREEN_LENGTH_IN_BYTES * 2 / 4)] =
	    zl[(SCREEN_WIDTH_IN_BYTES * (SCREEN_HEIGHT - 1)) / 4 +
	       (SCREEN_LENGTH_IN_BYTES * 3 / 4)] = zl[0] =
	    zl[SCREEN_LENGTH_IN_BYTES / 4] =
	    zl[SCREEN_LENGTH_IN_BYTES * 2 / 4] =
	    zl[SCREEN_LENGTH_IN_BYTES * 3 / 4] = fl;
	zl++;
	t--;
    } while (t != 0);

    memcpy(screenSave, screenSave2, SCREEN_LENGTH_IN_BYTES * 4);
    xsput(screenSave, 0);
    setPage(0);
    copyPage(0, 1);
    initRaqSave();
}

void terrain1(void)
{
    const unsigned long fl = 0x1e1e1e1eUL;
    const unsigned short f = 0x1e1eU;
    unsigned char *z;
    unsigned long *zl = (unsigned long *) screenSave2;
    int t = SCREEN_HEIGHT;

    memset(screenSave2, 0, SCREEN_LENGTH_IN_BYTES * 4);

    z = screenSave2;
    do {
	memset(z, 0x1c, 20);
	memset(z + SCREEN_LENGTH_IN_BYTES, 0x1c, 20);
	memset(z + SCREEN_LENGTH_IN_BYTES * 2, 0x1c, 20);
	memset(z + SCREEN_LENGTH_IN_BYTES * 3, 0x1c, 20);
	z += SCREEN_WIDTH_IN_BYTES + 1;
	t--;
    } while (t != 0);

    t = SCREEN_HEIGHT;
    z = screenSave2;
    do {
	*z = z[SCREEN_WIDTH_IN_BYTES - 1 + SCREEN_LENGTH_IN_BYTES * 3] =
	    0x1e;
	*(unsigned short *) (z + 39) =
	    *(unsigned short *) (z + SCREEN_LENGTH_IN_BYTES + 39) =
	    *(unsigned short *) (z + SCREEN_LENGTH_IN_BYTES * 2 + 39) =
	    *(unsigned short *) (z + SCREEN_LENGTH_IN_BYTES * 3 + 39) = f;
	z += SCREEN_WIDTH_IN_BYTES;
	t--;
    } while (t != 0);
    t = SCREEN_WIDTH_IN_BYTES / 4;
    do {
	zl[(SCREEN_WIDTH_IN_BYTES * (SCREEN_HEIGHT - 1)) / 4] =
	    zl[(SCREEN_WIDTH_IN_BYTES * (SCREEN_HEIGHT - 1)) / 4 +
	       SCREEN_LENGTH_IN_BYTES / 4] =
	    zl[(SCREEN_WIDTH_IN_BYTES * (SCREEN_HEIGHT - 1)) / 4 +
	       (SCREEN_LENGTH_IN_BYTES * 2 / 4)] =
	    zl[(SCREEN_WIDTH_IN_BYTES * (SCREEN_HEIGHT - 1)) / 4 +
	       (SCREEN_LENGTH_IN_BYTES * 3 / 4)] = zl[0] =
	    zl[SCREEN_LENGTH_IN_BYTES / 4] =
	    zl[SCREEN_LENGTH_IN_BYTES * 2 / 4] =
	    zl[SCREEN_LENGTH_IN_BYTES * 3 / 4] = fl;
	zl++;
	t--;
    } while (t != 0);

    memcpy(screenSave, screenSave2, SCREEN_LENGTH_IN_BYTES * 4);
    xsput(screenSave, 0);
    setPage(0);
    copyPage(0, 1);
    initRaqSave();
}
