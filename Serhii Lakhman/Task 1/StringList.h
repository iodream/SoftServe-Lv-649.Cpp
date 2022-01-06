#pragma once
#include "string.h"
#include "stdlib.h"

static char** NodeCreate(char*, char**);
void StringListAdd(char***, char*);
void StringListRemove(char***, const char*);
void StringListPrint(char**); 
int  StringListSize(char**);
int  StringListIndexOf(char**, const char*);
void StringListDestroy(char*** list_ptr);
void StringListRemoveAll(char*** list_ptr, const char* str);
void StringListRemoveForIndex(char*** list_ptr, const int index);
void StringListReplaceInStrings(char*** list_ptr, char* before, char* after);


/*

StringList node memory layout
char *key
char ***next

*/