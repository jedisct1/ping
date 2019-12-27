/* Jedi/Sector One */

#include <stdlib.h>
#include <string.h>
#ifndef __linux__
# include <pc.h>
# include <dos.h>
# include <sys/nearptr.h>
#else
# include <vga.h>
# include <sys/io.h>
#endif

#include "rgo.h"

extern void txtmode(void) RGONOP;
extern void mode13(void) RGONOP;
extern void ymode(void) RGONOP;
extern void xmode(void) RGONOP;
extern void xclear(unsigned char *const prout) RGO;
extern void yclear(unsigned char *const prout) RGO;
extern void copyYPage(const int from, const int to) RGO;
extern void copyPage(const int from, const int to) RGO;
extern void xsget(unsigned char *const whereto, const int page) RGO;
extern void xsput(unsigned char *const wherefrom, const int page) RGO;
extern void delayvbl(int t) RGO;

extern unsigned char *phybase, *logbase;

#ifdef __linux__
# define inportb inb
# define inportw inw
# define outportb(A, B) outb(B, A)
# define outportw(A, B) outw(B, A)
#endif

extern __inline__ void vsync(void)
{
#ifndef USE_SVGALIB_WAITRETRACE
    while ((inportb(0x3da) & 8) != 0);
    while ((inportb(0x3da) & 8) == 0);
#else
    vga_waitretrace();
#endif
}

#define WPLANE(X) ((X << 8) | 2)
#define WPLANE0 WPLANE(1)
#define WPLANE1 WPLANE(2)
#define WPLANE2 WPLANE(4)
#define WPLANE3 WPLANE(8)

extern __inline__ void writePlane(const int marcel)
{
    outportw(0x3c4, marcel);
}

#define RPLANE(X) ((X << 8) | 4)
#define RPLANE0 RPLANE(0)
#define RPLANE1 RPLANE(1)
#define RPLANE2 RPLANE(2)
#define RPLANE3 RPLANE(3)

extern __inline__ void readPlane(const int marcel)
{
    outportw(0x3ce, marcel);
}

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define SCREEN_WIDTH_IN_BYTES (SCREEN_WIDTH / 4)
#define SCREEN_LENGTH_IN_BYTES (SCREEN_WIDTH_IN_BYTES * SCREEN_HEIGHT)

extern __inline__ int screenOffset(const int x, const int y)
{
    return y * SCREEN_WIDTH_IN_BYTES + (x >> 2);
}

extern __inline__ int screenShift(const int x)
{
    return x & 3;
}

extern __inline__ void setYPage(const int page)
{
#ifndef __linux__
    const unsigned short port = 0x3d4;

    outportw(port, 0xd);
    if (page == 0) {
	phybase = (unsigned char *) (0xa0000 - __djgpp_base_address);
	outportw(port, 0x000c);
    } else if (page == 1) {
	phybase = (unsigned char *) (0xa4000 - __djgpp_base_address);
	outportw(port, 0x400c);
    } else if (page == 2) {
	phybase = (unsigned char *) (0xa8000 - __djgpp_base_address);
	outportw(port, 0x800c);
    } else {
	phybase = (unsigned char *) (0xac000 - __djgpp_base_address);
	outportw(port, 0xc00c);
    }
#else
    if (page == 0) {
	phybase = (unsigned char *) graph_mem;
	vga_setdisplaystart(0);
    } else if (page == 1) {
	phybase = (unsigned char *) graph_mem + 0x4000;
	vga_setdisplaystart(0x4000 * 4);
    } else if (page == 2) {
	phybase = (unsigned char *) graph_mem + 0x8000;
	vga_setdisplaystart(0x8000 * 4);
    } else {
	phybase = (unsigned char *) graph_mem + 0xc000;
	vga_setdisplaystart(0xc000 * 4);
    }
#endif
}

extern __inline__ void setPage(const int page)
{
#ifndef __linux__
    const unsigned short port = 0x3d4;

    outportw(port, 0xd);
    if (page == 0) {
	phybase = (unsigned char *) (0xa0000 - __djgpp_base_address);
	logbase = (unsigned char *) (0xa8000 - __djgpp_base_address);
	outportw(port, 0x000c);
    } else if (page == 1) {
	logbase = (unsigned char *) (0xa0000 - __djgpp_base_address);
	phybase = (unsigned char *) (0xa8000 - __djgpp_base_address);
	outportw(port, 0x800c);
    }
#else
    if (page == 0) {
	phybase = (unsigned char *) graph_mem;
	logbase = (unsigned char *) graph_mem + 0x8000;
	vga_setdisplaystart(0);
    } else if (page == 1) {
	logbase = (unsigned char *) graph_mem;
	phybase = (unsigned char *) graph_mem + 0x8000;
	vga_setdisplaystart(0x8000 * 4);
    }
#endif
}

extern __inline__ unsigned char *getYphybase(const int page)
{
#ifndef __linux__
    if (page == 0)
	return (unsigned char *) (0xa0000 - __djgpp_base_address);
    else if (page == 1)
	return (unsigned char *) (0xa4000 - __djgpp_base_address);
    else if (page == 2)
	return (unsigned char *) (0xa8000 - __djgpp_base_address);
    return (unsigned char *) (0xac000 - __djgpp_base_address);
#else
    if (page == 0)
	return (unsigned char *) graph_mem;
    else if (page == 1)
	return (unsigned char *) graph_mem + 0x4000;
    else if (page == 2)
	return (unsigned char *) graph_mem + 0x8000;
    return (unsigned char *) graph_mem + 0xc000;
#endif
}

extern __inline__ unsigned char *getphybase(const int page)
{
#ifndef __linux__
    if (page == 0)
	return (unsigned char *) (0xa0000 - __djgpp_base_address);
    return (unsigned char *) (0xa8000 - __djgpp_base_address);
#else
    if (page == 0)
	return (unsigned char *) graph_mem;
    return (unsigned char *) graph_mem + 0x8000;
#endif
}
