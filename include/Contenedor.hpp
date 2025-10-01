#pragma once

#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <string>

#include "BigInt.hpp"

class Contenedor {
private:
    std::vector<BigInt> data;
    
public:
    Contenedor();
    Contenedor(const Contenedor&);

    Contenedor& operator = (const Contenedor&);

    void add(const BigInt&);
    void del(const BigInt&);
    void sort();
    void writeToDisk(const std::string&);
    void readFromDisk(const std::string&);

    std::string toString() const;

    BigInt& findData(const BigInt&);
};