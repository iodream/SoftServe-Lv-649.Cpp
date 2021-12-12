#include "String.hpp"

#include <cstring>
#include <cstdlib>

char*  StringCopy(const char* original)
{
    auto original_size = strlen(original) + 1;
    void* copy = malloc(original_size);

    if (copy) {
        return static_cast<char*>(memcpy (copy, original, original_size));
    }

    return nullptr;
}

void StringDestroy(char*  str)
{
    free(str);
}

bool StringEqual(const char* a, const char* b)
{
    return strcmp(a, b) == 0;
}

bool StringLess(const char* a, const char* b)
{
    return strcmp(a, b) < 0;
}

// Returns nullptr if replacement failed and no memory was allocated
char* StringReplace(char* original, const char* pattern, const char* replacement)
{
    auto original_size = strlen(original);
    auto pattern_size = strlen(pattern);
    auto replacement_size = strlen(replacement);

    if (!pattern_size) {
        return nullptr;
    }

    // Find how many time pattern occurs in original
    int pattern_count = 0;
    char* pattern_position;
    char* original_position = original;
    while (pattern_position = strstr(original_position, pattern)) {
        pattern_count++;
        original_position = pattern_position + pattern_size;
    }

    if (!pattern_count) {
        return nullptr;
    }

    auto buffer_size = original_size + pattern_count * (replacement_size - pattern_size) + 1;
    
    char* buffer = static_cast<char*>(malloc(buffer_size));

    if (!buffer_size) {
        return nullptr;
    }

    char* buffer_position = buffer;
    original_position = original;

    while (pattern_position = strstr(original_position, pattern)) {
        strncpy(buffer_position, original_position, pattern_position - original_position);
        buffer_position += pattern_position - original_position;

        strncpy(buffer_position, replacement, replacement_size);
        buffer_position += replacement_size;
        original_position = pattern_position + pattern_size;
    }

    strcpy(buffer_position, original_position);

    return buffer;
}