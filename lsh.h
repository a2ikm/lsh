#ifndef LSH_H
#define LSH_H

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/// util.c

typedef struct {
  void **data;
  int capacity;
  int len;
} Vector;

Vector *vec_new(void);
void vec_free(Vector *v);
void vec_push(Vector *v, void *e);
void *vec_pop(Vector *v);

/// builtin.c

typedef int (*lsh_builtin_func) (Vector *);
lsh_builtin_func lsh_find_builtin_func(char *name);

/// parser.c

typedef struct {
  Vector *args;
} Command;

typedef struct {
  Vector *commands;
} Program;

void program_free(Program *p);

Program *lsh_parse(char *line);

#endif
