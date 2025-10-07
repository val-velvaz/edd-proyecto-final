#pragma once
#include "Game.hpp"
#include <SDL3/SDL.h> // Necesitamos incluir SDL para usar SDL_Event

class State {
public:
    virtual ~State() = default;

    // ¡AQUÍ ESTÁ EL CAMBIO! La función ahora debe aceptar un evento.
    virtual void handleInput(const SDL_Event& event) = 0;
    virtual void update(float dt) = 0;
    virtual void draw() = 0;

protected:
    Game& game;
    State(Game& game) : game(game) {}
};