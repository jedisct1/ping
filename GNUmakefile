# Makefile for Ping Linux by Jedi/Sector One <j@pureftpd.org>

# Name of the executable file
NAME 	= ping_game

# List of source files needed to build it

SRC	= \
nocrt.c xymode.c main.c \
sprites.c sprites2.c sprites3.c sprites4.c \
terrains.c palette.c score.c joystick.c \
sb/sb.c sound/sound.c gus/drv_gus.c gus/gus.c \
intro.c mikfx/mikfx.c

ASMSRC  = irq.s bigping.s miniping.s textures.s fondu.s crew.s screxfnt.s

CC 	= gcc
AS      = as

OBJOPT  = -O2 -fno-strict-aliasing -funsigned-char \
-Wall -W -Wbad-function-cast -Wcast-qual \
-Wpointer-arith -Wwrite-strings -Wshadow -Winline -Wstrict-prototypes
C2ASFL  = -S
COUTPUT = -o
ASFLAGS = -K
INCLFL  = -I
LINKFL  = -l
LINKPFL = -L

IPATH   = $(INCLFL). $(INCLFL)sound `libmikmod-config --cflags`
EXEOPT  = $(LINKFL)vga `libmikmod-config --ldadd --libs` $(LINKFL)m
LPATH   = $(LINKPFL). $(LINKPFL)sb $(LINKPFL)sound $(LINKPFL)gus

ASMOBJS = $(SRC:%.c=%.s) $(ASMSRC)
OBJS    = $(ASMOBJS:%.s=%.o)
RM 	= rm
STRIP	= strip
MV      = mv
CP      = cp
MKDIR   = mkdir
RMDIR   = deltree /Y
TOUCH   = touch
DPMI    = PING.DAT
PMODE   = c:\gcc\bin\pmodstub.exe
ZIP     = pkzip
ZIPFLAGS= -a -ex -r -P
ZIPNAME = ping2.zip
MAKEDEPEND = gcc -MM
CRUNCH  = djp $(NAME)
EXEADD  = stubedit $(NAME) dpmi=$(DPMI)
OTHERZIP= ping.dat ping.nfo file_id.diz sct1.diz sounds/*.*

CFLAGS  = $(OBJOPT) $(IPATH)
LDFLAGS = -s $(LPATH) $(EXEOPT) 

readme:
	@echo
	@echo '** PLEASE READ THE "README" and "SOUND.README" files and try again.'
	@echo	

all: $(NAME) 

checks:
	@./check

$(NAME): checks $(ASMOBJS) $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS)
#	$(CRUNCH)
#	$(EXEADD)
#	copy /B $(PMODE) + a.out $(NAME)
#	@-$(RM) *.ex~
	@$(CP) a.out $(NAME)
	@-$(RM) a.out
	@echo
	@echo "** Done ! Run ./ping_game as root on a console, now."
	@echo

%.s: %.c
	$(CC) $(CFLAGS) $(C2ASFL) $< $(COUTPUT) $@

%.o: %.s
	$(AS) $(ASFLAGS) $< $(COUTPUT) $@

depend:
	$(MAKEDEPEND) $(IPATH) *.c sb/*.c sound/*.c gus/*.c mikfx/*.c > dep

purge:
	-$(RM) dep
	-$(RM) *.*~ *.bak Includes/*.*~ Includes/*.bak a.out
	-$(RM) sb/*.*~ sb/*.bak
	-$(RM) sound/*.*~ sound/*.bak
	-$(RM) gus/*.*~ gus/*.bak

clean: purge
	-$(RM) $(NAME)
	-$(RM) $(SRC:%.c=%.s)
	-$(RM) $(SRC:%.c=%.o)
	-$(RM) $(ASMSRC:%.s=%.o)
		
zip: clean
	-$(RM) $(ZIPNAME)
	$(ZIP) $(ZIPFLAGS) $(ZIPNAME) *.*

disk: $(NAME)
	-$(RM) a:/$(ZIPNAME)
	$(ZIP) $(ZIPFLAGS) a:/$(ZIPNAME) $(NAME) $(OTHERZIP)

intro.o: intro.c ping.h rgo.h xymode.h sprites.h palette.h terrains.h \
 keyboard.h bigping.h miniping.h fondu.h crew.h font.h screxfnt.h \
 intro.h sound/mikjedi.h txt.h txt/page1.inc txt/page2.inc \
 txt/page3.inc txt/page4.inc txt/page5.inc txt/page6.inc txt/info1.inc \
 txt/info2.inc txt/info3.inc txt/info4.inc txt/cfg1.inc txt/cfg2.inc \
 txt/cfg3.inc txt/ctrl1.inc txt/ctrl2.inc txt/ctrl3.inc txt/cal11.inc \
 txt/cal12.inc txt/cal13.inc txt/cal14.inc txt/cal15.inc txt/cal21.inc \
 txt/cal22.inc txt/cal23.inc txt/cal24.inc txt/cal25.inc \
 txt/nohappy.inc txt/screx.inc joystick.h sound/sound.h
joystick.o: joystick.c xymode.h rgo.h
main.o: main.c main.h crt0init.h ping.h rgo.h xymode.h sprites.h \
 palette.h terrains.h keyboard.h score.h intersec.h sound/sound.h \
 joystick.h irq.h intro.h inc/bousin.inc inc/coeursin.inc
nocrt.o: nocrt.c
palette.o: palette.c xymode.h rgo.h palette_.h inc/pal.inc \
 inc/palcrew.inc
score.o: score.c ping.h rgo.h xymode.h sprites.h palette.h terrains.h \
 font.h inc/font.inc score.h
sprites.o: sprites.c ping.h rgo.h xymode.h sprites.h palette.h \
 terrains.h spr_dsp.h inc/normraq.inc inc/bigraq.inc inc/horiraq.inc \
 inc/bonus0.inc inc/bonus1.inc inc/bonus2.inc inc/bonus3.inc \
 inc/bonus6.inc inc/bonus7.inc inc/bonus9.inc inc/bonus10.inc \
 inc/bonus11.inc inc/bonus12.inc inc/bonus13.inc inc/bonusbck.inc \
 inc/rond0.inc inc/rond1.inc inc/rond2.inc inc/rond3.inc inc/rond4.inc \
 inc/rond5.inc inc/rond6.inc inc/rond7.inc inc/rond8.inc inc/rond9.inc \
 inc/rond10.inc inc/rond11.inc inc/rond12.inc inc/rond13.inc \
 inc/rond14.inc inc/rond15.inc inc/rond16.inc inc/rond17.inc \
 inc/rond18.inc inc/rond19.inc inc/rond20.inc inc/rond21.inc \
 inc/rond22.inc inc/rond23.inc inc/rond24.inc inc/rond25.inc \
 inc/rond26.inc inc/rond27.inc inc/rond28.inc inc/rond29.inc \
 inc/rond30.inc inc/rond31.inc spr_load.h
sprites2.o: sprites2.c ping.h rgo.h xymode.h sprites.h palette.h \
 terrains.h spr_dsp.h inc/normbool.inc inc/tinybool.inc \
 inc/midbool.inc spr_load.h
sprites3.o: sprites3.c ping.h rgo.h xymode.h sprites.h palette.h \
 terrains.h spr_dsp.h inc/coeur1.inc inc/coeur2.inc inc/coeur3.inc \
 inc/coeur4.inc inc/bisou2.inc inc/bisou1.inc spr_load.h
sprites4.o: sprites4.c ping.h rgo.h xymode.h sprites.h palette.h \
 terrains.h spr_dsp.h inc/bulle1.inc inc/bulle2.inc inc/bulle3.inc \
 spr_load.h
terrains.o: terrains.c ping.h rgo.h xymode.h sprites.h palette.h \
 terrains.h textures.h
xymode.o: xymode.c xymode.h rgo.h
sb.o: sb/sb.c
sound.o: sound/sound.c rgo.h sound/sound.h mikfx/mikfx.h
drv_gus.o: gus/drv_gus.c
gus.o: gus/gus.c
mikfx.o: mikfx/mikfx.c sound/sound.h rgo.h
