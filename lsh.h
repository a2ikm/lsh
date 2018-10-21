#ifndef LSH_H
#define LSH_H

typedef int (*lsh_builtin_func) (char **);
lsh_builtin_func lsh_find_builtin_func(char *name);
char **lsh_split_line(char *line);

#endif
