#include "Array.h"
#include <iostream>

Array::Array(int n, unsigned char val) {
    size = (n <= MAX_SIZE) ? n : MAX_SIZE;
    for (int i = 0; i < size; ++i)
        data[i] = val;
}

int Array::getSize() const {
    return size;
}

bool Array::rangeCheck(int index) const {
    return (index >= 0 && index < size);
}

unsigned char& Array::operator[](int index) {
    if (!rangeCheck(index)) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

const unsigned char& Array::operator[](int index) const {
    if (!rangeCheck(index)) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

void Array::add(const Array& other) {
    int minSize = (size < other.size) ? size : other.size;
    for (int i = 0; i < minSize; ++i) {
        data[i] += other.data[i];
    }
}

void Array::print() const {
    for (int i = 0; i < size; ++i)
        std::cout << (int)data[i] << " ";
    std::cout << std::endl;
}