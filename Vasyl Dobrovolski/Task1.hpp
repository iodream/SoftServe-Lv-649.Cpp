#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <stdlib.h>

void ListShow(char** list);

int StringListSize(char** list);

void CopyStr(char** node, char* text);

void StringListInit(char*** list, char* text);

void StringListAdd(char** list, char* text);

void StringListRemove(char*** list, char* text);

void StringListDestroy(char*** list);

int StringListIndexOf(char** list, char* text);

void StringListRemoveDuplicates(char** list);

void StringListSort(char** list);

void StringListReplaceInStrings(char** list, char* before, char* after);