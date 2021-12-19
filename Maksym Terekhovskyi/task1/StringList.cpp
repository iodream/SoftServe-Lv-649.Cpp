#include "StringList.h"
#include <iostream>
using namespace std;

static const int keyIndex = 0;
static const int nextIndex = 1;

static char** NodeCreate(char* key, char** next) {
    char** node = (char**)malloc(2 * sizeof(char**));

    node[keyIndex] = key;
    node[nextIndex] = (char*)next;

    return node;
}

void StringListAdd(char*** list_ptr, char* str) {
    char** temp = NodeCreate(str, NULL);
    char*** i = list_ptr;

    for (; *i; i = (char***)((*i) + nextIndex)) {}
    *i = temp;
}

void StringListPrint(char** list) {
    for (; list; list = (char**)(*(list + nextIndex))) {
        cout << list[keyIndex] << endl;
    }
}

void StringListDestroy(char*** list_ptr) {
    char** list = *list_ptr;
    char** nextNode = nullptr;

    for (; list; list = nextNode) {
        free(list[keyIndex]);
        nextNode = (char**)list[nextIndex];
        free(list);
    }
    *list_ptr = nullptr;
}

void StringListRemove(char*** list_ptr, const char* str) {
    for (; *list_ptr; list_ptr = (char***)((*list_ptr) + nextIndex)) {
        if (strcmp((*list_ptr)[keyIndex], str) == 0) {
            char** temp = *list_ptr;
            *list_ptr = (char**)(*list_ptr)[nextIndex];
            free(temp[keyIndex]);
            free(temp);
            break;
        }
    }
}

void StringListRemoveAll(char*** list_ptr, const char* str){
    for (; *list_ptr;) {
        if (strcmp((*list_ptr)[keyIndex], str) == 0) {
            char** temp = *list_ptr;
            *list_ptr = (char**)(*list_ptr)[nextIndex];
            free(temp[keyIndex]);
            free(temp);
        }
        else {
            list_ptr = (char***)((*list_ptr) + nextIndex);
        }
    }
}


int StringListSize(char** list) {
    int size = 0;

    for (; list; list = (char**)(*(list + nextIndex))) {
        size++;
    }

    return size;
}


int StringListIndexOf(char** list, const char* str) {
    int index = 0;

    for (; list; list = (char**)(*(list + nextIndex)), index++) {
        if (strcmp((list)[keyIndex], str) == 0) {
            return index;
        }
    }

    return -1;
}