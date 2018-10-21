#include "lsh.h"

#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"

Vector *lsh_split_line(char *line)
{
  char *token;
  Vector *tokens = vec_new();

  token = strtok(line, LSH_TOK_DELIM);
  while (token != NULL) {
    vec_push(tokens, token);
    token = strtok(NULL, LSH_TOK_DELIM);
  }
  vec_push(tokens, NULL);
  return tokens;
}
