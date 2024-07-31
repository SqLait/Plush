#include <linux/limits.h>
#include <luajit-5_1-2.1/lauxlib.h>
#include <luajit-5_1-2.1/lua.h>
#include <luajit-5_1-2.1/lualib.h>
#include <stdio.h>
#include <string.h>

#include "tabcomplete.h"

char* CompleteStr(char* curStr) {
  lua_State* L = luaL_newstate(); // Create a new Lua state
  if (L == NULL) {
    fprintf(stderr, "Failed to create Lua state\n");
  }

  luaL_openlibs(L); // Load Lua libraries

  // Load and run the Lua script
  if (luaL_loadfile(L, "../tab-completion/tabcomp.lua") || lua_pcall(L, 0, 0, 0)) {
    fprintf(stderr, "Cannot load tabcomplete.lua: %s\n", lua_tostring(L, -1));
    lua_close(L);
  }

  // Get the Lua function
  lua_getglobal(L, "TabCompl");
  if (!lua_isfunction(L, -1)) {
    fprintf(stderr, "TabCompl is not a function\n");
    lua_close(L);
  }

  // Push the input string as argument to the Lua function
  lua_pushstring(L, curStr);

  // Call the Lua function
  if (lua_pcall(L, 1, 1, 0) != LUA_OK) {
    fprintf(stderr, "Error in TabCompl: %s\n", lua_tostring(L, -1));
    lua_close(L);
  }

  // Check the result
  if (!lua_isstring(L, -1)) {
    fprintf(stderr, "TabCompl did not return a string\n");
    lua_close(L);
  }

  // Get the result string
  const char* result = lua_tostring(L, -1);
  strncpy(curStr, result, MAX_INPUT - 1); // Copy result to curStr
  curStr[MAX_INPUT - 1] = '\0'; // Ensure null termination

  lua_pop(L, 1); // Pop the result from the stack
  lua_close(L); // Close the Lua state

  return curStr;
}
