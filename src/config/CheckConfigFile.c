#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "ApplyInit.h"
#include "ExistsInConfig.h"

char* path = NULL;

int CheckConfigStatus() {
  char* homeDir = getenv("HOME") ? getenv("HOME") : ".";
  const char* configDirName = ".config/plush";

  char configDirPath[PATH_MAX];
  path = malloc(PATH_MAX);
  if (path == NULL) {
    perror("malloc failed");
    return 1;
  }

  snprintf(configDirPath, sizeof(configDirPath), "%s/%s", homeDir, configDirName);
  snprintf(path, PATH_MAX, "%s/init.lua", configDirPath);

  if (!ExistsInConfig(path)) {
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
          free(path); // Free allocated memory
          return 1;
        }
      }

      // Create config file
      FILE* file = fopen(path, "w");
      if (file == NULL) {
        perror("fopen failed");
        free(path); // Free allocated memory
        return 1;
      }
      fclose(file);
      printf("Config file created successfully.\n");
    } else {
      printf("\nConfig not created. Continue with built-in config.\n");
      free(path); // Free allocated memory
      return 1;
    }
  } else {
    ApplyInit();
  }
  free(path);
  return 0;
}

