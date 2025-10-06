#pragma once
#include "RecipeBook.hpp"

class UserInterface {
private:
    RecipeBook myBook;
    const std::string FILENAME = "recetario.txt";

    void mainMenu();
    void showRecipesMenu();
    void addRecipeMenu();
    void findRecipeMenu();
    void deleteRecipeMenu();
    void sortRecipeMenu();
    void manageIngredientsMenu();

    void showAllRecipes();
    void showFilteredRecipes();
    Category selectCategory();
    void pressEnterToContinue();

public:
    UserInterface();
    void run();
};