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
        this->myDigits.push_back(0);
    } else {
        while (n > 0) {
            this->myDigits.push_back(n % 10);
            n /= 10;
        }
    }
    this->myNumDigits = this->myDigits.size();
}

