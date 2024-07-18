#define SHELL_VARS_H
#ifdef SHELL_VARS_H
#define PROMPT_SIZE 256

extern char ps1[PROMPT_SIZE];
extern int silenceInit;

void PrintPs1();
#endif
