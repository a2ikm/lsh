#include "lsh.h"

#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"

Command *command_new(void)
{
  Command *c = malloc(sizeof(Command));
  c->args = vec_new();
  return c;
}

void command_free(Command *c)
{
  vec_free(c->args);
  free(c);
}

Program *program_new(void)
{
  Program *p = malloc(sizeof(Program));
  p->commands = vec_new();
  return p;
}

void program_free(Program *p)
{
  for (int i = 0; i < p->commands->len; i++) {
    command_free(p->commands->data[i]);
  }
  vec_free(p->commands);
  free(p);
}

Program *lsh_parse(char *line)
{
  char *token;
  char *part;
  Command *c = NULL;
  Program *p = program_new();

  while ((part = strsep(&line, ";")) != NULL) {
    while ((token = strsep(&part, LSH_TOK_DELIM)) != NULL) {
      if (strcmp(token, "") == 0) {
        continue;
      }
      if (c == NULL) {
        c = command_new();
        vec_push(p->commands, c);
      }
      vec_push(c->args, token);
    }
    if (c != NULL) {
      vec_push(c->args, NULL);
      c = NULL;
    }
  }

  return p;
}
