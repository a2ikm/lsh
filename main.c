#include "lsh.h"

int lsh_launch(Vector *args)
{
  pid_t pid, wpid;
  int status;

  pid = fork();
  if (pid == 0) {
    // Child process
    if (execvp((char *)args->data[0], (char **)args->data) == -1) {
      perror("lsh");
    }
    exit(EXIT_FAILURE);
  } else if (pid < 0) {
    // Error forking
    perror("lsh");
  } else {
    // Parent process
    do {
      wpid = waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }

  return 1;
}

int lsh_execute(Command *c)
{
  lsh_builtin_func f;

  if (c->args->data[0] == NULL) {
    // An empty command was entered.
    return 1;
  }

  f = lsh_find_builtin_func(c->args->data[0]);
  if (f != NULL) {
    return f(c->args);
  }

  return lsh_launch(c->args);
}

int lsh_run(Program *p)
{
  int ret;
  Command *c;
  for (int i = 0; i < p->commands->len; i++) {
    c = p->commands->data[i];
    ret = lsh_execute(c);
    if (!ret) {
      return ret;
    }
  }
  return ret;
}

#define LSH_RL_BUFSIZE 1024
char *lsh_read_line(void)
{
  int bufsize = LSH_RL_BUFSIZE;
  int position = 0;
  char *buffer = malloc(sizeof(char) * bufsize);
  int c;

  if (!buffer) {
    fprintf(stderr, "lsh: allocation error\n");
    exit(EXIT_FAILURE);
  }

  while (1) {
    // Read a character
    c = getchar();

    // If we hit EOF, replace it with a null character and return.
    if (c == EOF || c == '\n') {
      buffer[position] = '\0';
      return buffer;
    } else {
      buffer[position] = c;
    }
    position++;

    // If we have exceeded the buffer, reallocate.
    if (position >= bufsize) {
      bufsize += LSH_RL_BUFSIZE;
      buffer = realloc(buffer, bufsize);
      if (!buffer) {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }
  }
}

void lsh_loop(void)
{
  char *line;
  Program *p;
  int status;

  do {
    printf("> ");
    line = lsh_read_line();
    p = lsh_parse(line);
    status = lsh_run(p);

    free(line);
    program_free(p);
  } while (status);
}

int main(int argc, char **argv)
{
  // Load config files, if any.

  // Run command loop.
  lsh_loop();

  // Perform any shutdown/cleanup.

  return EXIT_SUCCESS;
}

