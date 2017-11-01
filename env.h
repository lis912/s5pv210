#ifndef _ENV_H__
#define _ENV_H__


int env_match(char *argv, int n, const char *env);
void print_all_env(void);
int put_env(int argc, char *argv[]);
int do_printenv(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[]);
int do_setenv(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[]);
char *getenv (char *name);


#endif