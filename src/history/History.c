#include <stdio.h>
#include <stdlib.h>
#include <linux/limits.h>
#include <string.h>

#include "History.h"
#include "../config/ExistsInConfig.h"

char* GetFilePath(const char* destFile) {
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
  snprintf(hsPath, PATH_MAX, "%s/%s", localShare, destFile);

  free(localShare);
  return hsPath;
}

int CreateHistoryFile() {
  char* hsPath = GetFilePath(".plushhs");
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
  char* hsPath = GetFilePath(".plushhs");
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

char** ListHistory(const char* filePath) {
  char** history = malloc(INIT_HS_SIZE * sizeof(char*));
  char line[LINE_SIZE];
  FILE* file = fopen(filePath, "r");

  int allocatedHistorySize = INIT_HS_SIZE;
  int i = 0;

  while (fgets(line, LINE_SIZE, file)) {
    if (i >= allocatedHistorySize) {
      allocatedHistorySize *= 2;
      history = realloc(history, allocatedHistorySize * sizeof(char*));
    }
    history[i] = malloc(strlen(line) + 1);
    strcpy(history[i], line);
    i++;
  }

  fclose(file);
  return history;
}
