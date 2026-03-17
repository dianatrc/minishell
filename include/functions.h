/*
** EPITECH PROJECT, 2026
** MINISHELL 1
** File description:
** Header file for functions and for includes
*/

#ifndef FUNCTIONS_H_
    #define FUNCTIONS_H_

    #include <stdlib.h>
    #include <stdio.h>
    #include <unistd.h>
    #include <string.h>
    #include <sys/wait.h>
    #include <signal.h>
    #include <sys/stat.h>
    #include <errno.h>

// my_lib.c
void my_putchar(char c);
int my_strlen(char *s);
void my_putstr(char *str);
char *my_strdup(char *src);
int my_strcmp(char *str1, char *str2);
int my_strncmp(char *str1, char *str2, int n);
// my_lib2.c
char *my_strcat(char *dest, char *src);
char *my_strchr(char *str, char c);
// builtins.c
void print_env(char **env, int *last_return);
void exit_program(char **arg, char *line, char **copy_env, int last_return);
char **execute_setenv(char **arg, char **copy_env, int *last_return);
char **execute_unsetenv(char **arg, char **copy_env, int *last_return);
// cd.c
char **execute_cd(char **arg, char **copy_env, int *last_return);
// exec.c
void execute_command(char **arg, char **env, int *last_return);
// env_utils.c
char *build_env_variable(char *name, char *value);
int get_env_var_index(char **copy_env, char *name);
int is_name_valid(char *name);
char **add_to_env(char **copy_env, char *new_var);
void detele_env_var(char **copy_env, int index);
// parsing
char **parse_command(char **arg, char **copy_env, char *line, int *last_return);
// main
char **transform_to_string_array(char *str, char *separator);
void free_array(char **arg);

#endif
