#include "pch.h"
#include "CppUnitTest.h"
#include "../lab4.3.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(UnitTest1)
    {
    public:

        TEST_METHOD(TestFractionDisplay)
        {
            // Тест методу display() класу Fraction
            Fraction frac(3, 1, false); // Розмір 3, 1 дробова частина, від'ємний знак
            frac[0] = 4;
            frac[1] = 5;
            frac[2] = 6;

            std::ostringstream output;
            std::streambuf* oldCoutStreamBuf = std::cout.rdbuf();
            std::cout.rdbuf(output.rdbuf());

            frac.display();

            std::cout.rdbuf(oldCoutStreamBuf);
            Assert::AreEqual("-4.56", "-4.56");
        }
    };
};
