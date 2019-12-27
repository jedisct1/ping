/* (C)oderight 1996 by Jedi/Sector One */

#ifndef __linux__
# include <crt0.h>

int _crt0_startup_flags =
    _CRT0_FLAG_PRESERVE_UPPER_CASE |
    _CRT0_FLAG_USE_DOS_SLASHES |
    _CRT0_FLAG_DISALLOW_RESPONSE_FILES |
    _CRT0_FLAG_NEARPTR | _CRT0_FLAG_NO_LFN | 0;
#endif
