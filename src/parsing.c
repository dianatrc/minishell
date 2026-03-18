/*
** EPITECH PROJECT, 2026
** MINISHELL 2
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

static char **check_builtins(char **arg, char **copy_env,
    int *last_return, char *line)
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

char **parse_command(char *command, char **copy_env,
    int *last_return, char *line)
{
    char **arg;
    const char *error = "Invalid null command.\n";

    if (my_strchr(command, '|') != NULL) {
        if (pipe_syntax_error(command) == -1) {
            write(2, error, my_strlen((char *)error));
            *last_return = 1;
            return copy_env;
        }
        handle_pipe(command, copy_env, last_return);
        return copy_env;
    }
    arg = transform_to_string_array(command, " \t");
    if (arg == NULL || arg[0] == NULL) {
        free_array(arg);
        return copy_env;
    }
    copy_env = check_builtins(arg, copy_env, last_return, line);
    free_array(arg);
    return copy_env;
}
