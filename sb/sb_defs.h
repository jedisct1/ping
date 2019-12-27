#ifndef __SB_DEF
#define __SB_DEF
#ifdef __cplusplus
extern "C" {
#endif

#ifndef BYTE
#define BYTE                    unsigned char
#endif
#ifndef WORD
#define WORD                    unsigned short
#endif
#ifndef DWORD
#define DWORD                   unsigned long
#endif

/* Formats to pass to the sb_load_sample() function.                          */
#define _SB_RAW                 0
#define _SB_WAV                 1
#define _SB_VOC                 2

/* Maximum samples that can be mixed or queued at a time.                     */
#define _SB_MAX_MIX             16
#define _SB_MAX_QUEUE           16

/*
   Size of the DMA transfer buffer.  Smaller sizes give better resolution in
   sample mixing, but take more CPU resources.
   THIS IS CURRENTLY HARD-CODED INTO THE SBDRIVER.C MODULE!  DON'T CHANGE IT
   HERE UNLESS YOU KNOW WHERE TO CHANGE IT THERE.
*/
#define _SB_BUFFER_SIZE         96
#define _SB_BLOCK_SIZE          (_SB_BUFFER_SIZE/2)

/* struct to store sample info.                                               */
    typedef struct {
	BYTE *data;
	int length;
	int stereo;
	int bits;
	int left_volume;
	int right_volume;
	void (*callback) (void);
    } sb_sample;

/* enum for return-values of many of the sb_ functions.                       */
    typedef enum {
	SB_SUCCESS,
	SB_FAILURE,
	SB_BAD_BLASTER,
	SB_BAD_ADDRESS,
	SB_BAD_IRQ,
	SB_BAD_DMA,
	SB_BAD_FILE,
	SB_BUSY,
	SB_BAD_POINTER
    } sb_status;

    typedef struct {
	char *sample;
	char name[22];
	WORD length;
	char fineTune;
	BYTE loudness;
	WORD repeatStart;
	WORD repeatLength;
    } sb_mod_instrument;

    typedef struct {
	char title[20];
	sb_mod_instrument *instrument;
	BYTE songLength;
	BYTE CIAA;
	BYTE arrangement[128];
	BYTE id[4];
	BYTE *patternBuffer;
	int modSamples;
	int modChannels;
    } sb_mod_file;

#ifdef __cplusplus
}
#endif
#endif
