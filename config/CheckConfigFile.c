#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "ApplyInit.h"

int ExistsInConfig(const char* fpath) {
  FILE* file;
  if ((file = fopen(fpath, "r"))) {
    fclose(file);
    return 1; // File exists
  }
  return 0; // File does not exist
}

int CheckConfigStatus() {
  char* homeDir = getenv("HOME") ? getenv("HOME") : ".";
  const char* configDirName = ".config/plush";
  const char* luaFile = "init.lua";

  char configDirPath[256];
  snprintf(configDirPath, sizeof(configDirPath), "%s/%s", homeDir, configDirName);

  char configFilePath[256];
  snprintf(configFilePath, sizeof(configFilePath), "%s/%s", configDirPath, luaFile);

  if (!ExistsInConfig(configFilePath)) {
    printf("No config file detected in ~/.config/plush.\n\nWould you like to generate one? [y/n]: ");

    char opt;
    while (1) {
      opt = getchar();
      if (opt == 'y' || opt == 'n') {
        // Clear the input buffer
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        break; // Exit the loop after valid input
      }
    }

    if (opt == 'y') {
      // Ensure directory exists
      struct stat st;
      if (stat(configDirPath, &st) == -1) {
        printf("Creating directory %s...\n", configDirPath);
        if (mkdir(configDirPath, 0700) != 0) {
          perror("mkdir failed");
          return 1;
        }
      }

      // Create config file
      FILE* file = fopen(configFilePath, "w");
      if (file == NULL) {
        perror("fopen failed");
        return 1;
      }
      fclose(file);
      printf("Config file created successfully.\n");
    } else {
      printf("\nConfig not created. Continue with built-in config.\n");
      return 1;
    }
  } else {
    printf("Config file detected in ~/.config/plush.\n");
    ApplyInit();
  }

  return 0;
}

