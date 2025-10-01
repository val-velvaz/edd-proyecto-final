#include <stdexcept>
#include "BigInt.hpp"


BigInt::BigInt(unsigned long long n = 0) {}

BigInt::BigInt(long long n){
    if (n > 0) {
        this->mySign = positive;
    } else if (n < 0) {
        this->mySign = negative;
        n = -n;
    } else {
        this->mySign = zero;
    }

    if (n == 0) {
        // se recorre en orden inverso
        // el digito en la posicion 0 del vector es el de las unidades
        this->myDigits.push_back(0);
    } else {
        while (n > 0) {
            this->myDigits.push_back(n % 10);
            n /= 10;
        }
    }
    this->myNumDigits = this->myDigits.size();
}

std::string BigInt::toString() const {
    std::string result = "";
    if (mySign == negative) {
        result += "-";
    }
    // recorrer el numero en orden inverso
    for(auto it = this->myDigits.rbegin(); it != myDigits.rend(); it++) {
        result += (*it + '0');
    }
    return result;
}

void BigInt::Print(std::ostream& os) const {
    os << toString();
}




