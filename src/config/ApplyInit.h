#include <luajit-5_1-2.1/luajit.h>
#include <luajit-5_1-2.1/lualib.h>
#include <luajit-5_1-2.1/lauxlib.h>

#include "../core-utils/core.h"

#define APPLY_INIT_H
#ifdef APPLY_INIT_H

#define PROMPT_SIZE 256

extern char ps1[PROMPT_SIZE];
extern int silenceInit;
extern char* path;

static void RegisterPlush(lua_State* L);
static void RegisterCoreUtils(lua_State* L);

int ApplyInit();
int SetPrompt(lua_State* L);

static const struct luaL_Reg Plush[] = {
  {"SetPrompt", SetPrompt},
  {NULL, NULL}
};

static const struct luaL_Reg Utils[] = {
  {"SetPrompt", SetPrompt},
  {NULL, NULL}
};
#endif
