#include <luajit-2.1/luajit.h>
#include <luajit-2.1/lualib.h>
#include <luajit-2.1/lauxlib.h>

#define EXPOSE_CORE_UTILS_H
#ifdef EXPOSE_CORE_UTILS_H
int ls(lua_State* L);

static const struct luaL_Reg Plush[] = {
  {"ls", ls},
  {NULL, NULL}
};
#endif 
