#include <termios.h>

#define SHELL_H
#ifdef SHELL_H

int Loop();
static void ExecuteCommand(char**);
static void ChangeDir(char*);
static void BuiltInCommand(char**);
static void TokenizeInput(char**, char*);
static void HandleBackspace(int*);
static void ExecuteCommandLoop(char**);
static void HandleInput(char*, int*);

static void InitTermios(struct termios*, struct termios*);
static void ResetTermios(struct termios*);
#endif
