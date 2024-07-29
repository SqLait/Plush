#include <luajit-5_1-2.1/luajit.h>
#include <luajit-5_1-2.1/lualib.h>
#include <luajit-5_1-2.1/lauxlib.h>

void ExposeCoreUtils();


void RegisterUtils(lua_State* L) {
  //luaL_newlib(L, CoreUtils);  // Create a new library
  lua_setglobal(L, "CoreUtils");  // Set the library as a global variable
}
