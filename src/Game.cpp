#include "Game.hpp"
#include "State.hpp"
#include <SDL3_ttf/SDL_ttf.h> // <-- LÍNEA CORREGIDA
#include <memory>

Game::Game() {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_CreateWindowAndRenderer("Recetario Kawaii", 800, 600, 0, &window, &renderer);
    
    recipeBook.loadFromFile("recetario.txt");
}

Game::~Game() {
    recipeBook.saveToFile("recetario.txt");
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::pushState(std::unique_ptr<State> state) {
    states.push(std::move(state));
}

void Game::popState() {
    if (!states.empty()) {
        states.pop();
    }
}

void Game::changeState(std::unique_ptr<State> state) {
    if (!states.empty()) {
        popState();
    }
    pushState(std::move(state));
}

void Game::run() {
    bool quit = false;
    while (!quit && !states.empty()) {
        auto& currentState = states.top();

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                quit = true;
            }
            currentState->handleInput(event);
        }

        currentState->update(1.0f / 60.0f);

        SDL_SetRenderDrawColor(renderer, 255, 240, 245, 255); // Rosa pastel
        SDL_RenderClear(renderer);
        currentState->draw();
        SDL_RenderPresent(renderer);
    }
}