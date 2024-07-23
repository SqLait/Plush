#include <stdio.h>
#include "ExistsInConfig.h"

int ExistsInConfig(const char* fpath) {
  FILE* file;
  if ((file = fopen(fpath, "r"))) {
    fclose(file);
    return 1; // File exists
  }
  return 0; // File does not exist
}
