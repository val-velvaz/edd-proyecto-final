#pragma once
#include "List.hpp"
#include "Recipe.hpp"
#include <string>

class RecipeBook {
private:
    List<Recipe> recipes;
    void sort(List<Recipe>& list, int (*cmp)(const Recipe&, const Recipe&));

public:
    void addRecipe(const Recipe& recipe);
    int findRecipeByName(const std::string& name);
    void deleteRecipeByName(const std::string& name);
    void deleteAllRecipes();

    void sortRecipesByName();
    void sortRecipesByPrepTime();
    
    const List<Recipe>& getRecipes() const;
    Recipe& getRecipe(int index);

    void saveToFile(const std::string& filename);
    void loadFromFile(const std::string& filename);
};