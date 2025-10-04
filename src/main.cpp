#include <iostream>
#include "BigInt.hpp"

int main() {
    // Casos básicos positivos
    BigInt a("12345");
    BigInt b("6789");

    BigInt c = a + b;  // suma
    std::cout << a.toString() << " + " << b.toString() << " = " << c.toString() << std::endl;

    a += b;  // suma con +=
    std::cout << "Despues de a += b: a = " << a.toString() << std::endl;

    // Casos con negativos
    BigInt d("-5000");
    BigInt e("3000");

    BigInt f = d + e;
    std::cout << d.toString() << " + " << e.toString() << " = " << f.toString() << std::endl;

    BigInt g = e + d;
    std::cout << e.toString() << " + " << d.toString() << " = " << g.toString() << std::endl;

    // Suma de dos negativos
    BigInt h("-2500");
    BigInt i("-750");
    BigInt j = h + i;
    std::cout << h.toString() << " + " << i.toString() << " = " << j.toString() << std::endl;

    // Suma con cero
    BigInt zero("0");
    BigInt k = j + zero;
    std::cout << j.toString() << " + 0 = " << k.toString() << std::endl;

    return 0;
}
