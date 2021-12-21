#pragma once
#include "string.h"
#include "stdlib.h"

static char** NodeCreate(char*, char**);
void StringListAdd(char***, char*);
void StringListDestroy(char***);
void StringListRemove(char***, const char*);
void StringListPrint(char**);
int StringListSize(char**);
int StringListIndexOf(char**, const char*);
void StringListRemoveAll(char*** list_ptr, const char* str);