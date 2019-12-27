#ifndef __SB_DRIVER
#define __SB_DRIVER
#ifdef __cplusplus
extern "C" {
#endif

/* If one of the functions in this module returns an error, look here for a
   description of what happened.                                              */
    extern char sb_driver_error[80];
    extern int sb_sample_frequency;

/* Pass: Frequency (Hz) all your samples will be running at.                  */
/* Returns: sb_status enum indicating what happened (see sb_defs.h)           */
    sb_status sb_install_driver(int);

/* Pass:                                                                      */
/* Returns:                                                                   */
    void sb_uninstall_driver(void);

#ifdef __cplusplus
}
#endif
#endif
