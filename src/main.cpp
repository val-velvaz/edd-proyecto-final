#include "Game.hpp"
#include "states/MainMenuState.hpp"

int main(int argc, char* argv[]) {
    Game game;
    game.pushState(std::make_unique<MainMenuState>(game));
    game.run();
    return 0;
}