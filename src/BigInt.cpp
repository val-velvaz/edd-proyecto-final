#include <stdexcept>
#include <new>
#include "BigInt.hpp"


BigInt::BigInt() {}

BigInt::BigInt(long long n){
    if (n > 0) {
        this->mySign = positive;
    } else if (n < 0) {
        // pedo
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

int BigInt::getNumDigits() const {
    return static_cast<int>(myDigits.size());
}

BigInt& BigInt::operator ++ () {
    *this += BigInt(1);
    return *this;
}

BigInt& BigInt::operator -- () {
    *this -= BigInt(1);
    return *this;
}

const BigInt BigInt::operator ++ (int dummy) { //dummy porque no se va a utilizar
    BigInt oldValue = *this;
    ++*this;
    return oldValue;
}

const BigInt BigInt::operator -- (int dummy) {
    BigInt oldValue = *this;
    --*this;
    return oldValue;
}

BigInt& BigInt::operator  = (const BigInt& other) {
    if (this != &other) {
        this->myNumDigits = other.myNumDigits;
        this->myDigits = other.myDigits;
        this->mySign = other.mySign;
    } return *this;
}




