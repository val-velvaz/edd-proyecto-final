#include <stdexcept>
#include <new>
#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>

#include "BigInt.hpp"

bool BigInt::isNegative() const {
    if (this->mySign == negative) return true;
    return false;
}

bool BigInt::isPositive() const {
    if (this->isNegative() != true) return true;
    return false;
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
        size_t start = 0;
        
        if (str[0] == '-') {
            mySign = negative;
            start = 1;
        } else if (str[0] == '+') {
            mySign = positive;
            start = 1;
        } else {
            mySign = positive;
        }

        if (start >= str.size()) {
            throw std::invalid_argument("String vacío después del signo");
        }

        for (int i = str.size() - 1; i >= static_cast<int>(start); --i) {
            char c = str[i];
            
            if (!isdigit(c)) {
                throw std::invalid_argument("Caracter no numerico");
            }
            
            int digit = c - '0';
            myDigits.push_back(digit);
        }

        myNumDigits = static_cast<int>(myDigits.size());
        normalize();

    } catch (const std::invalid_argument& e) {
        std::cerr << "Argumento invalido: " << e.what() << std::endl;
        myDigits.clear();
        myDigits.push_back(0);
        myNumDigits = 1;
        mySign = Sign::zero;
    } catch (const std::out_of_range& e) {
        std::cerr << "Fuera de rango: " << e.what() << std::endl;
        myDigits.clear();
        myDigits.push_back(0);
        myNumDigits = 1;
        mySign = Sign::zero;
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

BigInt::BigInt(const BigInt& other)
    : myNumDigits(other.myNumDigits), myDigits(other.myDigits), mySign(other.mySign) {}

BigInt::BigInt(BigInt&& other) noexcept
    : myNumDigits(other.myNumDigits),
    myDigits(std::move(other.myDigits)),
    mySign(other.mySign)
    {
        other.myNumDigits = 0;
        other.mySign = Sign::zero;
}

bool Null(const BigInt& other) {
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
    long long uno = 1;
    *this += BigInt(uno);
    return *this;
}

BigInt& BigInt::operator -- () {
    long long uno = 1;
    *this -= BigInt(uno);
    return *this;
}

const BigInt BigInt::operator ++ (int dummy) {
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
    *this = *this % other;
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
        BigInt positiveB = b.Abs();
        result = a + positiveB;
        return result;
    }
    
    if (a.mySign == BigInt::negative && b.mySign == BigInt::positive) {
        BigInt positiveA = a.Abs();
        result = positiveA + b;
        result.mySign = BigInt::negative;
        result.normalize();
        return result;
    }
    
    if (a.mySign == BigInt::positive && b.mySign == BigInt::positive) {
        if (a.Abs() >= b.Abs()) {
            result.mySign = BigInt::positive;
            int borrow = 0;
            
            for (size_t i = 0; i < a.myDigits.size(); ++i) {
                int diff = a.myDigits[i] - borrow;
                if (i < b.myDigits.size()) {
                    diff -= b.myDigits[i];
                }
                
                if (diff < 0) {
                    diff += 10;
                    borrow = 1;
                } else {
                    borrow = 0;
                }
                
                result.myDigits.push_back(diff);
            }
        } else {
            result.mySign = BigInt::negative;
            int borrow = 0;
            
            for (size_t i = 0; i < b.myDigits.size(); ++i) {
                int diff = b.myDigits[i] - borrow;
                if (i < a.myDigits.size()) {
                    diff -= a.myDigits[i];
                }
                
                if (diff < 0) {
                    diff += 10;
                    borrow = 1;
                } else {
                    borrow = 0;
                }
                
                result.myDigits.push_back(diff);
            }
        }
    }
    
    result.normalize();
    return result;
}

BigInt operator * (const BigInt& a, const BigInt& b) {
    long long cero = 0;
    if (a.mySign == BigInt::zero || b.mySign == BigInt::zero) {
        return BigInt(cero);
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
    long long cero = 0;
    if (a.Abs() < b.Abs()) {
        return BigInt(cero);
    }

    BigInt absA = a.Abs();
    BigInt absB = b.Abs();

    BigInt result;
    result.mySign = BigInt::positive;
    BigInt currentDividend;
    currentDividend.mySign = BigInt::positive;

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

    result.myNumDigits = result.myDigits.size();
    
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
    
    result.normalize();
    return result;
}

BigInt operator ^ (const BigInt& a, const BigInt& b) {
    BigInt base = a;
    BigInt exp = b;
    
    if (b.isNegative()) {
        long long uno = 1;
        BigInt one(uno);
        if (a.Abs() == one) {
            return one;
        }
        long long cero = 0;
        return BigInt(cero);
    }
    
    if (exp.mySign == BigInt::zero) {
        long long uno = 1;
        return BigInt(uno);
    }
    
    if (base.mySign == BigInt::zero) {
        long long cero = 0;
        return BigInt(cero);
    }
    
    long long uno = 1;
    BigInt one(uno);
    if (base == one) {
        return one;
    }
    
    long long menosUno = -1;
    BigInt negOne(menosUno);
    if (base == negOne) {
        return exp.isOdd() ? negOne : one;
    }
    
    BigInt result(uno);
    BigInt absExp = exp.Abs();
    BigInt currentBase = base.Abs();
    
    long long cero = 0;
    BigInt zero(cero);
    long long dos = 2;
    BigInt two(dos);
    
    while (absExp > zero) {
        if (absExp.isOdd()) {
            result = result * currentBase;
        }
        currentBase = currentBase * currentBase;
        absExp = absExp / two;
    }
    
    if (a.isNegative() && b.isOdd()) {
        result.mySign = BigInt::negative;
    }
    
    return result;
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

    for (int i = myDigits.size() - 1; i >= 0; --i) {
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
    if (myNumDigits > 10 || (myNumDigits == 10 && myDigits[9] > 2)) {
        throw std::overflow_error("Conversion to int would overflow");
    }
    int result = 0;
    for (size_t i = 0; i < myDigits.size(); ++i) {
        result += myDigits[i] * pow(10, i);
    }

    if (mySign == negative) {
        return -result;
    }
    return result;
}

double BigInt::toDouble() const {
    double result = 0.0;
    for (size_t i = 0; i < myDigits.size(); ++i) {
        result += myDigits[i] * pow(10, i);
    }

    if (mySign == negative) {
        return -result;
    }
    return result;
}

int BigInt::getNumDigits() const {
    return static_cast<int>(myDigits.size());
}

int BigInt::compare(const BigInt& other) const {
    if (mySign != other.mySign) {
        if (mySign == zero && other.mySign == zero) return 0;
        if (mySign == positive) return 1;
        if (mySign == zero) return other.mySign == positive ? -1 : 1;
        return -1;
    }
    
    if (mySign == zero) return 0;
    
    if (myNumDigits != other.myNumDigits) {
        bool isGreater = myNumDigits > other.myNumDigits;
        if (mySign == negative) isGreater = !isGreater;
        return isGreater ? 1 : -1;
    }
    
    for (int i = myNumDigits - 1; i >= 0; --i) {
        if (myDigits[i] != other.myDigits[i]) {
            bool isGreater = myDigits[i] > other.myDigits[i];
            if (mySign == negative) isGreater = !isGreater;
            return isGreater ? 1 : -1;
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
    if (a.isNegative()) {
        throw std::invalid_argument("No se puede calcular la raiz cuadrada de un numero negativo");
    }
    
    if (a.mySign == BigInt::zero) {
        long long cero = 0;
        return BigInt(cero);
    }
    
    long long uno = 1;
    BigInt one(uno);
    if (a == one) {
        return one;
    }
    
    long long diez = 10;
    BigInt ten(diez);
    if (a < ten) {
        for (long long i = 2; i <= 3; i++) {
            long long val = i;
            BigInt test(val);
            if (test * test == a) return test;
            if (test * test > a) {
                long long prevVal = i - 1;
                return BigInt(prevVal);
            }
        }
    }
    
    long long dos = 2;
    BigInt two(dos);
    BigInt x_actual = a / two;
    
    if (x_actual.mySign == BigInt::zero) {
        x_actual = one;
    }
    
    BigInt x_next;
    int maxIterations = 1000;
    int iterations = 0;
    
    while (iterations < maxIterations) {
        if (x_actual.mySign == BigInt::zero) {
            long long ceroVal = 0;
            return BigInt(ceroVal);
        }
        
        x_next = (x_actual + a / x_actual) / two;
        
        if (x_next >= x_actual) {
            break;
        }
        
        x_actual = x_next;
        iterations++;
    }
    
    BigInt candidato1 = x_actual;
    BigInt candidato2 = x_actual + one;
    
    BigInt cuadrado1 = candidato1 * candidato1;
    BigInt cuadrado2 = candidato2 * candidato2;
    
    if (cuadrado2 <= a) {
        return candidato2;
    }
    
    return candidato1;
}

BigInt Factorial(int n) {
    if (n < 0) {
        throw std::invalid_argument("Cannot compute factorial of a negative number.");
    }
    
    long long uno = 1;
    if (n == 0 || n == 1) {
        return BigInt(uno);
    }
    
    BigInt result(uno);
    
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

BigInt BigInt::random(int numDigits) {
    if (numDigits <= 0) {
        return BigInt(static_cast<long long>(0));
    }

    BigInt result;
    result.myDigits.clear();
    result.mySign = positive;
    result.myNumDigits = numDigits;

    static bool seeded = false;
    if (!seeded) {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        seeded = true;
    }

    result.myDigits.push_back(std::rand() % 9 + 1);

    for (int i = 1; i < numDigits; ++i) {
        result.myDigits.push_back(std::rand() % 10);
    }

    return result;
}
