#pragma once
#include "RecipeBook.hpp"
#include <SDL3/SDL.h> // Usamos la cabecera de SDL
#include <memory>
#include <stack>

class State; // Declaración adelantada

class Game {
public:
    Game();
    ~Game(); // Añadimos un destructor para limpiar los recursos de SDL
    void run();

    void pushState(std::unique_ptr<State> state);
    void popState();
    void changeState(std::unique_ptr<State> state);
    
    // Devolvemos punteros de SDL, no objetos de SFML
    SDL_Window* getWindow() { return window; }
    SDL_Renderer* getRenderer() { return renderer; }
    RecipeBook& getRecipeBook() { return recipeBook; }

private:
    // Reemplazamos las variables de SFML con las de SDL
    SDL_Window* window;
    SDL_Renderer* renderer;

    RecipeBook recipeBook;
    std::stack<std::unique_ptr<State>> states;
};