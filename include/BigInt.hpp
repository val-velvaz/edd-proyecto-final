#pragma once

#include <string>
#include <vector>

class BigInt {
private:
    int myNumDigits;
    std::vector<char> myDigits;
    enum Sign{positive, negative, zero};
    Sign mySign; // positivo o negativo

    int numDigits() const;
    int getDigit(int value);

    void addSigDigit(int value);
    void changeDigit(int value);
    void normalize();

    bool isNegative() const;
    bool isPositive() const;
    
public:
    explicit BigInt(unsigned long long n = 0);
    explicit BigInt(long long n);
    explicit BigInt(const std::string&);
    BigInt(const BigInt&);
    //~BigInt();

    friend bool Null(const BigInt&);
    int operator [] (const int) const;

    BigInt& operator = (const BigInt&);

    BigInt& operator += (const BigInt&);
    BigInt& operator -= (const BigInt&);
    BigInt& operator *= (const BigInt&);
    BigInt& operator /= (const BigInt&);
    BigInt& operator *= (const BigInt&);

    std::string toString() const;
    int ToInt() const;
    double toDouble() const;

    bool equal(const BigInt& rhs) const;
    bool LessThan(const BigInt& rhs) const;
    void Print(std::ostream& os) const;
};

std::ostream& operator << (std::ostream&, const BigInt&);
std::istream& operator >> (std::istream&, BigInt&);

BigInt operator + (const BigInt& lhs, const BigInt& rhs);
BigInt operator - (const BigInt& lhs, const BigInt& rhs);
BigInt operator * (const BigInt& lhs, const BigInt& rhs);
BigInt operator % (const BigInt& lhs, const BigInt& rhs);
BigInt operator * (const BigInt& lhs, int num);
BigInt operator * (int num, const BigInt& rhs);

bool operator == (const BigInt& lhs, const BigInt& rhs);
bool operator < (const BigInt& lhs, const BigInt& rhs);
bool operator != (const BigInt& lhs, const BigInt& rhs);
bool operator > (const BigInt& lhs, const BigInt& rhs);
bool operator >= (const BigInt& lhs, const BigInt& rhs);
bool operator <= (const BigInt& lhs, const BigInt& rhs);