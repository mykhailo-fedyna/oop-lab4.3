#include <iostream>
#include <typeinfo>
#include <iomanip>
#include "Array.h"
#include "Fraction.h"
#include "String.h"

void testFractionAddition() {
    // Тест 1: Додавання додатніх чисел
    Fraction f1(5, 0, 2, true);  // 0.00
    f1[1] = 1; f1[2] = 8; f1[3] = 5;        // 0.12

    Fraction f2(5, 0, 2, true);   // 0.00
    f2[2] = 3; f2[3]= 8; f2[4] = 7;         // 3.04

    std::cout << "Testing Fraction addition:\n";
    std::cout << "f1 = "; f1.print();
    std::cout << "f2 = "; f2.print();

    f1.add(f2);
    std::cout << "f1 + f2 = "; f1.print();
    std::cout << "As double: " << std::fixed << std::setprecision(2) << f1.toDouble() << "\n\n";
}

int main() {
    testFractionAddition();

    Array* arr[3];

    // Створення об'єктів
    arr[0] = new Array(5, 10);
    arr[1] = new Fraction(4, 5, 2, true);
    arr[2] = new String("Hello World");

    // Вивід інформації про об'єкти
    for (int i = 0; i < 3; ++i) {
        std::cout << "Type: " << typeid(*arr[i]).name() << "\n";
        std::cout << "Value: ";
        arr[i]->print();
    }

    // Демонстрація поліморфізму
    for (int i = 0; i < 3; ++i) {
        std::cout << "\nAdding " << typeid(*arr[i]).name() << " to itself:\n";
        std::cout << "Before: ";
        arr[i]->print();
        arr[i]->add(*arr[i]);
        std::cout << "After: ";
        arr[i]->print();
    }

    // Демонстрація методів String
    String* s = dynamic_cast<String*>(arr[2]);
    if (s) {
        std::cout << "\nString operations:\n";
        std::cout << "Original: ";
        s->print();

        std::cout << "Insert 'C++ ' at position 6: ";
        s->insert("C++ ", 6);
        s->print();

        std::cout << "Remove 'C++ ': ";
        s->remove("C++ ");
        s->print();

        std::cout << "Concat with ' from C++': ";
        s->concat(String(" from C++"));
        s->print();
    }

    // Очищення пам'яті
    for (int i = 0; i < 3; ++i) {
        delete arr[i];
    }

    return 0;
}