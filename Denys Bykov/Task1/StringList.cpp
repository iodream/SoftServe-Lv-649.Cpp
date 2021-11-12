#include "StringList.hpp"

const int node_size = sizeof(char*) + sizeof(char*);

// StringList node memory layout
// char*  val
// char** next

static char** StringListGetValPtr(StringList head)
{
    return head;
}

static char*** StringListGetNxtPtr(StringList head)
{
    return reinterpret_cast<char***>(head + 1);
}

char*  StringListGetVal(StringList head)
{
    if (!head)
        return nullptr;
    return *StringListGetValPtr(head);
}

char** StringListGetNxt(StringList head)
{
    if (!head)
        return nullptr;
    return *StringListGetNxtPtr(head);
}

static char** new_node(char *val, char** nxt)
{
    char** node = static_cast<char**>(malloc(node_size));
    *(StringListGetValPtr(node)) = val;
    *(StringListGetNxtPtr(node)) = nxt;
    return node;
}

bool StringListAdd(StringList* head, char* str)
{
    if (!head || !str)
        return false;
    char*** node = head;
    for (; *node; node = StringListGetNxtPtr(*node)) {}
    *node = new_node(str, nullptr);
    return true;
}

void StringListDestroy(StringList* head)
{
    if (!head)
        return;
    char** node = *head;
    while (node) {
        char** to_free = node;
        free(StringListGetVal(node));
        node = StringListGetNxt(node);
        free(to_free);
    }
    *head = nullptr;
}

int StringListSize(StringList head)
{
    char** node = head;
    int counter = 0;
    for (; node; node = StringListGetNxt(node)) {
        counter++;
    }
    return counter;
}

StringList StringListAtIndex(StringList head, unsigned int idx)
{
    char** node = head;
    unsigned int counter = 0;
    for (; node; node = StringListGetNxt(node)) {
        if (counter == idx)
            break;
        counter++;
    }
    return node;
}

int StringListIndexOf(StringList head, const char* str)
{
    if (!str)
        return -1;
    int counter = 0;
    int sample_len = strlen(str);
    char** node = head;
    for (; node; node = StringListGetNxt(node)) {
        char* val = StringListGetVal(node);
        int slen = strlen(val);
        if (slen == sample_len) {
            if (!strcmp(str, val))
                return counter;
        }
        counter++;
    }
    return -1;
}

void StringListRemove(StringList* head, const char* str)
{
    if (!head || !str)
        return;
    int sample_len = strlen(str);
    char*** node_ptr = head;
    while (*node_ptr) {
        char* val = StringListGetVal(*node_ptr);
        int slen = strlen(val);
        if (slen == sample_len) {
            if (!strcmp(str, val)) {
                char** to_free = *node_ptr;
                *node_ptr = StringListGetNxt(*node_ptr);
                free(val);
                free(to_free);
                continue;
            }
        }
        node_ptr = StringListGetNxtPtr(*node_ptr);
    }
}

void StringListRemoveDuplicates(StringList head)
{
    if (!head)
        return;
    char** node = head;
    for (; StringListGetNxt(node); node = StringListGetNxt(node))
    {
        StringListRemove(StringListGetNxtPtr(node), StringListGetVal(node));
    }
}

void StringListReplaceInStrings
    (StringList head, const char* before, const char* after)
{
    if (!before || !after)
        return;
    int before_len = strlen(before);
    int after_len  = strlen(after);
    int size_delta = after_len - before_len;
    char** node = head;

    for (; node; node = StringListGetNxt(node)) {
        char** val_ptr = StringListGetValPtr(node);
        char* val = *val_ptr;
        char* sub_str = strstr(val, before);
        if (sub_str) {
            int slen = strlen(val) + 1;
            char *tmp =
                static_cast<char*>(malloc((slen + size_delta) * sizeof(char)));
            int pre_len = sub_str - (val);
            int suf_len = slen - pre_len - before_len;
            memcpy(tmp, val, pre_len);
            memcpy(tmp + pre_len, after, after_len);
            memcpy(
                tmp + pre_len + after_len,
                (val) + pre_len + before_len,
                suf_len
            );
            free(val);
            *val_ptr = tmp;
        }
    }
}

void StringListSort(StringList head)
{
    if (!(StringListGetNxt(head)))
        return;
    char** node = head;
    char** last = StringListGetNxt(head);
    for (; StringListGetNxt(node); node = StringListGetNxt(node)) {
        char** nxt = StringListGetNxt(node);
        if (0 < strcmp(StringListGetVal(node), StringListGetVal(nxt))) {
            char* tmp = StringListGetVal(nxt);
            *StringListGetValPtr(nxt)  = StringListGetVal(node);
            *StringListGetValPtr(node) = tmp;
        }
        last = StringListGetNxt(node);
    }

    while (last != head) {
        node = head;
        for (; StringListGetNxt(node) != last; node = StringListGetNxt(node)) {
            char** nxt = StringListGetNxt(node);
            if (0 < strcmp(StringListGetVal(node), StringListGetVal(nxt))) {
                char* tmp = StringListGetVal(nxt);
                *StringListGetValPtr(nxt)  = StringListGetVal(node);
                *StringListGetValPtr(node) = tmp;
            }
        }
        last = node;
    }
}
