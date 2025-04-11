#ifndef FRACTION_H
#define FRACTION_H

#include "Array.h"
#include <string>

class Fraction : public Array {
private:
    int decimalPlaces;
    bool sign;

    void normalize();  // ����������� ����� (������� ������� ��� �����������)

public:
    Fraction(int n = 0, unsigned char val = 0, int decPlaces = 2, bool s = true);
    void add(const Array& other) override;
    void print() const override;

    // ����������� � double ��� ����������
    double toDouble() const;
};

#endif