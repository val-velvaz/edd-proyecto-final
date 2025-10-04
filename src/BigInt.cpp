#include <stdexcept>
#include <new>
#include <iostream>
#include <string>
#include <algorithm>

#include "BigInt.hpp"

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

void BigInt::normalize() {
    if (myDigits.empty()) {
        myDigits.push_back(0);
        myNumDigits = 1;
        mySign = Sign::zero;
        return;
    }

    while (myDigits.size() > 1 && myDigits.back() == 0) {
        myDigits.pop_back();
    }

    myNumDigits = myDigits.size();

    if (myNumDigits == 1 && myDigits[0] == 0) {
        mySign = Sign::zero;
    }
}

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

BigInt::BigInt(const std::string& str) {
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

BigInt::BigInt(const float& f) {
    long long n = static_cast<long long>(f);
    if (n > 0) {
        this->mySign = positive;
    } else if (n < 0) {
        this->mySign = negative;
        n = -n;
    } else {
        this->mySign = zero;
    }
    if (n == 0) {
        this->myDigits.push_back(0);
    } else {
        while (n > 0) {
            this->myDigits.push_back(n % 10);
            n /= 10;
        }
    }
    this->myNumDigits = this->myDigits.size();
    this->normalize();
}

// constructor copia
BigInt::BigInt(const BigInt& other)
    : myNumDigits(other.myNumDigits), myDigits(other.myDigits), mySign(other.mySign) {}

// cosas por movimiento
BigInt::BigInt(BigInt&& other) noexcept
    : myNumDigits(other.myNumDigits),
    myDigits(std::move(other.myDigits)), // porque vector es dinamico
    mySign(other.mySign)
    {
        other.myNumDigits = 0;
        other.mySign = Sign::zero;
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

// operador de asignacion normal
BigInt& BigInt::operator  = (const BigInt& other) {
    if (this != &other) {
        this->myNumDigits = other.myNumDigits;
        this->myDigits = other.myDigits;
        this->mySign = other.mySign;
    } return *this;
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

BigInt& BigInt::operator += (const BigInt& other) {
    *this = *this + other;
    return *this;
}

BigInt& BigInt::operator -= (const BigInt& other) {
    *this = *this - other;
    return *this;
}

BigInt& BigInt::operator *= (const BigInt& other) {
    *this = *this * other;
    return *this;
}

BigInt& BigInt::operator /= (const BigInt& other) {
    *this = *this / other;
    return *this;
}

BigInt& BigInt::operator %= (const BigInt& other) {
    *this = *this - other;
    return *this;
}

BigInt operator + (const BigInt& a, const BigInt& b) {
    BigInt result;

    if (a.mySign == b.mySign) {
        result.mySign = a.mySign;

        int carry = 0;
        size_t n = std::max(a.myDigits.size(), b.myDigits.size());

        for (size_t i = 0; i < n || carry; ++i) {
            int sum = carry;
            if (i < a.myDigits.size()) sum += a.myDigits[i];
            if (i < b.myDigits.size()) sum += b.myDigits[i];

            if (i < result.myDigits.size())
                result.myDigits[i] = sum % 10;
            else
                result.myDigits.push_back(sum % 10);

            carry = sum / 10;
        }
    }
    else {
        const BigInt *larger, *smaller;
        bool resultSign;

        if (a.Abs() >= b.Abs()) {
            larger = &a;
            smaller = &b;
            resultSign = a.mySign == BigInt::positive;
        } else {
            larger = &b;
            smaller = &a;
            resultSign = b.mySign == BigInt::positive;
        }

        result.mySign = resultSign ? BigInt::positive : BigInt::negative;

        int borrow = 0;
        for (size_t i = 0; i < larger->myDigits.size(); ++i) {
            int diff = larger->myDigits[i] - borrow;
            if (i < smaller->myDigits.size()) diff -= smaller->myDigits[i];

            if (diff < 0) {
                diff += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }

            result.myDigits.push_back(diff);
        }
    }
    result.normalize();
    return result;
}

BigInt operator - (const BigInt& a, const BigInt& b) {
    BigInt result;
    if (b.mySign == BigInt::negative) {
        result = a + b.Abs();
    } else {
        result = a + BigInt(-1) * b; // Placeholder
    }
    return result;
}

BigInt operator * (const BigInt& a, const BigInt& b) {
    if (a.mySign == BigInt::zero || b.mySign == BigInt::zero) {
        return BigInt(0LL);
    }

    BigInt absA = a.Abs();
    BigInt absB = b.Abs();
    BigInt result;

    result.myDigits.assign(absA.myDigits.size() + absB.myDigits.size(), 0);

    for (size_t i = 0; i < absA.myDigits.size(); ++i) {
        int carry = 0;
        for (size_t j = 0; j < absB.myDigits.size() || carry; ++j) {
            long long currentDigit = result.myDigits[i + j];
            if (j < absB.myDigits.size()) {
                currentDigit += (long long)absA.myDigits[i] * absB.myDigits[j];
            }
            currentDigit += carry;

            result.myDigits[i + j] = currentDigit % 10;
            carry = currentDigit / 10;
        }
    }

    result.myNumDigits = result.myDigits.size();

    // determinar el signo del resultado
    if (a.mySign == b.mySign) {
        result.mySign = BigInt::positive;
    } else {
        result.mySign = BigInt::negative;
    }

    result.normalize();
    return result;
}

BigInt operator / (const BigInt& a, const BigInt& b) {
    if (b.mySign == BigInt::zero) {
        throw std::invalid_argument("Division by zero");
    }
    if (a.Abs() < b.Abs()) {
        return BigInt(0LL);
    }

    BigInt absA = a.Abs();
    BigInt absB = b.Abs();

    BigInt result;
    BigInt currentDividend;

    for (int i = absA.getNumDigits() - 1; i >= 0; --i) {
        currentDividend.myDigits.insert(currentDividend.myDigits.begin(), absA.myDigits[i]);
        currentDividend.normalize();

        int count = 0;
        while (currentDividend >= absB) {
            currentDividend = currentDividend - absB;
            count++;
        }
        result.myDigits.insert(result.myDigits.begin(), count);
    }

    //signo
    if (a.mySign != b.mySign) {
        result.mySign = BigInt::negative;
    } else {
        result.mySign = BigInt::positive;
    }

    result.normalize();
    return result;
}

BigInt operator % (const BigInt& a, const BigInt& b) {
    if (b.mySign == BigInt::zero) {
        throw std::invalid_argument("Modulo by zero");
    }

    BigInt quotient = a / b;
    BigInt result = a - (quotient * b);
    
    return result;
}

BigInt operator ^ (const BigInt& a, const BigInt& b) {
    BigInt base = a;
    BigInt exp = b;
    BigInt result(1LL); // 1

    // exponente negativo y cero
    if (b.isNegative()) {
        // pendiente exponente negativos 
        if (a.Abs() == BigInt(1LL)) {
            return BigInt(1LL);
        }
        return BigInt(0LL);
    }

    if (exp.mySign == BigInt::zero) {
        return BigInt(1LL);
    }
    
    // positivo
    BigInt absExp = exp.Abs(); 

    while (absExp > BigInt(0LL)) {
        if (absExp.isOdd()) { 
            result = result * base;
        }
        base = base * base;
        absExp = absExp / BigInt(2LL); 
    }
    if (a.isNegative() && b.isOdd()) {
        result.mySign = BigInt::negative;
    } return result;
}

BigInt operator * (const BigInt& a, int num) {
    long long n = num;
    BigInt b(n);
    return a * b;
}

BigInt operator * (int num, const BigInt& a) {
    return a * num;
}

bool operator == (const BigInt& a, const BigInt& b) {
    return a.compare(b) == 0;
}

bool operator != (const BigInt& a, const BigInt& b) {
    return a.compare(b) != 0;
}

bool operator < (const BigInt& a, const BigInt& b) {
    return a.compare(b) < 0;
}

bool operator > (const BigInt& a, const BigInt& b) {
    return a.compare(b) > 0;
}

bool operator >= (const BigInt& a, const BigInt& b) {
    return a.compare(b) >= 0;
}

bool operator <= (const BigInt& a, const BigInt& b) {
    return a.compare(b) <= 0;
}

std::string BigInt::toString() const {
    std::string result = "";
    if (mySign == negative) {
        result += "-";
    }
    if (mySign == zero)  return "0";

    for (int i = myDigits.size() - 1; i >= 0; --i) { // OOOOK
        result += '0' + myDigits[i];
    }

    return result;
}

BigInt BigInt::Abs() const {
    BigInt temp = *this;
    if (temp.mySign == negative) {
        temp.mySign = positive;
    }
    temp.normalize();
    return temp;
}

int BigInt::ToInt() const {
// pendiente
}

double BigInt::toDouble() const {
// pendiente
}

int BigInt::getNumDigits() const {
    return static_cast<int>(myDigits.size());
}

int BigInt::compare(const BigInt& other) const {
    if (mySign != other.mySign) {
        return mySign == positive ? 1 : -1;
    }
    if (myNumDigits != other.myNumDigits) {
        return (myNumDigits > other.myNumDigits) ? 1 : -1;
    }
    for (int i = myNumDigits - 1; i >= 0; --i) {
        if (myDigits[i] != other.myDigits[i]) {
            return (myDigits[i] > other.myDigits[i]) ? 1 : -1;
        }
    }
    return 0;
}

bool BigInt::equal(const BigInt& other) const {
    return this->compare(other) == 0;
}

bool BigInt::LessThan(const BigInt& other) const {
    return this->compare(other) < 0;
}

bool BigInt::MoreThan(const BigInt& other) const {
    return this->compare(other) > 0;
}

void BigInt::Print(std::ostream& os) const {
    os << toString();
}

std::ostream& operator << (std::ostream& os, const BigInt& obj) {
    os << obj.toString();
    return os;
}

std::istream& operator >> (std::istream& is, BigInt& obj) {
    std::string str;
    is >> str;
    obj = BigInt(str);
    return is;
}

BigInt sqrt(BigInt& a) {
    // metodo de newton
    // lo saque de internet
    if (a.isNegative()) {
        throw std::invalid_argument("No se puede calcular la raiz negativa de un numero negativo");
    }
    if (a.mySign == BigInt::zero) {
        return BigInt(0LL);
    }
    
    BigInt x_actual;
    if (a.getNumDigits() % 2 == 0) {
        x_actual = BigInt("1" + std::string(a.getNumDigits() / 2, '0'));
    } else {
        x_actual = BigInt("3" + std::string(a.getNumDigits() / 2, '0'));
    }
    
    BigInt x_next = (x_actual + a / x_actual) / BigInt(2LL);

    while (x_next < x_actual) {
        x_actual = x_next;
        x_next = (x_actual + a / x_actual) / BigInt(2LL);
    }
    
    return x_actual;
}

BigInt Factorial(int n) {
        // para n=0 y n=1
    if (n < 0) {
        throw std::invalid_argument("Cannot compute factorial of a negative number.");
    }
    if (n == 0 || n == 1) {
        return BigInt(1LL);
    }
    BigInt result(1LL);
    
    for (int i = 2; i <= n; ++i) {
        BigInt temp(static_cast<long long>(i));
        result = result * temp;
    }
    return result;
}

int compare(const BigInt& a, const BigInt& b) {
    return a.compare(b);
}

bool BigInt::isOdd() const {
    if (myDigits.empty()) {
        return false;
    }
    return myDigits[0] % 2 != 0;
}