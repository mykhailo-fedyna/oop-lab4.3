#ifndef ARRAY_H
#define ARRAY_H

#include <stdexcept>

class Array {
protected:
    static const int MAX_SIZE = 256;
    unsigned char data[MAX_SIZE];
    int size;

public:
    Array(int n = 0, unsigned char val = 0);
    virtual ~Array() {}

    int getSize() const;
    bool rangeCheck(int index) const;
    unsigned char& operator[](int index);
    const unsigned char& operator[](int index) const;

    virtual void add(const Array& other);
    virtual void print() const;
};

#endif