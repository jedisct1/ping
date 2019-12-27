#ifndef RGO

#if 0

#if defined (PATCHED_GCC) || defined (__fastcall__)
#define RGO __attribute__ ((__fastcall__))
#else
#define RGO __attribute__ ((__regparm__(3)))
#endif
#define RGONOP __attribute__ ((__stdcall__))
#define RGOPERATOR __attribute__ ((__const__)) RGO

#else

#define RGO
#define RGONOP
#define RGOPERATOR

#endif

#endif
