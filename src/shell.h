#define SHELL_H
#ifdef SHELL_H

int Loop();
static void ExecuteCommand(char**);
static void ChangeDir(char*);
static void BuiltInCommand(char**);
static void Tokenizer(char**, char*, int);
#endif
