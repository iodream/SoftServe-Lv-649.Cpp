#ifndef STRING_LIST_CPP_SENTRY
#define STRING_LIST_CPP_SENTRY

#include <stdlib.h>
#include <string.h>

/* StringList equal to null is treated as a list with the size 0. */
using StringList = char**;

/* Inserts node with value str at the end of the list or initializes it.
   Param str should be C-style string allocated on the free store.
   Returns true in the case of successful insertion.
   Returns false if head or str points to null. */
bool StringListAdd(StringList* head, char* str);

/* Frees strings and nodes and sets value of head to null.
   If head is null does nothing. */
void StringListDestroy(StringList* head);

/* Returns a node value.
   If node is null returns null. */
char* StringListGetVal(StringList node);

/* Returns a next node.
   If node is null returns null. */
StringList StringListGetNxt(StringList node);

/* Returns a list size. */
int  StringListSize(StringList head);

/* Returns a list node at index idx.
   If idx is out of range returns null. */
StringList StringListAtIndex(StringList head, unsigned int idx);

/* Returns an index of the first node with value equal to str or -1.
   If str is null returns -1. */
int  StringListIndexOf(StringList head, const char* str);

/* Removes nodes with the value equal to str from the list.
   If head or str is null does nothing. */
void StringListRemove(StringList* head, const char* str);

/* Removes duplicates form the list.  */
void StringListRemoveDuplicates(StringList head);

/* Replaces every occurrence of the before,
   in each of the string lists's strings, with after.
   If before or after is null does nothing. */
void StringListReplaceInStrings
    (StringList head, const char* before, const char* after);

/* Sorts the list in ascending order. */
void StringListSort(StringList head);

#endif
