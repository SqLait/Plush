#include "shell.h"
#include "config/CheckConfigFile.h"
#include "history/History.h"

int main() {
  CreateHistoryFile();
  CheckConfigStatus();
  Loop();
  return 0;
}
