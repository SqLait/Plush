#include <stdio.h>

int ExistsInConfig(const char *fname) {
  FILE *file;
  char path[1024];

  snprintf(path, sizeof(path), ".config/plush/%s", fname);

  if ((file = fopen(path, "r"))) {
    fclose(file);
    return 1;
  }
  return 0;
}

void ApplyConfig() {
}
