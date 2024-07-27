#include <luajit-2.1/luajit.h>
#include <luajit-2.1/lualib.h>
#include <luajit-2.1/lauxlib.h>

#define APPLY_INIT_H
#ifdef APPLY_INIT_H

#define PROMPT_SIZE 256

extern char ps1[PROMPT_SIZE];
extern int silenceInit;
extern char* path;

int ApplyInit();
int SetPrompt(lua_State* L);
void RegisterPlush(lua_State* L);

static const struct luaL_Reg Plush[] = {
  {"SetPrompt", SetPrompt},
  {NULL, NULL}
};
#endif
