#include <luajit-5_1-2.1/lua.h>
#include <luajit-5_1-2.1/luajit.h>
#include <luajit-5_1-2.1/lualib.h>
#include <luajit-5_1-2.1/lauxlib.h>

#include "../../history/History.h"

//main is in here for easier testing of auto completion.
int main() {
  lua_State* L;
  luaL_openlibs(L);
  
  lua_close(L);
  return 0;
}
