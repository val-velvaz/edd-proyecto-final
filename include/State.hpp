#pragma once
#include "Game.hpp"

class State {
public:
    // Virtual destructor para asegurar la limpieza correcta de las clases hijas
    virtual ~State() = default;

    // Métodos puros virtuales que cada "pantalla" del juego deberá implementar
    virtual void handleInput() = 0;
    virtual void update(float dt) = 0; // dt = delta time, para animaciones fluidas
    virtual void draw() = 0;

protected:
    // Cada estado necesita una referencia al juego principal para poder cambiar de estado
    // o acceder a la ventana.
    Game& game;

    // Constructor protegido para que solo las clases hijas puedan usarlo.
    State(Game& game) : game(game) {}
};