#pragma once
#include "State.hpp" // <-- Asegúrate de que la ruta sea correcta

class MainMenuState : public State {
public:
    MainMenuState(Game& game);

    // ¡AQUÍ ESTÁ EL CAMBIO! Actualizamos la firma de la función.
    void handleInput(const SDL_Event& event) override;
    void update(float dt) override;
    void draw() override;

private:
    // ... el resto de las variables se quedan igual
    // (Necesitarás añadir las variables para la fuente y los textos)
};