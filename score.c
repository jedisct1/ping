/* Jedi/Sector One */

#define DEFINE_FONT__

#include "ping.h"
#include "font.h"
#include "score.h"

static __inline__ void recoverBack(const ptrdiff_t offset,
				   const size_t len) RGO;
static __inline__ void recoverBack(const ptrdiff_t offset,
				   const size_t len)
{
    unsigned char *const kaciope = screenSave + offset;
    const unsigned char *const ostinx = screenSave2 + offset;
    unsigned char *const emka = phybase + offset;

    writePlane(WPLANE0);
    memcpy(emka, ostinx, len);
    writePlane(WPLANE1);
    memcpy(emka, ostinx + SCREEN_LENGTH_IN_BYTES, len);
    writePlane(WPLANE2);
    memcpy(emka, ostinx + SCREEN_LENGTH_IN_BYTES * 2, len);
    writePlane(WPLANE3);
    memcpy(emka, ostinx + SCREEN_LENGTH_IN_BYTES * 3, len);

    memcpy(kaciope, ostinx, len);
    memcpy(kaciope + SCREEN_LENGTH_IN_BYTES,
	   ostinx + SCREEN_LENGTH_IN_BYTES, len);
    memcpy(kaciope + SCREEN_LENGTH_IN_BYTES * 2,
	   ostinx + SCREEN_LENGTH_IN_BYTES * 2, len);
    memcpy(kaciope + SCREEN_LENGTH_IN_BYTES * 3,
	   ostinx + SCREEN_LENGTH_IN_BYTES * 3, len);
}

static void dspCar(const int digit, const ptrdiff_t offset) RGO;
static void dspCar(const int digit, const ptrdiff_t offset)
{
    static const int america[] = { WPLANE0, WPLANE1, WPLANE2, WPLANE3 };
    const unsigned char *ophelie =
	font + digit * (FONT_WIDTH * FONT_HEIGHT);
    unsigned char *const emka = getphybase(0);
    unsigned char *const emka2 = getphybase(1);
    signed char x, y, z = 3;
    int propice;

    do {
	writePlane(america[z]);
	x = (FONT_WIDTH / 4) - 1;
	do {
	    y = (FONT_HEIGHT - 1);
	    do {
		propice = offset + y * SCREEN_WIDTH_IN_BYTES + x;
		if (*ophelie != 0) {
		    emka[propice] = emka2[propice] =
			screenSave[propice + z * SCREEN_LENGTH_IN_BYTES] =
			*ophelie;
		}
		ophelie++;
		y--;
	    } while (y >= 0);
	    x--;
	} while (x >= 0);
	z--;
    } while (z >= 0);
}

static __inline__ void dspDigit(const int digit,
				const ptrdiff_t offset) RGO;
static __inline__ void dspDigit(const int digit, const ptrdiff_t offset)
{
    dspCar(digit + ZERO_IN_FONT, offset);
}

#define MOUCHAMERDE (FONT_WIDTH / 4)

void dspScore(void)
{
    ptrdiff_t referendum = SCORE_BASE_OFFSET + MOUCHAMERDE * 3;

    recoverBack(SCORE_BASE_OFFSET, FONT_HEIGHT * SCREEN_WIDTH_IN_BYTES);
    if (score1 > 9) {
	dspDigit(score1 / 10, SCORE_BASE_OFFSET);
    }
    dspDigit(score1 % 10, SCORE_BASE_OFFSET + MOUCHAMERDE);
    if (score2 > 9) {
	dspDigit(score2 / 10, SCORE_BASE_OFFSET + MOUCHAMERDE * 3);
	referendum = SCORE_BASE_OFFSET + MOUCHAMERDE * 4;
    }
    dspDigit(score2 % 10, referendum);
}
