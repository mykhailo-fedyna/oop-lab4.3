#include <iostream>
#include <cstring>
#include <typeinfo>
#include <limits>

class Array {
protected:
    unsigned char* arr;
    size_t size;
    static const size_t MAX_SIZE = 256;

public:
    Array(size_t n = 0, unsigned char value = 0) : size(n) {
        if (n > MAX_SIZE) {
            throw std::out_of_range("Size exceeds maximum allowed size");
        }
        arr = new unsigned char[n];
        for (size_t i = 0; i < n; ++i) {
            arr[i] = value;
        }
    }

    virtual ~Array() {
        delete[] arr;
    }

    unsigned char& operator[](size_t index) {
        rangeCheck(index);
        return arr[index];
    }

    const unsigned char& operator[](size_t index) const {
        rangeCheck(index);
        return arr[index];
    }

    virtual void addElements(const Array& other) {
        if (size != other.size) {
            throw std::invalid_argument("Array sizes must match");
        }
        for (size_t i = 0; i < size; ++i) {
            arr[i] += other.arr[i];
        }
    }

protected:
    void rangeCheck(size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
    }
};

class Fraction : public Array {
private:
    int fractionalDigits;
    bool sign;

public:
    Fraction(size_t n, int fracDigits, bool s = true)
        : Array(n, 0), fractionalDigits(fracDigits), sign(s) {}

    void addElements(const Array& other) override {
        if (typeid(*this) != typeid(other)) {
            throw std::invalid_argument("Only fractions can be added to fractions");
        }
        Array::addElements(other);
    }

    void inputData() {
        std::cout << "Enter sign (+ for positive, - for negative): ";
        char s;
        std::cin >> s;
        sign = (s == '+');

        std::cout << "Enter number of fractional digits: ";
        std::cin >> fractionalDigits;

        std::cout << "Enter " << size << " elements for the fraction: ";
        for (size_t i = 0; i < size; ++i) {
            int value;
            std::cin >> value;
            arr[i] = static_cast<unsigned char>(value);
        }
    }

    void display() const {
        std::cout << (sign ? "+" : "-");
        for (size_t i = 0; i < size; ++i) {
            std::cout << static_cast<int>(arr[i]);
            if (i == fractionalDigits - 1) std::cout << ".";
        }
        std::cout << std::endl;
    }
};

class String : public Array {
public:
    String(size_t maxLen = MAX_SIZE) : Array(maxLen) {}

    void inputData() {
        std::cout << "Enter a string: ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очищення буферу
        char temp[MAX_SIZE];
        std::cin.getline(temp, MAX_SIZE);

        size_t len = std::strlen(temp);
        if (len >= MAX_SIZE) {
            throw std::out_of_range("String too long");
        }
        arr[0] = len; // Length stored in the 0th element
        std::memcpy(arr + 1, temp, len);
    }

    const char* getString() const {
        return reinterpret_cast<const char*>(arr + 1);
    }

    size_t length() const {
        return arr[0];
    }

    void findSubstring(const char* substring) const {
        const char* str = getString();
        const char* found = std::strstr(str, substring);
        if (found) {
            std::cout << "Substring found at position: "
                << (found - str) << std::endl;
        }
        else {
            std::cout << "Substring not found" << std::endl;
        }
    }

    void deleteSubstring(const char* substring) {
        char* str = const_cast<char*>(getString());
        char* found = std::strstr(str, substring);
        if (found) {
            size_t len = std::strlen(substring);
            std::memmove(found, found + len, std::strlen(found + len) + 1);
            arr[0] -= len;
        }
    }

    void insertSubstring(const char* substring, size_t pos) {
        char* str = const_cast<char*>(getString());
        size_t subLen = std::strlen(substring);
        size_t curLen = length();

        if (pos > curLen || curLen + subLen >= MAX_SIZE) {
            throw std::out_of_range("Invalid position or substring too long");
        }

        std::memmove(str + pos + subLen, str + pos, curLen - pos + 1);
        std::memcpy(str + pos, substring, subLen);
        arr[0] += subLen;
    }

    void concatenate(const String& other) {
        size_t curLen = length();
        size_t otherLen = other.length();

        if (curLen + otherLen >= MAX_SIZE) {
            throw std::out_of_range("Resulting string too long");
        }

        std::memcpy(arr + 1 + curLen, other.getString(), otherLen + 1);
        arr[0] += otherLen;
    }
    void display() const {
        std::cout << "String: " << getString() << std::endl;
    }
};

int main() {
    try {
        // Fraction
        size_t n;
        std::cout << "Enter size of the fraction array: ";
        std::cin >> n;

        Fraction frac(n, 2);
        frac.inputData();
        frac.display();

        // String
        String str;
        str.inputData();
        str.display();

        str.findSubstring("lo");
        str.deleteSubstring("lo");
        std::cout << "After deletion: ";
        str.display();

        str.insertSubstring("TEST", 2);
        std::cout << "After insertion: ";
        str.display();

        String str2;
        str2.inputData();
        str.concatenate(str2);
        std::cout << "After concatenation: ";
        str.display();

    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
