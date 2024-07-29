#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "constants.h"
#include "config/ApplyInit.h"
#include "history/History.h"
#include "shell.h"

void Loop() {
  char input[MAX_INPUT_SIZE];
  char *args[MAX_TOKENS];
  int position = 0;
  int should_run = 1;

  while (should_run) {
    printf("%s", ps1);
    fflush(stdout);

    memset(input, 0, MAX_INPUT_SIZE);
    position = 0;

    int ch;
    while ((ch = getchar()) != EOF && ch != '\n') {
      if (position < MAX_INPUT_SIZE - 1) {
        input[position++] = (char)ch;
      } else {
        fprintf(stderr, "Input too long\n");
        while ((ch = getchar()) != EOF && ch != '\n');
        break;
      }
    }
    input[position] = '\0';

    if (position == 0) {
      continue;
    }

    WriteInHistory(input);

    position = 0;
    char *token = strtok(input, DELIM);
    while (token != NULL) {
      args[position] = token;
      position++;
      token = strtok(NULL, DELIM);
    }
    args[position] = NULL;

    // Check for built-in commands
    if (args[0] != NULL) {
      if (strcmp(args[0], "cd") == 0) {
        ChangeDir(args[1]);
      } else if (strcmp(args[0], "exit") == 0) {
        should_run = 0;
      } else {
        ExecuteCommand(args);
      }
    }
  }
}


void ExecuteCommand(char** args) {
  pid_t pid = fork();
  if (pid == 0) {
    // Child process
    if (execvp(args[0], args) == -1) {
      perror("Plush");
    }
    exit(EXIT_FAILURE);
  } else if (pid < 0) {
    // Error forking
    perror("Plush");
  } else {
    // Parent process
    waitpid(pid, NULL, 0);
  }
}

void ChangeDir(char* path) {
  if (path == NULL) {
    char *homeDir = getenv("HOME") ? getenv("HOME") : ".";
    ChangeDir(homeDir);
  } else {
    if (chdir(path) != 0) {
      perror("Plush");
    }
  }
}
