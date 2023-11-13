#ifndef _SHELL_H_
#define _SHELL_H_

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int str_len(char *str);
char *str_dup(char *str);
char *str_cpy(char *dest, char *src);
char *str_n_cpy(char *dest, char *src, int n);
int str_cmp(char *s1, char *s2);
char *str_tok(char *src, char *delim);
void handle_line(char *lineptr, char *parent, char **env);
void seperator(char *str, char *parent, char **env);
void logic_operators(char *str, char *parent, char **env);
char *paths(char **env, char *str);
char *get_env(char *env_name, char **env);
void run(char *str, char *parent, char **env);
void run_child(char *parent_name, char **argv, char **env);
void built_in_commands(char **argv, char **env, char *parent_name);
void handle_exit(char **argv, char *parent_name);
int check_digit(char *str);
int string_to_int(char *str);
int check_built_cmd(char *str);
int unset_env(char **argv, char **env, char *parent_name);
int set_env(char **argv, char **env, char *parent_name);
void handle_alias(char **argv, char *parent);
void handle_cd(char **argv, char **env, char *parent_name);
#endif
