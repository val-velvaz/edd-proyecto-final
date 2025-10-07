#include "Game.hpp"
#include "states/MainMenuState.hpp" // Crearemos este archivo después

int main() {
    Game game;
    // El estado inicial será el menú principal
    game.pushState(std::make_unique<MainMenuState>(game));
    game.run();
    return 0;
}