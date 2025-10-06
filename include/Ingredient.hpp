#pragma once
#include <string>
#include <iostream>

class Ingredient {
public:
    std::string name;
    std::string quantity;

    friend std::ostream& operator<<(std::ostream& os, const Ingredient& ingredient) {
        os << ingredient.name << std::endl;
        os << ingredient.quantity << std::endl;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Ingredient& ingredient) {
        std::getline(is, ingredient.name);
        std::getline(is, ingredient.quantity);
        return is;
    }
    
    std::string toString() const {
        return name + " (" + quantity + ")";
    }
};