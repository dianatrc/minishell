/*
** EPITECH PROJECT, 2026
** MINISHELL 1
** File description:
** Input parsing and command execution flow
*/

#include "../include/functions.h"

static int count(char *str, char *separator)
{
    int count = 0;
    char *copy = NULL;
    char *token = NULL;

    if (!str)
        return 0;
    copy = my_strdup(str);
    token = strtok(copy, separator);
    while (token) {
        count++;
        token = strtok(NULL, separator);
    }
    free(copy);
    return count;
}

char **transform_to_string_array(char *str, char *separator)
{
    char **arg = malloc(sizeof(char *) * (count(str, separator) + 1));
    int index = 0;
    char *token = NULL;

    if (!arg) {
        perror("malloc error transform");
        exit(84);
    }
    token = strtok(str, separator);
    while (token) {
        arg[index] = my_strdup(token);
        index++;
        token = strtok(NULL, separator);
    }
    arg[index] = NULL;
    return arg;
}

char **parse_command(char **arg, char **copy_env, char *line, int *last_return)
{
    if (my_strcmp(arg[0], "exit") == 0)
        exit_program(arg, line, copy_env, *last_return);
    if (my_strcmp(arg[0], "cd") == 0)
        return execute_cd(arg, copy_env, last_return);
    if (my_strcmp(arg[0], "setenv") == 0 && arg[1] != NULL)
        return execute_setenv(arg, copy_env, last_return);
    if (my_strcmp(arg[0], "unsetenv") == 0)
        return execute_unsetenv(arg, copy_env, last_return);
    if (my_strcmp(arg[0], "env") == 0 ||
        (my_strcmp(arg[0], "setenv") == 0 && arg[1] == NULL)) {
        print_env(copy_env, last_return);
        return copy_env;
    }
    execute_command(arg, copy_env, last_return);
    return copy_env;
}
