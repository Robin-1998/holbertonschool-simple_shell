#ifndef MAIN_H
#define MAIN_H

#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>

char *_strdup(char *str);
int _strcmp(char *s1, char *s2, int nbre_lettre);
int _strlen(char *str);
char *_strchr(char *s, char c);
char *_getenv(char *name, char **environ);
size_t _read_line(char **line, size_t *n);
void _fork_execve_wait(char **argument, char **environ);
extern char **environ;
char **_token_doubletableau(char *str, char *separator);
int _getpath(char **argument, char **environ);


#endif /* MAIN_H */
