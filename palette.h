/* Jedi/Sector One */

extern void setpal(void) RGONOP;
extern void setpalcrew(void) RGONOP;
extern void setblack(void) RGONOP;

extern __inline__ void setbackground(const unsigned char red,
				     const unsigned char green,
				     const unsigned char blue)
{
    outportb(0x3c8, 0);
    outportb(0x3c9, red);
    outportb(0x3c9, green);
    outportb(0x3c9, blue);
}
