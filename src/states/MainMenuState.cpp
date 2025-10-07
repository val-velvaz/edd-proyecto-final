#include "states/MainMenuState.hpp"
// ... otros includes que necesites (iostream, etc.)

// Constructor (ejemplo)
MainMenuState::MainMenuState(Game& game) : State(game) {
    // Aquí cargarías la fuente y configurarías tus textos (botones)
}

// ¡AQUÍ ESTÁ EL CAMBIO PRINCIPAL!
void MainMenuState::handleInput(const SDL_Event& event) {
    // El bucle "while (pollEvent)" ya no está aquí.
    // Solo reaccionamos al evento que nos pasaron.
    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        if (event.button.button == SDL_BUTTON_LEFT) {
            // Revisa si el clic fue en el botón de salir
            // (Necesitarás tener una variable para el botón de salir)
            // if (exitButton.getGlobalBounds().contains(event.button.x, event.button.y)) {
            //     game.popState(); // o game.getWindow().close()
            // }
        }
    }
}

void MainMenuState::update(float dt) {
    // La lógica de hover (revisar la posición del mouse) se queda aquí
}

void MainMenuState::draw() {
    // La lógica para dibujar los textos se queda aquí
}