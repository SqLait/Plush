#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <termios.h>

#include "constants.h"
#include "config/ApplyInit.h"
#include "history/History.h"
#include "shell.h"

int should_run = 1;

int Loop() {
  char input[MAX_INPUT_SIZE];
  char *args[MAX_TOKENS];
  int position = 0;

  struct termios oldt, newt;
  InitTermios(&oldt, &newt);

  while (should_run) {
    printf("%s", ps1);
    fflush(stdout);

    memset(input, 0, MAX_INPUT_SIZE);
    position = 0;

    HandleInput(input, &position);

    if (position == 0)
      continue;

    WriteInHistory(input);

    TokenizeInput(args, input);
    BuiltInCommand(args);
  }

  ResetTermios(&oldt);
  return 0;
}

/*Will handle input detected while typing commands*/
static void HandleInput(char* input, int* position) {
  int ch;
  while ((ch = getchar()) != EOF && ch != '\n') {
    if (ch == '\t') {
      printf("tab detected");
      continue;
    }
    if (ch == 127) {
      HandleBackspace(position);
      continue;
    }
    if (*position < MAX_INPUT_SIZE - 1) {
      input[(*position)++] = (char)ch;
      putchar(ch);
    } else {
      fprintf(stderr, "Input too long\n");
      while ((ch = getchar()) != EOF && ch != '\n');
      break;
    }
  }
  putchar('\n');
  input[*position] = '\0';
}

/*Termios does not work with backspace. This is the quick fix to that*/
static void HandleBackspace(int* position) {
  if (*position > 0) {
    (*position)--;
    printf("\b \b");
  }
}

/*Initialize a old and new terminal for the dynamic input checking*/
static void InitTermios(struct termios* oldt, struct termios* newt) {
  tcgetattr(STDIN_FILENO, oldt);
  *newt = *oldt;
  newt->c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, newt);
}

/*Will reset termios when the shell is ending*/
static void ResetTermios(struct termios* oldt) {
  tcsetattr(STDIN_FILENO, TCSANOW, oldt);
}

/*Split the text up into multiple commands*/
static void TokenizeInput(char** args, char* input) {
  int pos = 0;
  char *token = strtok(input, DELIM);
  while (token != NULL) {
    args[pos] = token;
    pos++;
    token = strtok(NULL, DELIM);
  }
  args[pos] = NULL;
}

/*Handles things like cd and other commands you might
 * want to extend in this shell*/
static void BuiltInCommand(char** args) {
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

/*Creates a fork proccess of the command you entered*/
static void ExecuteCommand(char** args) {
  pid_t pid = fork();

  if (pid == 0) {
    if (execvp(args[0], args) == -1) {
      perror("Plush");
    }
    exit(EXIT_FAILURE);
  } else if (pid < 0) {
    perror("Plush");
  } else {
    waitpid(pid, NULL, 0);
  }
}

/*Extend the use case of the cd command*/
static void ChangeDir(char* path) {
  if (path == NULL) {
    char *homeDir = getenv("HOME") ? getenv("HOME") : ".";
    ChangeDir(homeDir);
  } else {
    if (chdir(path) != 0) {
      perror("Plush");
    }
  }
}

