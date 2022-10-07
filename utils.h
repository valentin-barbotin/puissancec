#if !defined(UTILS_H)
#define UTILS_H

#define bool int
#define true 1
#define false 0

void removeLineFeed(char* str);
const unsigned long long hash(const char* str);
int doesInclude(char** array, const char* str, const int size);
char* readFile(const char* src);
char* removeSuffix(char* src, char* suffix);

#endif // MACRO


