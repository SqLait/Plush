#include <lua5.4/lua.h>
#include <lua5.4/lualib.h>
#include <lua5.4/lauxlib.h>
#include <string.h>

#include "CheckConfigFile.h"
#include "ApplyInit.h"

/*Initializing config will be done here.*/
char ps1[PROMPT_SIZE];

int ApplyInit() {
  lua_State* L = luaL_newstate();
  luaL_openlibs(L);

  RegisterPlush(L);  // Register C functions

  if (luaL_loadfile(L, path) || lua_pcall(L, 0, 0, 0)) {
    printf("Cannot run init.lua: %s\n", lua_tostring(L, -1));
    lua_close(L);
    return 1;
  }

  lua_close(L);
  return 0;
}

int SetPrompt(lua_State* L) {
  if (lua_isstring(L, 1)) {
    const char* prompt = lua_tostring(L, 1);
    strncpy(ps1, prompt, sizeof(ps1) - 1);
  } else {
    strncpy(ps1, "Plush ~> ", sizeof(ps1) - 1);
  }
  ps1[sizeof(ps1) - 1] = '\0';
  return 0;
}

void RegisterPlush(lua_State* L) {
  luaL_newlib(L, Plush);  // Create a new library
  lua_setglobal(L, "Plush");  // Set the library as a global variable
}
