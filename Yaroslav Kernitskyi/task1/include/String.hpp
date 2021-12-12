#ifndef STRING_H_INCLUDED
#define STRING_H_INCLUDED

char* StringCopy(const char* original);
void StringDestroy(char*  str);

bool StringEqual(const char* a, const char* b);
bool StringLess(const char* a, const char* b);

char* StringReplace(char* original, const char* pattern, const char* replacement);

#endif // STRING_H_INCLUDED
