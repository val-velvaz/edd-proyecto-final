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

BigInt::BigInt(const BigInt& other)
    : myNumDigits(other.myNumDigits), myDigits(other.myDigits), mySign(other.mySign) {}

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

// operador de asignacion normal
BigInt& BigInt::operator  = (const BigInt& other) {
    if (this != &other) {
        this->myNumDigits = other.myNumDigits;
        this->myDigits = other.myDigits;
        this->mySign = other.mySign;
    } return *this;
}

BigInt::BigInt(BigInt&& other) noexcept 
    : myNumDigits(other.myNumDigits), 
    myDigits(std::move(other.myDigits)), // porque vector es dinamico
    mySign(other.mySign)
    {
        other.myNumDigits = 0;
        other.mySign = Sign::zero;
}

BigInt& BigInt::operator = (BigInt&& other) noexcept {
    if (this != &other) {
        this->myDigits = std::move(other.myDigits);
        this->myNumDigits = other.myNumDigits;
        this->mySign = other.mySign;

        other.myNumDigits = 0;
        other.mySign = Sign::zero;
    } return *this;
}



