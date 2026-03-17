/*
** EPITECH PROJECT, 2026
** MINISHELL 1
** File description:
** Minishell 1 project
*/

#include "../include/functions.h"

void my_putchar(char c)
{
    write(1, &c, 1);
}

void my_putstr(char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        my_putchar(str[i]);
    }
}

void free_array(char **arg)
{
    if (arg == NULL)
        return;
    for (int i = 0; arg[i] != NULL; i++) {
        free(arg[i]);
    }
    free(arg);
}

static char **get_env_copy(char **env)
{
    int i = 0;
    char **copy_env = NULL;

    while (env[i])
        i++;
    copy_env = malloc(sizeof(char *) * (i + 1));
    if (!copy_env) {
        perror("malloc copy_env");
        exit(84);
    }
    for (int j = 0; j < i; j++) {
        copy_env[j] = my_strdup(env[j]);
    }
    copy_env[i] = NULL;
    return copy_env;
}

static char **process_line(char *line, char **copy_env, int *last_return)
{
    char **arg = NULL;
    int len = my_strlen(line);

    if (len > 0 && line[len - 1] == '\n')
        line[len - 1] = '\0';
    arg = transform_to_string_array(line, " \t");
    if (arg[0] == NULL) {
        free(arg);
        return copy_env;
    }
    copy_env = parse_command(arg, copy_env, line, last_return);
    free_array(arg);
    return copy_env;
}

int main(int argc, char **argv, char **env)
{
    char *line = NULL;
    const char *prompt = "$> ";
    char **copy_env = get_env_copy(env);
    size_t line_length = 0;
    int last_return = 0;

    (void)argc;
    (void)argv;
    signal(SIGINT, SIG_IGN);
    while (1) {
        if (isatty(0))
            write(1, prompt, my_strlen((char *)prompt));
        if (getline(&line, &line_length, stdin) == -1)
            break;
        copy_env = process_line(line, copy_env, &last_return);
    }
    free(line);
    free_array(copy_env);
    return last_return;
}
