#include <luajit-5_1-2.1/luajit.h>
#include <luajit-5_1-2.1/lualib.h>
#include <luajit-5_1-2.1/lauxlib.h>

#include "../../history/History.h"

int CompareInToHs() {
  char** history = ListHistory(GetFilePath(".plushhs"));
  return 0;
}
