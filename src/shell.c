#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <lua5.4/lua.h>
#include <lua5.4/lualib.h>
#include <lua5.4/lauxlib.h>

#include "constants.h"


void ExecuteCommand(char**);
void ChangeDir(char*);
int GetShellPrompt(char*, size_t);

void Loop() {
  char prompt[256];
  char input[MAX_INPUT_SIZE];
  char *args[MAX_TOKENS];
  char *token;
  int should_run = 1;

  GetShellPrompt(prompt, sizeof(prompt));

  while (should_run) {
    printf("%s ~> ", prompt);
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
        ChangeDir(args[1]);
      } else if (strcmp(args[0], "exit") == 0) {
        should_run = 0;
      } else {
        ExecuteCommand(args);
      }
    }
  }
}

int GetShellPrompt(char* prompt, size_t prompt_size) {
  lua_State* L = luaL_newstate();
  luaL_openlibs(L);

  if (luaL_loadfile(L, "lua/DefaultPrompt.lua") || lua_pcall(L, 0, 0, 0)) {
    printf("Cannot run Lua file: %s\n", lua_tostring(L, -1));
    lua_close(L);
    return 1;
  }

  // Push the function name onto the stack
  lua_getglobal(L, "Prompt");
  if (!lua_istable(L, -1)) {
    printf("Cannot find 'Prompt' table\n");
    lua_close(L);
    return 1;
  }

  lua_getfield(L, -1, "Default");
  if (!lua_isfunction(L, -1)) {
    printf("Cannot find 'Default' function\n");
    lua_close(L);
    return 1;
  }

  if (lua_pcall(L, 0, 1, 0) != 0) {
    printf("Error running function 'Prompt.Default': %s\n", lua_tostring(L, -1));
    lua_close(L);
    return 1;
  }

  if (!lua_isstring(L, -1)) {
    printf("Function 'Prompt.Default' must return a string\n");
    lua_close(L);
    return 1;
  }

  const char* lua_prompt = lua_tostring(L, -1);
  strncpy(prompt, lua_prompt, prompt_size - 1);
  prompt[prompt_size - 1] = '\0';  // Ensure null termination

  lua_close(L);
  return 0;
}
void ExecuteCommand(char **args) {
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

void ChangeDir(char *path) {
  if (path == NULL) {
    char *homeDir = getenv("HOME") ? getenv("HOME") : ".";
    ChangeDir(homeDir);
  } else {
    if (chdir(path) != 0) {
      perror("Plush");
    }
  }
}
