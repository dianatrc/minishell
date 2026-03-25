/*
** EPITECH PROJECT, 2026
** MINISHELL 2
** File description:
** Redirections handling
*/

#include "../include/functions.h"

static char *get_filename(char *str)
{
    int i = 0;
    char *filename = NULL;

    while (str[i] == ' ' || str[i] == '\t')
        i++;
    filename = my_strdup(&str[i]);
    if (!filename)
        return NULL;
    for (int j = 0; filename[j] != '\0'; j++)
        if (filename[j] == ' ' || filename[j] == '\t') {
            filename[j] = '\0';
            break;
        }
    return filename;
}

static int get_output_fd(char *ptr, char **filename)
{
    int fd = 0;

    if (*(ptr + 1) == '>') {
        *filename = get_filename(ptr + 2);
        if (!*filename)
            return -1;
        fd = open(*filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
    } else {
        *filename = get_filename(ptr + 1);
        if (!*filename)
            return -1;
        fd = open(*filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    }
    return fd;
}

static int output_redirection(char *command)
{
    char *ptr = my_strchr(command, '>');
    char *filename = NULL;
    int fd = 0;

    if (!ptr)
        return 0;
    fd = get_output_fd(ptr, &filename);
    *ptr = '\0';
    if (fd == -1) {
        perror(filename);
        free(filename);
        return -1;
    }
    dup2(fd, STDOUT_FILENO);
    close(fd);
    free(filename);
    return 0;
}

static int get_input_fd(char *ptr, char **filename)
{
    int fd = 0;

    *filename = get_filename(ptr + 1);
    if (!*filename)
        return -1;
    fd = open(*filename, O_RDONLY, 0644);
    return fd;
}

static int input_redirection(char *command)
{
    char *ptr = my_strchr(command, '<');
    char *filename = NULL;
    int fd = 0;

    if (!ptr || *(ptr + 1) == '<')
        return 0;
    fd = get_input_fd(ptr, &filename);
    *ptr = '\0';
    if (fd == -1) {
        perror(filename);
        free(filename);
        return -1;
    }
    dup2(fd, STDIN_FILENO);
    close(fd);
    free(filename);
    return 0;
}

int apply_redirection(char *command)
{
    if (input_redirection(command) == -1)
        return -1;
    if (output_redirection(command) == -1)
        return -1;
    return 0;
}
