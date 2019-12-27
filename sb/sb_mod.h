#ifndef __SB_MOD
#define __SB_MOD
#ifdef __cplusplus
extern "C" {
#endif

    sb_mod_file *sb_load_mod_file(char *);
    void sb_free_mod_file(sb_mod_file *);
    void sb_mod_initialize_player(void);
    void sb_mod_play(sb_mod_file *);
    void sb_mod_pause(void);
    void sb_mod_resume(void);
    void sb_mod_parse_file(void);
    void sb_mod_parse_file_mono(void);

    int sb_mod_module_lock_your_memory(void);

    void sb_mod_show_info(void);

    extern char sb_mod_error[64];
    extern int sb_mod_active;
    extern int sb_mod_volume;

#ifdef __cplusplus
}
#endif
#endif
