#include <lua5.4/lua.h>
#include <lua5.4/lualib.h>
#include <lua5.4/lauxlib.h>
#include <string.h>

#include "CheckConfigFile.h"
#include "ShellVars.h"

/*Initializing config will be done here.*/
char ps1[PROMPT_SIZE];

int ApplyInit(const char* path) {
  lua_State* L = luaL_newstate();
  luaL_openlibs(L);

  if (luaL_loadfile(L, path) || lua_pcall(L, 0, 0, 0)) {
    printf("Cannot run init.lua: %s\n", lua_tostring(L, -1));
    lua_close(L);
    return 1;
  }

  lua_getglobal(L, "Prompt");  // Push the function onto the stack
  if (lua_isfunction(L, -1)) {
    if (lua_pcall(L, 0, 1, 0) == LUA_OK) {
      const char* temp = lua_tostring(L, -1);
      if (temp) {
        strncpy(ps1, temp, sizeof(ps1) - 1);
        ps1[sizeof(ps1) - 1] = '\0';
      }
      lua_pop(L, 1);  // Remove the result from the stack
    } else {
      printf("Error running function 'Prompt': %s\n", lua_tostring(L, -1));
      lua_pop(L, 1);  // Remove error message from the stack
    }
  } else {
    strncpy(ps1, "Plush ~> ", sizeof(ps1) - 1);
    ps1[sizeof(ps1) - 1] = '\0';
  }

  lua_close(L);
  return 0;
}


void PrintPs1() {
  printf("%s", ps1);
}
