#pragma once
#include <SFML/Graphics.hpp>
#include "RecipeBook.hpp"
#include <memory>
#include <stack>

class State; // Declaración adelantada

class Game {
public:
    Game();
    void run();

    void pushState(std::unique_ptr<State> state);
    void popState();
    void changeState(std::unique_ptr<State> state);
    
    sf::RenderWindow& getWindow() { return window; }
    RecipeBook& getRecipeBook() { return recipeBook; }

private:
    sf::RenderWindow window;
    RecipeBook recipeBook;
    std::stack<std::unique_ptr<State>> states;
};