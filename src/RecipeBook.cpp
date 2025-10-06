#include "RecipeBook.hpp"
#include <fstream>
#include <iostream>


void RecipeBook::addRecipe(const Recipe& recipe) {
    recipes.add(recipes.last() + 1, recipe);
}

int RecipeBook::findRecipeByName(const std::string& name) {
    for (int i = 0; i <= recipes.last(); ++i) {
        if (recipes.get(i).name == name) {
            return i;
        }
    }
    return -1; 
}

void RecipeBook::deleteRecipeByName(const std::string& name) {
    int pos = findRecipeByName(name);
    if (pos != -1) {
        recipes.del(pos);
    }
}

void RecipeBook::deleteAllRecipes() {
    recipes.init();
}

void RecipeBook::sortRecipesByName() {
    sort(recipes, Recipe::compareByName);
}

void RecipeBook::sortRecipesByPrepTime() {
    sort(recipes, Recipe::compareByPrepTime);
}

const List<Recipe>& RecipeBook::getRecipes() const {
    return recipes;
}

Recipe& RecipeBook::getRecipe(int index) {
    return const_cast<Recipe&>(recipes.get(index));
}

void RecipeBook::saveToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo para guardar." << std::endl;
        return;
    }

    file << recipes.last() + 1 << std::endl; 
    for (int i = 0; i <= recipes.last(); ++i) {
        const auto& recipe = recipes.get(i);
        file << recipe.name << std::endl;
        file << recipe.author << std::endl;
        file << static_cast<int>(recipe.category) << std::endl;
        file << recipe.prepTime << std::endl;
        file << recipe.procedure << std::endl;
        
        file << recipe.ingredients.last() + 1 << std::endl; 
        for (int j = 0; j <= recipe.ingredients.last(); ++j) {
            file << recipe.ingredients.get(j);
        }
    }
    file.close();
}

void RecipeBook::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "No se encontró el archivo. Se creará uno nuevo al guardar." << std::endl;
        return;
    }

    deleteAllRecipes();
    int recipeCount;
    file >> recipeCount;
    file.ignore(); 

    for (int i = 0; i < recipeCount; ++i) {
        Recipe recipe;
        int categoryEnum;
        std::getline(file, recipe.name);
        std::getline(file, recipe.author);
        file >> categoryEnum;
        recipe.category = static_cast<Category>(categoryEnum);
        file >> recipe.prepTime;
        file.ignore(); 
        std::getline(file, recipe.procedure);
        
        int ingredientCount;
        file >> ingredientCount;
        file.ignore();

        for (int j = 0; j < ingredientCount; ++j) {
            Ingredient ingredient;
            file >> ingredient;
            recipe.ingredients.add(j, ingredient);
        }
        addRecipe(recipe);
    }
    file.close();
}


void RecipeBook::sort(List<Recipe>& list, int (*cmp)(const Recipe&, const Recipe&)) {
    int n = list.last();
    if (n <= 0) return;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n - i; ++j) {
            Recipe a = list.get(j);
            Recipe b = list.get(j + 1);
            if (cmp(a, b) > 0) {
                list.del(j);
                list.add(j, b);
                list.del(j + 1);
                list.add(j + 1, a);
            }
        }
    }
}