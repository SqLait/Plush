#define HISTORY_H
#ifdef HISTORY_H
#define INIT_HS_SIZE 30
#define LINE_SIZE 100
int CreateHistoryFile();
int WriteInHistory(const char* command);
char** ListHistory(const char* filePath);
char* GetFilePath(const char* destFile);
#endif
