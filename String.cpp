#include "String.h"
#include <iostream>
#include <cstring>

String::String(const char* str) {
    maxLen = MAX_SIZE - 1;
    size = strlen(str);
    if (size > maxLen) size = maxLen;
    data[0] = size;
    memcpy(data + 1, str, size);
}

int String::length() const {
    return data[0];
}

bool String::find(const char* substr) const {
    int len = strlen(substr);
    for (int i = 1; i <= length() - len + 1; ++i) {
        if (memcmp(&data[i], substr, len) == 0) return true;
    }
    return false;
}

void String::remove(const char* substr) {
    int len = strlen(substr);
    for (int i = 1; i <= length() - len + 1; ++i) {
        if (memcmp(&data[i], substr, len) == 0) {
            memmove(&data[i], &data[i + len], length() - i - len + 1);
            data[0] -= len;
            return;
        }
    }
}

void String::insert(const char* substr, int pos) {
    int len = strlen(substr);
    if (pos < 1 || pos > length() + 1) return;
    if (length() + len > maxLen) len = maxLen - length();
    memmove(&data[pos + len], &data[pos], length() - pos + 1);
    memcpy(&data[pos], substr, len);
    data[0] += len;
}

void String::concat(const String& other) {
    int len = other.length();
    if (length() + len > maxLen) len = maxLen - length();
    memcpy(&data[length() + 1], &other.data[1], len);
    data[0] += len;
}

void String::add(const Array& other) {
    concat(dynamic_cast<const String&>(other));
}

void String::print() const {
    for (int i = 1; i <= length(); ++i)
        std::cout << data[i];
    std::cout << std::endl;
}