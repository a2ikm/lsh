#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "builtin.h"

/*
  Function Declarations for builtin shell commands:
 */
int lsh_pwd(char **args);
int lsh_cd(char **args);
int lsh_help(char **args);
int lsh_exit(char **args);

/*
  List of builtin commands, followed by their corresponding functions.
 */
char *builtin_str[] = {
  "pwd",
  "cd",
  "help",
  "exit"
};

lsh_builtin_func builtin_func[] = {
  &lsh_pwd,
  &lsh_cd,
  &lsh_help,
  &lsh_exit
};

int lsh_num_builtins() {
  return sizeof(builtin_str) / sizeof(char *);
}

lsh_builtin_func lsh_find_builtin_func(char *name)
{
  int i;
  for (i = 0; i < lsh_num_builtins(); i++) {
    if (strcmp(name, builtin_str[i]) == 0) {
      return builtin_func[i];
    }
  }
  return NULL;
}

/*
  Builtin function implementations.
*/
int lsh_pwd(char **args)
{
  char *pwd = getcwd(NULL, 0);
  if (pwd == NULL) {
    perror("lsh");
  } else {
    printf("%s\n", pwd);
    free(pwd);
  }
  return 1;
}

int lsh_cd(char **args)
{
  if (args[1] == NULL) {
    fprintf(stderr, "lsh: expected argument to \"cd\"\n");
  } else {
    if (chdir(args[1]) != 0) {
      perror("lsh");
    }
  }
  return 1;
}

int lsh_help(char **args)
{
  int i;
  printf("Stephen Brennan's LSH\n");
  printf("Type program names and arguments, and hit enter.\n");
  printf("The following are built in:\n");

  for (i = 0; i < lsh_num_builtins(); i++) {
    printf("  %s\n", builtin_str[i]);
  }

  printf("Use the man command for information on other programs.\n");
  return 1;
}

int lsh_exit(char **args)
{
  return 0;
}