#ifndef STRING_LIST_CPP_SENTRY
#define STRING_LIST_CPP_SENTRY

#include <stdlib.h>
#include <string.h>

using StringList = char**;

void StringListInit(StringList* list);
void StringListDestroy(StringList* list);
void StringListAdd(StringList* list, char* str);
void StringListRemove(StringList list, const char* str);
int  StringListSize(StringList list);
int  StringListIndexOf(StringList list, const char* str);
void StringListRemoveDuplicates(StringList list);
void StringListReplaceInStrings
    (StringList list, const char* before, const char* after);
void StringListSort(StringList list);

#endif
