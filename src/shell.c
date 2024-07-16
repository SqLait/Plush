#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "constants.h"


void execute_command(char**);
void change_directory(char*);

void Loop() {
  char input[MAX_INPUT_SIZE];
  char *args[MAX_TOKENS];
  char *token;
  int should_run = 1;

  while (should_run) {
    printf("Plush ~> ");
    fgets(input, MAX_INPUT_SIZE, stdin);

    // Parse the input into tokens
    int position = 0;
    token = strtok(input, DELIM);
    while (token != NULL) {
      args[position] = token;
      position++;
      token = strtok(NULL, DELIM);
    }
    args[position] = NULL;

    // Check for built-in commands
    if (args[0] != NULL) {
      if (strcmp(args[0], "cd") == 0) {
        change_directory(args[1]);
      } else if (strcmp(args[0], "exit") == 0) {
        should_run = 0;
      } else {
        execute_command(args);
      }
    }
  }
}

void execute_command(char **args) {
  pid_t pid = fork();
  if (pid == 0) {
    // Child process
    if (execvp(args[0], args) == -1) {
      perror("my_shell");
    }
    exit(EXIT_FAILURE);
  } else if (pid < 0) {
    // Error forking
    perror("my_shell");
  } else {
    // Parent process
    waitpid(pid, NULL, 0);
  }
}

void change_directory(char *path) {
  if (path == NULL) {
    fprintf(stderr, "my_shell: expected argument to \"cd\"\n");
  } else {
    if (chdir(path) != 0) {
      perror("my_shell");
    }
  }
}
