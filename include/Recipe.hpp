#pragma once
#include <string>
#include <iostream>
#include "List.hpp"
#include "Ingredient.hpp"

enum class Category { DESAYUNO, COMIDA, CENA, NAVIDENO, NONE };

class Recipe {
public:
    std::string name;
    std::string author;
    Category category;
    int prepTime; 
    std::string procedure;
    List<Ingredient> ingredients;

    static int compareByName(const Recipe& a, const Recipe& b) {
        if (a.name < b.name) return -1;
        if (a.name > b.name) return 1;
        return 0;
    }

    static int compareByPrepTime(const Recipe& a, const Recipe& b) {
        if (a.prepTime < b.prepTime) return -1;
        if (a.prepTime > b.prepTime) return 1;
        return 0;
    }

    std::string categoryToString() const {
        switch (category) {
            case Category::DESAYUNO: return "Desayuno";
            case Category::COMIDA:   return "Comida";
            case Category::CENA:     return "Cena";
            case Category::NAVIDENO: return "Navideno";
            default: return "Sin Categoria";
        }
    }

    std::string toString() const {
        std::string result = "\n>> " + name + " <<\n";
        result += "Autor: " + author + "\n";
        result += "Categoria: " + categoryToString() + "\n";
        result += "Tiempo de Preparacion: " + std::to_string(prepTime) + " minutos\n\n";
        result += "Ingredientes:\n";
        for (int i = 0; i <= ingredients.last(); ++i) {
            result += "- " + ingredients.get(i).toString() + "\n";
        }
        result += "\nProcedimiento:\n" + procedure + "\n";
        return result;
    }
};