#pragma once

#include <string>
#include <vector>

class BigInt {
private:
    int myNumDigits;
    std::vector<int> myDigits;
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
    BigInt();
    explicit BigInt(long long);
    explicit BigInt(const std::string&);
    BigInt(const BigInt&);
    //~BigInt();

    friend bool Null(const BigInt&);
    int operator [] (const int) const;

    BigInt& operator = (const BigInt&);

    // preincremento
    BigInt& operator ++ ();
    BigInt& operator -- ();
    // postincremento
    const BigInt operator ++ (int);
    const BigInt operator -- (int);



    friend BigInt& operator += (BigInt&, const BigInt&);
    friend BigInt& operator -= (BigInt&, const BigInt&);
    friend BigInt& operator *= (BigInt&, const BigInt&);
    friend BigInt& operator /= (BigInt&, const BigInt&);
    friend BigInt& operator %= (BigInt&, const BigInt&);

    friend BigInt operator + (const BigInt& lhs, const BigInt& rhs);
    friend BigInt operator - (const BigInt& lhs, const BigInt& rhs);
    friend BigInt operator * (const BigInt& lhs, const BigInt& rhs);
    friend BigInt operator / (const BigInt& lhs, const BigInt& rhs);
    friend BigInt operator % (const BigInt& lhs, const BigInt& rhs);
    friend BigInt operator ^ (const BigInt& lhs, const BigInt& rhs);

    friend BigInt operator * (const BigInt& lhs, int num); // pendiente
    friend BigInt operator * (int num, const BigInt& rhs); // pendiente

    friend bool operator == (const BigInt& lhs, const BigInt& rhs);
    friend bool operator < (const BigInt& lhs, const BigInt& rhs);
    friend bool operator != (const BigInt& lhs, const BigInt& rhs);
    friend bool operator > (const BigInt& lhs, const BigInt& rhs);
    friend bool operator >= (const BigInt& lhs, const BigInt& rhs);
    friend bool operator <= (const BigInt& lhs, const BigInt& rhs);

    std::string toString() const;
    int ToInt() const;
    double toDouble() const;

    int getNumDigits() const;

    bool equal(const BigInt& rhs) const;
    bool LessThan(const BigInt& rhs) const;
    void Print(std::ostream& os) const;

    friend std::ostream& operator << (std::ostream&, const BigInt&);
    friend std::istream& operator >> (std::istream&, BigInt&);

    friend BigInt sqrt(BigInt& a);
    friend BigInt Factorial(int n);
};





