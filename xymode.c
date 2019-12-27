/* Jedi/Sector One */

#include "xymode.h"

unsigned char *phybase, *logbase;
#ifndef __linux__
static union REGS in, out;
#endif

void txtmode(void)
{
#ifndef __linux__
    in.w.ax = 3;
    int86(0x10, &in, &out);
#endif
}

void mode13(void)
{
#ifndef __linux__
    vsync();
    in.w.ax = 0x13;
    int86(0x10, &in, &out);
#endif
}

#ifdef __linux__
static void init(void)
{
    static unsigned char flag;

    if (flag == 0) {
	flag++;
	vga_init();
    }
}
#endif

void ymode(void)
{
#ifndef __linux__
    mode13();
    outportb(0x3c4, 4);
    outportb(0x3c5, (inportb(0x3c5) & (255 - 8)) | 4);
    outportb(0x3ce, 6);
    outportb(0x3cf, inportb(0x3cf) & (255 - 2));
    outportb(0x3d4, 0x14);
    outportb(0x3d5, inportb(0x3d5) & (255 - 64));
    outportb(0x3d4, 0x17);
    outportb(0x3d5, inportb(0x3d5) | 64);
#else
    init();
    vga_setmode(G320x200x256);
    vga_setmodeX();
#endif
}

void xmode(void)
{
#ifndef __linux__
    ymode();
    outportb(0x3c2, 255 - (4 + 8 + 16));
    outportw(0x3d4, 0x300);
    outportb(0x3d4, 0x11);
    outportb(0x3d5, inportb(0x3d5) & 127);
    outportw(0x3d4, 0xd06);
    outportw(0x3d4, 0x3e07);
    outportw(0x3d4, 0x4109);
    outportw(0x3d4, 0xea10);
    outportw(0x3d4, 0xac11);
    outportw(0x3d4, 0xdf12);
    outportw(0x3d4, 0xe715);
    outportw(0x3d4, 0x616);
#else
    init();
    vga_setmode(G320x240x256);
    vga_setmodeX();
#endif
}

static __inline__ void zclear(unsigned char *const prout,
			      const size_t size)
{
    writePlane(WPLANE0 | WPLANE1 | WPLANE2 | WPLANE3);
    memset((void *) prout, 0, size);
}

void yclear(unsigned char *const prout)
{
    zclear(prout, SCREEN_WIDTH_IN_BYTES * 200);
}

void xclear(unsigned char *const prout)
{
    zclear(prout, SCREEN_WIDTH_IN_BYTES * 240);
}

void copyYPage(const int from, const int to)
{
#ifndef __linux__
    void *const zto =
	(void *) (0xa0000 + to * 0x4000 - __djgpp_base_address);
    void *const zfrom =
	(void *) (0xa0000 + from * 0x4000 - __djgpp_base_address);
#else
    void *const zto = (void *) (graph_mem + to * 0x4000);
    void *const zfrom = (void *) (graph_mem + from * 0x4000);
#endif

    readPlane(RPLANE0);
    writePlane(WPLANE0);
    memcpy(zto, zfrom, SCREEN_LENGTH_IN_BYTES);
    readPlane(RPLANE1);
    writePlane(WPLANE1);
    memcpy(zto, zfrom, SCREEN_LENGTH_IN_BYTES);
    readPlane(RPLANE2);
    writePlane(WPLANE2);
    memcpy(zto, zfrom, SCREEN_LENGTH_IN_BYTES);
    readPlane(RPLANE3);
    writePlane(WPLANE3);
    memcpy(zto, zfrom, SCREEN_LENGTH_IN_BYTES);
}

void copyPage(const int from, const int to)
{
#ifndef __linux__
    void *const zto =
	(void *) (0xa0000 + to * 0x8000 - __djgpp_base_address);
    void *const zfrom =
	(void *) (0xa0000 + from * 0x8000 - __djgpp_base_address);
#else
    void *const zto = (void *) (graph_mem + to * 0x8000);
    void *const zfrom = (void *) (graph_mem + from * 0x8000);
#endif

    readPlane(RPLANE0);
    writePlane(WPLANE0);
    memcpy(zto, zfrom, SCREEN_LENGTH_IN_BYTES);
    readPlane(RPLANE1);
    writePlane(WPLANE1);
    memcpy(zto, zfrom, SCREEN_LENGTH_IN_BYTES);
    readPlane(RPLANE2);
    writePlane(WPLANE2);
    memcpy(zto, zfrom, SCREEN_LENGTH_IN_BYTES);
    readPlane(RPLANE3);
    writePlane(WPLANE3);
    memcpy(zto, zfrom, SCREEN_LENGTH_IN_BYTES);
}

void xsget(unsigned char *const whereto, const int page)
{
#ifndef __linux__
    unsigned char *const zfrom =
	(unsigned char *) (0xa0000 + page * 0x8000 - __djgpp_base_address);
#else
    unsigned char *const zfrom =
	(unsigned char *) (graph_mem + page * 0x8000);
#endif
    unsigned char *const zto = (unsigned char *) whereto;

    readPlane(RPLANE0);
    memcpy(zto, zfrom, SCREEN_LENGTH_IN_BYTES);
    readPlane(RPLANE1);
    memcpy(zto + SCREEN_LENGTH_IN_BYTES, zfrom, SCREEN_LENGTH_IN_BYTES);
    readPlane(RPLANE2);
    memcpy(zto + SCREEN_LENGTH_IN_BYTES * 2, zfrom,
	   SCREEN_LENGTH_IN_BYTES);
    readPlane(RPLANE3);
    memcpy(zto + SCREEN_LENGTH_IN_BYTES * 3, zfrom,
	   SCREEN_LENGTH_IN_BYTES);
}

void xsput(unsigned char *const wherefrom, const int page)
{
#ifndef __linux__
    unsigned char *const zto =
	(unsigned char *) (0xa0000 + page * 0x8000 - __djgpp_base_address);
#else
    unsigned char *const zto =
	(unsigned char *) (graph_mem + page * 0x8000);
#endif
    unsigned char *const zfrom = (unsigned char *) wherefrom;

    writePlane(WPLANE0);
    memcpy(zto, zfrom, SCREEN_LENGTH_IN_BYTES);
    writePlane(WPLANE1);
    memcpy(zto, zfrom + SCREEN_LENGTH_IN_BYTES, SCREEN_LENGTH_IN_BYTES);
    writePlane(WPLANE2);
    memcpy(zto, zfrom + SCREEN_LENGTH_IN_BYTES * 2,
	   SCREEN_LENGTH_IN_BYTES);
    writePlane(WPLANE3);
    memcpy(zto, zfrom + SCREEN_LENGTH_IN_BYTES * 3,
	   SCREEN_LENGTH_IN_BYTES);
}

void delayvbl(int t)
{
    do {
	vsync();
	t--;
    } while (t != 0);
}
