#include "Fraction.h"
#include <iostream>
#include <cmath>
#include <iomanip>

Fraction::Fraction(int n, unsigned char val, int decPlaces, bool s)
    : Array(n, val), decimalPlaces(decPlaces), sign(s) {
    if (decimalPlaces >= n) {
        decimalPlaces = n > 0 ? n - 1 : 0;
    }
}

void Fraction::normalize() {
    // ������� ����������� ������ ����� (�� �������� ������� �� �������)
    for (int i = size - 1; i > 0; --i) {
        if (data[i] > 9) {
            data[i - 1] += data[i] / 10;
            data[i] %= 10;
        }
    }

    // ������� ��'����� ������� (���� ���� ����������)
    if (!sign) {
        for (int i = size - 1; i > 0; --i) {
            if (data[i] < 0) {
                data[i - 1]--;
                data[i] += 10;
            }
        }
    }
}

void Fraction::add(const Array& other) {
    const Fraction* otherFraction = dynamic_cast<const Fraction*>(&other);
    if (!otherFraction) {
        throw std::invalid_argument("Can only add Fraction to Fraction");
    }

    // ��������� ���� ����������
    if (sign == otherFraction->sign) {
        // ���� ����� ������� - ������ ������
        for (int i = 0; i < size && i < otherFraction->size; ++i) {
            data[i] += (*otherFraction)[i];
        }
    }
    else {
        // ���� ����� ��� - �������
        for (int i = 0; i < size && i < otherFraction->size; ++i) {
            data[i] -= (*otherFraction)[i];
        }
    }

    normalize();  // ���������� ���������
}

void Fraction::print() const {
    if (!sign) std::cout << "-";

    // ֳ�� �������
    for (int i = 0; i < size - decimalPlaces; ++i) {
        std::cout << (int)data[i];
    }

    // ������� �������
    if (decimalPlaces > 0) {
        std::cout << ".";
        for (int i = size - decimalPlaces; i < size; ++i) {
            std::cout << (int)data[i];
        }
    }
    std::cout << std::endl;
}

double Fraction::toDouble() const {
    double result = 0;

    // ֳ�� �������
    for (int i = 0; i < size - decimalPlaces; ++i) {
        result = result * 10 + data[i];
    }

    // ������� �������
    double fraction = 0;
    for (int i = size - decimalPlaces; i < size; ++i) {
        fraction = fraction * 10 + data[i];
    }
    fraction /= pow(10, decimalPlaces);

    result += fraction;
    return sign ? result : -result;
}