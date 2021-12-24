#ifndef STRINGLIST_H_INCLUDED
#define STRINGLIST_H_INCLUDED

#include "Node.hpp"

using StringList = Node;

/* Initializes list */
void StringListInit(StringList* list);
/* Destroy list and set pointer to nullptr. */
void StringListDestroy(StringList* list);

/* Inserts value at the beginning of the list (in constant time) */
void StringListPushFront(StringList* list, const char* str);
/* Inserts value at the end of the list. */
void StringListPushBack(StringList* list, const char* str);
/* Removes all occurrences of str in the list. */
void StringListRemoveAll(StringList* list, const char* str);

/* Returns the number of items in the list. */
int StringListSize(StringList list);
/* Returns the index position of the first occurrence of str in the list. */
int StringListIndexOf(StringList list, const char* str);

/* Removes duplicate entries from the list. */
void StringListRemoveDuplicates(StringList list);
/* Replaces every occurrence of the before, in each of the string lists's strings, with after. */
void StringListReplaceInStrings(StringList list, const char* before, const char* after);
/* Sorts the list of strings in ascending order */
void StringListSort(StringList list);

/* Create one element list */
StringList StringListCreateSingleton(const char* str);
/* Checks if list contains one element */
bool StringListIsSingleton(StringList head);

#endif // STRINGLIST_H_INCLUDED
