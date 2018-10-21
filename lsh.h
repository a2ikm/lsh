#ifndef LSH_H
#define LSH_H

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef int (*lsh_builtin_func) (char **);
lsh_builtin_func lsh_find_builtin_func(char *name);
char **lsh_split_line(char *line);

#endif
