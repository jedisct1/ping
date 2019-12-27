/* Jedi/Sector One */

#include <stdlib.h>
#include <stddef.h>
#ifndef __linux__
# include <pc.h>
#else
# include "xymode.h"
# include <sys/io.h>
#endif
#include <string.h>
#include "palette_.h"

void setpal(void)
{
#ifndef __linux__
    outportb(0x3c8, 0);
    outportsb(0x3c9, pal, (sizeof pal) / sizeof pal[0]);
#else
    const unsigned char *ppnt = pal;
    int t = sizeof pal / sizeof pal[0];

    outb(0, 0x3c8);
    do {
	outb(*ppnt++, 0x3c9);
	t--;
    } while (t != 0);
#endif
}

void setpalcrew(void)
{
#ifndef __linux__
    outportb(0x3c8, 0);
    outportsb(0x3c9, palcrew, (sizeof palcrew) / sizeof palcrew[0]);
#else
    const unsigned char *ppnt = palcrew;
    int t = sizeof palcrew / sizeof palcrew[0];

    outb(0, 0x3c8);
    do {
	outb(*ppnt++, 0x3c9);
	t--;
    } while (t != 0);
#endif
}

void setblack(void)
{
    int t = 256 * 3;

    outportb(0x3c8, 0);
    do {
	outportb(0x3c9, 0);
	t--;
    } while (t != 0);
}
