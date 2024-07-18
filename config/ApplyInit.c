#include <lua5.4/lua.h>
#include <lua5.4/lualib.h>
#include <lua5.4/lauxlib.h>

#include "CheckConfigFile.h"

int ApplyInit(const char* path) {
  lua_State* L = luaL_newstate();
  luaL_openlibs(L);

  if (luaL_loadfile(L, path) || lua_pcall(L, 0, 0, 0)) {
    printf("Cannot run init.lua: %s\n", lua_tostring(L, -1));
    lua_close(L);
    return 1;
  }

  lua_getglobal(L, "Config");
  lua_pcall(L, 0, 0, 0);

  lua_close(L);
  return 0;
}
