#include <stdlib.h>
#ifndef __linux__
# include <dos.h>
#else
# include "xymode.h"
#endif
#include "rgo.h"

#ifndef FALSE
#define FALSE 0
#endif

/* global joystick position variables */
int joy_x = 0;
int joy_y = 0;
int joy_left = FALSE;
int joy_right = FALSE;
int joy_up = FALSE;
int joy_down = FALSE;
int joy_b1 = FALSE;
int joy_b2 = FALSE;

/* joystick state information */
#define JOYSTICK_PRESENT      1
#define JOYSTICK_CALIB_TL     2
#define JOYSTICK_CALIB_BR     4

static int joystick_flags = 0;

/* calibrated position values */
static int joycentre_x, joycentre_y;
static int joyx_min, joyx_low_margin, joyx_high_margin, joyx_max;
static int joyy_min, joyy_low_margin, joyy_high_margin, joyy_max;



/* poll:
 *  Polls the joystick to read the axis position. Returns raw position
 *  values in x and y, zero for success, non-zero if no joystick found.
 */

static int poll(int *x, int *y) RGO;
static int poll(int *x, int *y)
{
    asm("  movw $0x201, %%dx ; "	/* joystick port */
	"  movl $100000, %%ecx ; "	/* loop counter in ecx */
	"  xorl %0, %0 ; " "  xorl %1, %1 ; " "  cli ; " "  outb %%al, %%dx ; "	/* write to joystick port */
	"  jmp 0f ; " " 0: " "  inb %%dx, %%al ; "	/* read joystick port */
	"  movl %%eax, %%ebx ; " "  shrl $1, %%ebx ; "	/* test x axis bit */
	"  adcl $0, %0 ; " "  shrl $1, %%ebx ; "	/* test y axis bit */
	"  adcl $0, %1 ; " "  testb $3, %%al ; "	/* repeat? */
  "  loopnz 0b ; " "  sti ; ":"=S"(*x),
				/* output registers */
	"=D"(*y)
  :
  :	"eax", "ebx", "ecx", "edx");	/* clobbered registers */

    if ((*x >= 100000) || (*y >= 100000)) {
	return -1;
    }

    return 0;
}



/* initialise_joystick:
 *  Calibrates the joystick by reading the axis values when the joystick
 *  is centered. You should call this before using other joystick functions,
 *  and must make sure the joystick is centered when you do so. Returns
 *  non-zero if no joystick is present.
 */
int initialise_joystick(void)
{
    if (poll(&joycentre_x, &joycentre_y) != 0) {
	joy_x = joy_y = 0;
	joy_left = joy_right = joy_up = joy_down = FALSE;
	joy_b1 = joy_b2 = FALSE;
	joystick_flags = 0;
	return -1;
    }

    joystick_flags = JOYSTICK_PRESENT;

    return 0;
}



/* sort_out_middle_values:
 *  Sets up the values used by sort_out_analogue() to create a 'dead'
 *  region in the centre of the joystick range.
 */
static void sort_out_middle_values(void) RGONOP;
static void sort_out_middle_values(void)
{
    joyx_low_margin = joycentre_x - (joycentre_x - joyx_min) / 8;
    joyx_high_margin = joycentre_x + (joyx_max - joycentre_x) / 8;
    joyy_low_margin = joycentre_y - (joycentre_y - joyy_min) / 8;
    joyy_high_margin = joycentre_y + (joyy_max - joycentre_y) / 8;
}



/* calibrate_joystick_tl:
 *  For analogue access to the joystick, call this after
 *  initialise_joystick(), with the joystick at the top left
 *  extreme, and also call calibrate_joystick_br();
 */
int calibrate_joystick_tl(void)
{
    if (!(joystick_flags & JOYSTICK_PRESENT)) {
	joystick_flags &= (~JOYSTICK_CALIB_TL);
	return -1;
    }

    if (poll(&joyx_min, &joyy_min) != 0) {
	joystick_flags &= (~JOYSTICK_CALIB_TL);
	return -1;
    }

    if (joystick_flags & JOYSTICK_CALIB_BR)
	sort_out_middle_values();

    joystick_flags |= JOYSTICK_CALIB_TL;

    return 0;
}



/* calibrate_joystick_br:
 *  For analogue access to the joystick, call this after
 *  initialise_joystick(), with the joystick at the bottom right
 *  extreme, and also call calibrate_joystick_tl();
 */
int calibrate_joystick_br(void)
{
    if (!(joystick_flags & JOYSTICK_PRESENT)) {
	joystick_flags &= (~JOYSTICK_CALIB_BR);
	return -1;
    }

    if (poll(&joyx_max, &joyy_max) != 0) {
	joystick_flags &= (~JOYSTICK_CALIB_BR);
	return -1;
    }

    if (joystick_flags & JOYSTICK_CALIB_TL)
	sort_out_middle_values();

    joystick_flags |= JOYSTICK_CALIB_BR;

    return 0;
}



/* sort_out_analogue:
 *  There are a couple of problems with reading analogue input from the PC
 *  joystick. For one thing, joysticks tend not to centre repeatably, so
 *  we need a small 'dead' zone in the middle. Also a lot of joysticks aren't
 *  linear, so the positions less than centre need to be handled differently
 *  to those above the centre.
 */
static int sort_out_analogue(int x, int min, int low_margin, int centre,
			     int high_margin, int max) RGO;
static int sort_out_analogue(int x, int min, int low_margin, int centre,
			     int high_margin, int max)
{
    (void) centre;

    if (x < min) {
	return -128;
    } else if (x < low_margin) {
	return -128 + (x - min) * 128 / (low_margin - min);
    } else if (x <= high_margin) {
	return 0;
    } else if (x <= max) {
	return 128 - (max - x) * 128 / (max - high_margin);
    } else
	return 128;
}



/* poll_joystick:
 *  Updates the global joystick position variables. You must call
 *  calibrate_joystick() before using this.
 */
void poll_joystick(void)
{
    int x, y;
    unsigned char status;

    if (joystick_flags & JOYSTICK_PRESENT) {
	poll(&x, &y);
	status = inportb(0x201);

	if ((joystick_flags & JOYSTICK_CALIB_TL) &&
	    (joystick_flags & JOYSTICK_CALIB_BR)) {
	    joy_x =
		sort_out_analogue(x, joyx_min, joyx_low_margin,
				  joycentre_x, joyx_high_margin, joyx_max);
	    joy_y =
		sort_out_analogue(y, joyy_min, joyy_low_margin,
				  joycentre_y, joyy_high_margin, joyy_max);
	} else {
	    joy_x = x - joycentre_x;
	    joy_y = y - joycentre_y;
	}

	joy_left = (x < (joycentre_x / 2));
	joy_right = (x > (joycentre_x * 3 / 2));
	joy_up = (y < (joycentre_y / 2));
	joy_down = (y > ((joycentre_y * 3) / 2));

	joy_b1 = ((status & 0x10) == 0);
	joy_b2 = ((status & 0x20) == 0);
    }
}
