#ifndef STRING_H
#define STRING_H

#include "Array.h"
#include <cstring>

class String : public Array {
private:
    int maxLen;

public:
    String(const char* str = "");
    int length() const;
    bool find(const char* substr) const;
    void remove(const char* substr);
    void insert(const char* substr, int pos);
    void concat(const String& other);

    void add(const Array& other) override;
    void print() const override;
};

#endif