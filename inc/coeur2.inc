INIT;
PLANE(0);
SPRITEANDL(0, 0, 0xff00ff00UL);
SPRITEORL(0, 0, 0x00370037UL);
SPRITEANDL(0, 1, 0xff000000UL);
SPRITEORL(0, 1, 0x00303130UL);
SPRITEWRITEB(1, 2, 0x31U);
SPRITEWRITEB(1, 3, 0x31U);
SPRITEWRITEB(1, 4, 0x32U);
SPRITEWRITEB(1, 5, 0x31U);
PLANE(1);
SPRITEWRITEW(0, 0, 0x3331U);
SPRITEWRITEW(0, 1, 0x3332U);
SPRITEWRITEW(0, 2, 0x3231U);
SPRITEWRITEB(1, 3, 0x31U);
SPRITEWRITEB(1, 4, 0x31U);
PLANE(2);
SPRITEWRITEW(0, 0, 0x3532U);
SPRITEWRITEW(0, 1, 0x3331U);
SPRITEWRITEW(0, 2, 0x3232U);
SPRITEWRITEW(0, 3, 0x3131U);
PLANE(3);
SPRITEWRITEW(0, 0, 0x3131U);
SPRITEWRITEW(0, 1, 0x3231U);
SPRITEWRITEW(0, 2, 0x3131U);
SPRITEWRITEB(0, 3, 0x32U);
SPRITEWRITEB(0, 4, 0x31U);
LOAD_PLANE(0);
LOAD_WRITEL(0, 0);
LOAD_WRITEL(0, 1);
LOAD_WRITEL(0, 2);
LOAD_WRITEL(0, 3);
LOAD_WRITEL(0, 4);
LOAD_WRITEB(1, 5);
LOAD_PLANE(1);
LOAD_WRITEL(0, 0);
LOAD_WRITEL(0, 1);
LOAD_WRITEL(0, 2);
LOAD_WRITEL(0, 3);
LOAD_WRITEB(1, 4);
LOAD_WRITEB(1, 5);
LOAD_PLANE(2);
LOAD_WRITEL(0, 0);
LOAD_WRITEL(0, 1);
LOAD_WRITEL(0, 2);
LOAD_WRITEL(0, 3);
LOAD_WRITEB(1, 4);
LOAD_WRITEB(1, 5);
LOAD_PLANE(3);
LOAD_WRITEL(0, 0);
LOAD_WRITEL(0, 1);
LOAD_WRITEL(0, 2);
LOAD_WRITEL(0, 3);
LOAD_WRITEL(0, 4);
LOAD_WRITEB(1, 5);
