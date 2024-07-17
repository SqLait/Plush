#include "shell.h"
#include "../config/CheckConfigFile.h"

int main() {
  CheckConfigStatus();
  Loop();
  return 0;
}
