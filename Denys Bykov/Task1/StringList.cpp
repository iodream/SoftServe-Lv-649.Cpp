#include "StringList.hpp"

void StringListInit(StringList* list)
{
    *list = static_cast<char**>(malloc(sizeof(char**)));
    **list = nullptr;
}

void StringListDestroy(StringList* list)
{
    char** pos = *list;
    for (; *pos; pos++)
        free(*pos);
    free(*list);
    *list = nullptr;
}

int  StringListSize(StringList list)
{
    char** pos = list;
    for (; *pos; pos++) {}
    return static_cast<int>(pos - list);
}

void StringListAdd(StringList* list, char* str)
{
    char** memory_block = *list;
    int old_size = StringListSize(*list);
    int new_size = old_size + 1;
    int size_to_allocate = sizeof(char**) * (new_size + 1);
    memory_block  =
        static_cast<char**>(realloc(memory_block, size_to_allocate));
    *(memory_block + new_size - 1) = str;
    *(memory_block + new_size) = nullptr;
    *list = memory_block;
}

void StringListRemove(StringList list, const char* str)
{
    StringList pos = list;
    int sample_len = strlen(str);
    int old_size = StringListSize(list) + 1;

    int counter = 0;
    for (; *pos; pos++) {
        int slen = strlen(*pos);
        counter++;
        if (slen == sample_len) {
            if (!strcmp(str, *pos)) {
                free(*pos);
                memmove(pos, pos + 1, (old_size - counter) * sizeof(char*));
                continue;
            }
        }
    }
}

int  StringListIndexOf(StringList list, const char* str)
{
    int sample_len = strlen(str);
    char** pos = list;
    for (; *pos; pos++) {
        int slen = strlen(*pos);
        if (slen == sample_len) {
            if (!strcmp(str, *pos))
                break;
        }
    }
    return pos - list;
}

void StringListRemoveDuplicates(StringList list)
{
    char** pos = list;
    for (; *pos; pos++)
        StringListRemove(pos + 1, *pos);
}

void StringListReplaceInStrings
    (StringList list, const char* before, const char* after)
{
    int before_len = strlen(before);
    int after_len  = strlen(after);
    int size_delta = after_len - before_len;
    char** str_p = list;
    while(*str_p) {
        char* sub_str = strstr(*str_p, before);
        if (sub_str) {
            int slen = strlen(*str_p) + 1;
            char *tmp =
                static_cast<char*>(malloc((slen + size_delta) * sizeof(char)));
            int pre_len = sub_str - (*str_p);
            int suf_len = slen - pre_len - before_len;
            memcpy(tmp, *str_p, pre_len);
            memcpy(tmp + pre_len, after, after_len);
            memcpy(
                tmp + pre_len + after_len,
                (*str_p) + pre_len + before_len,
                suf_len
            );
            free(*str_p);
            *str_p = tmp;
        }
        str_p++;
    }
}

void StringListSort(StringList list)
{
    if (!(*list) && !(*(list + 1)))
        return;
    char** pos = list;
    char** last_pos = list + 1;
    for (; *(pos + 1); pos++) {
        if (0 < strcmp(*pos, *(pos + 1))) {
            char* tmp = *(pos + 1);
            *(pos + 1) = *pos;
            *pos = tmp;
        }
        last_pos = pos;
    }

    for (; last_pos != list; last_pos--) {
        pos = list;
        for (; pos != last_pos; pos++) {
            if (0 < strcmp(*pos, *(pos + 1))) {
                char* tmp = *(pos + 1);
                *(pos + 1) = *pos;
                *pos = tmp;
            }
        }
    }
}
