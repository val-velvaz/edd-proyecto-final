#include <iostream>
#include <stdexcept>
#include "BigInt.hpp"

void test_constructors() {
    std::cout << "--- Probando constructores ---" << std::endl;
    BigInt a(1234567890123456789LL);
    std::cout << "BigInt a(long long): " << a << std::endl;

    BigInt b("9876543210987654321");
    std::cout << "BigInt b(string): " << b << std::endl;

    BigInt c(3.14159f);
    std::cout << "BigInt c(float): " << c << std::endl;
    std::cout << std::endl;
}

void test_arithmetic() {
    std::cout << "--- Probando operaciones aritmeticas ---" << std::endl;
    BigInt a("123456789");
    BigInt b("987654321");
    BigInt c("-5000");
    BigInt d("3000");
    BigInt e("-2500");
    BigInt f("-750");

    std::cout << a << " + " << b << " = " << a + b << std::endl;
    std::cout << c << " + " << d << " = " << c + d << std::endl;
    std::cout << d << " + " << c << " = " << d + c << std::endl;
    std::cout << e << " + " << f << " = " << e + f << std::endl;

    std::cout << a << " - " << b << " = " << a - b << std::endl;
    std::cout << b << " - " << a << " = " << b - a << std::endl;

    BigInt g("12345");
    BigInt h("6789");
    std::cout << g << " * " << h << " = " << g * h << std::endl;

    BigInt i("1000");
    BigInt j("10");
    std::cout << i << " / " << j << " = " << i / j << std::endl;
    std::cout << i << " % " << j << " = " << i % j << std::endl;
    std::cout << std::endl;
}

void test_comparisons() {
    std::cout << "--- Probando comparaciones ---" << std::endl;
    BigInt a("100");
    BigInt b("100");
    BigInt c("50");
    BigInt d("-100");

    std::cout << a << " == " << b << ": " << (a == b) << std::endl;
    std::cout << a << " != " << c << ": " << (a != c) << std::endl;
    std::cout << c << " < " << a << ": " << (c < a) << std::endl;
    std::cout << a << " > " << c << ": " << (a > c) << std::endl;
    std::cout << a << " >= " << b << ": " << (a >= b) << std::endl;
    std::cout << a << " <= " << c << ": " << (a <= c) << std::endl;
    std::cout << d << " < " << c << ": " << (d < c) << std::endl;
    std::cout << std::endl;
}

void test_compound_assignment() {
    std::cout << "--- Probando operadores de asignacion compuesta ---" << std::endl;
    BigInt a("100");
    BigInt b("50");
    a += b;
    std::cout << "100 += 50: " << a << std::endl;
    a -= b;
    std::cout << a << " -= " << b << ": " << a << std::endl;
    std::cout << std::endl;
}

void test_conversions_and_functions() {
    std::cout << "--- Probando conversiones y funciones matematicas ---" << std::endl;
    BigInt num("121");
    std::cout << "sqrt(" << num << ") = " << sqrt(num) << std::endl;
    
    int fact_n = 50;
    std::cout << fact_n << "! = " << Factorial(fact_n) << std::endl;

    BigInt num_pow("3");
    BigInt exp_pow("10");
    std::cout << num_pow << " ^ " << exp_pow << " = " << (num_pow ^ exp_pow) << std::endl;
    
    BigInt large_num("12345");
    std::cout << large_num << " a int: " << large_num.ToInt() << std::endl;
    std::cout << large_num << " a double: " << large_num.toDouble() << std::endl;

    std::cout << "Abs de -100: " << BigInt("-100").Abs() << std::endl;
    std::cout << std::endl;
}

int main() {
    test_constructors();
    test_arithmetic();
    test_comparisons();
    test_compound_assignment();
    test_conversions_and_functions();

    return 0;
}