#include <iostream>

#include "BigInt.hpp"

int main() {
    BigInt a(12345);

    std::cout << "numero : ";
    a.Print(std::cout);
    std::cout << std::endl;
    
    BigInt b(-3456);
    b.Print(std::cout);
    std::cout << std::endl;

    return 0;
}
