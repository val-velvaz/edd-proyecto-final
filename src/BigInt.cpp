#include <stdexcept>
#include <new>
#include <iostream>
#include <string>

#include "BigInt.hpp"


BigInt::BigInt() {}

BigInt::BigInt(long long& n){
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

// constructor copia
BigInt::BigInt(const BigInt& other)
    : myNumDigits(other.myNumDigits), myDigits(other.myDigits), mySign(other.mySign) {}

std::string BigInt::toString() const {
    std::string result = "";
    if (mySign == negative) {
        result += "-";
    }

    for (int d : myDigits) {   // recorrido normal
        result += '0' + d;
    }

    return result;
}

BigInt::BigInt(const std::string& str) {
    // recorrer el string y meter sus caracteres como dígitos en el vector<int>
    try {
        myDigits.clear();
         // detectar el signo
        size_t start = 0;
        if (str[0] == '-') {
            mySign = negative;
            start = 1;
        } else if (str[0] == '+') {
            mySign = positive;
            start = 1;
        } else {
            mySign = positive; // por defecto
        }

        for (auto i = start; i < str.size(); i++) {
            char c = str[i]; // obtener el caracter

            if (!isdigit(c)) {
                throw std::invalid_argument("Caracter no numerico");
            }

            int digit = c - '0';
            myDigits.push_back(digit);

            
        }
        while (myDigits.size() > 1 && myDigits[0] == 0) {
                myDigits.erase(myDigits.begin());
            }

        myNumDigits = static_cast<int>(myDigits.size());

    } catch (const std::invalid_argument& e) {
        std::cerr << "Argumento invalido: " << e.what() << std::endl;
    } catch (const std::out_of_range& e) {
        std::cerr << "Fuera de rango: " << e.what() << std::endl;
    }
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

// cosas por movimiento
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

bool BigInt::isNegative() const {
    if (this->mySign == negative) return true;
    return false;
    // return mySing == negative;
}

bool BigInt::isPositive() const {
    if (this->isNegative() != true) return true;
    return false;
    // return mySign == positive;
}

bool Null(const BigInt& other) { // para ver si es cero
    return other.mySign == BigInt::zero;
}

int BigInt::operator [] (const int index) const {
    if (myDigits.size() <= index || index < 0) {
        throw std::out_of_range("Indice fuera de rango");
    } return myDigits[index];
}

int& BigInt::operator [] (const int index) {
    if (myDigits.size() <= index || index < 0) {
        throw std::out_of_range("Indice fuera de rango");
    } return myDigits[index];
}