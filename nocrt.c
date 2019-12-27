/* (C)oderight 1996 by Jedi/Sector One */

#ifndef __linux__
# include <crt0.h>

# ifndef NEED_ENVIRONMENT
void __crt0_load_environment_file(char *_app_name)
{
    (void) _app_name;
}
# endif
# ifndef NEED_ARGUMENTS
void __crt0_setup_arguments(void)
{
}
# endif
char **__crt0_glob_function(char *_arg)
{
    (void) _arg;
    return (char **) 0;
}
#endif
