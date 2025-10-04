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
    // usar explicit para constructores de conversion
    BigInt();
    explicit BigInt(long long&); // int64_t
    explicit BigInt(const std::string&);
    explicit BigInt(const float&);
    BigInt(const BigInt&); // copiar los datos que no son dinamicos
    BigInt(BigInt&&) noexcept; // copiar los recursos dinamicos
    //~BigInt();

    friend bool Null(const BigInt&);

    int operator [] (const int) const;
    int& operator [] (const int); // poder modificar el indice

    BigInt& operator = (const BigInt&);
    BigInt& operator = (BigInt&&) noexcept;

    // preincremento
    BigInt& operator ++ ();
    BigInt& operator -- ();
    // postincremento
    const BigInt operator ++ (int);
    const BigInt operator -- (int);

    BigInt& operator += (const BigInt&);
    BigInt& operator -= (const BigInt&);
    BigInt& operator *= (const BigInt&);
    BigInt& operator /= (const BigInt&);
    BigInt& operator %= (const BigInt&);

    friend BigInt operator + (const BigInt&, const BigInt&); // static cast a bigint
    friend BigInt operator - (const BigInt&, const BigInt&);
    friend BigInt operator * (const BigInt&, const BigInt&);
    friend BigInt operator / (const BigInt&, const BigInt&);
    friend BigInt operator % (const BigInt&, const BigInt&);
    friend BigInt operator ^ (const BigInt&, const BigInt&);

    friend BigInt operator * (const BigInt&  , int num); // pendiente
    friend BigInt operator * (int num, const BigInt&); // pendiente

    friend bool operator == (const BigInt&, const BigInt&);
    friend bool operator < (const BigInt&, const BigInt&);
    friend bool operator != (const BigInt&, const BigInt&);
    friend bool operator > (const BigInt&, const BigInt&);
    friend bool operator >= (const BigInt&, const BigInt&);
    friend bool operator <= (const BigInt&, const BigInt&);

    std::string toString() const;
    int ToInt() const;
    double toDouble() const;
    BigInt Abs() const;

    int getNumDigits() const;

    bool equal(const BigInt&) const;
    bool LessThan(const BigInt&) const;
    bool MoreThan(const BigInt&) const;
    void Print(std::ostream& os) const;

    friend std::ostream& operator << (std::ostream&, const BigInt&);
    friend std::istream& operator >> (std::istream&, BigInt&);

    friend BigInt sqrt(BigInt& a);

    int compare(const BigInt&) const;
    static int compare(const BigInt&, const BigInt&);

    bool isOdd() const;
};

BigInt Factorial(int n);





