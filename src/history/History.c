#include <stdio.h>
#include <stdlib.h>
#include <linux/limits.h>
#include <string.h>

#include "History.h"
#include "../config/ExistsInConfig.h"

char* LocateHs() {
  char* homeDir = getenv("HOME") ? getenv("HOME") : ".";
  const char* localDir = ".local/share";

  char* localShare = malloc(PATH_MAX);
  char* hsPath = malloc(PATH_MAX);

  if (localShare == NULL || hsPath == NULL) {
    perror("malloc failed");
    free(localShare);
    free(hsPath);
    return NULL;
  }

  snprintf(localShare, PATH_MAX, "%s/%s", homeDir, localDir);
  snprintf(hsPath, PATH_MAX, "%s/.plushhs", localShare);

  free(localShare);
  return hsPath;
}

int CreateHistoryFile() {
  char* hsPath = LocateHs();
  if (hsPath == NULL) {
    return 1;
  }

  if (!ExistsInConfig(hsPath)) {
    FILE* file = fopen(hsPath, "w");
    if (file == NULL) {
      perror("fopen failed");
      free(hsPath);
      return 1;
    }
    fclose(file);
  }

  free(hsPath);
  return 0;
}

int WriteInHistory(const char* command) {
  char* hsPath = LocateHs();
  if (hsPath == NULL) {
    return 1;
  }

  FILE* file = fopen(hsPath, "a");
  if (file == NULL) {
    perror("fopen failed");
    free(hsPath);
    return 1;
  }

  fprintf(file, "%s", command);
  fclose(file);

  free(hsPath);
  return 0;
}
