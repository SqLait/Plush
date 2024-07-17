#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

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

int StartConfig() {
  if (!ExistsInConfig("config.c") || !ExistsInConfig("config.lua")) {
    printf("No config file detected in ~/.config/plush.\n\nWould you like to generate one? [y/n]: ");
    char opt = getchar();
    if (opt == 'y') {
      if (mkdir("~/.config/plush", 700) != 0) {
        return 1;
      }

      FILE *file = fopen("config.lua", "w");
      if (file == NULL) {
        perror("fopen failed");
        return 1;
      }
      return 0;

    } else if (opt == 'n'){
      printf("\nConfig not created. Continue with built-in config.");
      return 1;

    } else {
      printf("\nDefaulted to N.");
      return 1;
    }
  } else if (ExistsInConfig("config.c") || ExistsInConfig("config.lua")) {
    ApplyConfig();
  } else {
    perror("Config related issue. Can't find or init the file.");
  }
  return 0;
}
