INIT;
PLANE(0);
SPRITEWRITEW(0, 0, 0x3330U);
SPRITEWRITEB(1, 1, 0x32U);
SPRITEWRITEB(1, 2, 0x31U);
PLANE(1);
SPRITEWRITEW(0, 0, 0x3432U);
SPRITEWRITEW(0, 1, 0x3131U);
PLANE(2);
SPRITEWRITEW(0, 0, 0x3031U);
SPRITEWRITEB(0, 1, 0x32U);
SPRITEWRITEB(0, 2, 0x32U);
PLANE(3);
SPRITEWRITEB(0, 1, 0x31U);
SPRITEWRITEB(0, 2, 0x32U);
SPRITEWRITEB(0, 3, 0x32U);
LOAD_PLANE(0);
LOAD_WRITEL(0, 0);
LOAD_WRITEL(0, 1);
LOAD_WRITEB(1, 2);
LOAD_WRITEB(1, 3);
LOAD_PLANE(1);
LOAD_WRITEL(0, 0);
LOAD_WRITEL(0, 1);
LOAD_WRITEB(1, 2);
LOAD_WRITEB(1, 3);
LOAD_PLANE(2);
LOAD_WRITEL(0, 0);
LOAD_WRITEL(0, 1);
LOAD_WRITEL(0, 2);
LOAD_WRITEB(1, 3);
LOAD_PLANE(3);
LOAD_WRITEL(0, 0);
LOAD_WRITEL(0, 1);
LOAD_WRITEL(0, 2);
LOAD_WRITEB(0, 3);
