#ifndef __linux__
#if 1
#include "mikmod.h"
#endif
#if 0
#include "mirq.h"
#endif

#include "norgo.h"

extern UWORD UltraSizeDram(void) RGONOP;
extern ULONG UltraMalloc(ULONG reqsize) RGO;
extern void UltraFree(ULONG size, ULONG location) RGO;
extern void UltraEnableOutput(void) RGONOP;
extern void UltraDisableOutput(void) RGONOP;
extern BOOL UltraDetect(void) RGONOP;
extern void UltraOpen(int voices) RGO;
extern void UltraClose(void) RGONOP;
extern void UltraSelectVoice(UBYTE voice) RGO;
extern void UltraSetFrequency(ULONG speed_khz) RGO;
extern void UltraSetLoopMode(UBYTE mode) RGO;
extern void UltraSetVoice(ULONG location) RGO;
extern void UltraGoVoice(UBYTE mode) RGO;
extern void UltraStartVoice(ULONG begin, ULONG start, ULONG end,
			    UBYTE mode) RGO;
extern void UltraStopVoice(void) RGONOP;
extern void UltraSetBalance(UBYTE pan) RGO;
extern void UltraSetVolume(UWORD volume) RGO;
extern void UltraPokeChunk(ULONG address, UBYTE * src, ULONG size) RGO;
extern void UltraPoke(ULONG address, UBYTE data) RGO;
extern void UltraRampLinearVolume(UWORD start_idx, UWORD end_idx,
				  ULONG msecs, UBYTE mode) RGO;
extern void UltraVectorLinearVolume(UWORD end_idx, UBYTE rate,
				    UBYTE mode) RGO;
extern void UltraSetLinearVolume(UWORD index) RGO;



#endif
