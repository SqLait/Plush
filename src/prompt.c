#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <lua5.4/lua.h>
#include <lua5.4/lualib.h>
#include <lua5.4/lauxlib.h>

#include "../config/CheckConfigFile.h"

static int SetDefaultPrompt(char*, size_t, char*);
void PrintShellPrompt();

int customOrDefault;

void PrintShellPrompt() {
  char prompt[256];
  char customPromptDir[512];
  char defaultPromptDir[] = "lua/DefaultPrompt.lua";

  const char* homeDir = getenv("HOME");
  snprintf(customPromptDir, sizeof(customPromptDir), "%s/.config/plush/prompt.lua", homeDir);

  if (!ExistsInConfig(customPromptDir)) {
    customOrDefault = 1;
    SetDefaultPrompt(prompt, sizeof(prompt), defaultPromptDir);
    printf("%s ~> ", prompt);
  } else {
    customOrDefault = 0;
    SetDefaultPrompt(prompt, sizeof(prompt), customPromptDir);
    printf("%s ~> ", prompt);
  }
}

static int SetDefaultPrompt(char* prompt, size_t promptSize, char* path) {
  lua_State* L = luaL_newstate();
  luaL_openlibs(L);

  if (luaL_loadfile(L, path) || lua_pcall(L, 0, 0, 0)) {
    printf("Cannot run Lua file: %s\n", lua_tostring(L, -1));
    lua_close(L);
    return 1;
  }
  // Push the function name onto the stack
  if (customOrDefault != 0) {
    lua_getglobal(L, "Prompt");
    lua_getfield(L, -1, "Default");
  } else {
    lua_getglobal(L, "config");
  }
  lua_pcall(L, 0, 1, 0);

  const char* lua_prompt = lua_tostring(L, -1);
  strncpy(prompt, lua_prompt, promptSize - 1);
  prompt[promptSize - 1] = '\0';

  lua_close(L);
  return 0;
}
