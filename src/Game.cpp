#include "Game.hpp"
#include "State.hpp"

Game::Game() : window(sf::VideoMode(800, 600), "Recetario Kawaii") {
    window.setFramerateLimit(60);
    // Cargar recetas desde el disco al iniciar
    recipeBook.loadFromFile("recetario.txt");
}

void Game::pushState(std::unique_ptr<State> state) {
    states.push(std::move(state));
}

void Game::popState() {
    // Guardar recetas al salir del juego
    recipeBook.saveToFile("recetario.txt");
    states.pop();
}

void Game::changeState(std::unique_ptr<State> state) {
    if (!states.empty()) {
        states.pop();
    }
    pushState(std::move(state));
}

void Game::run() {
    sf::Clock clock;

    while (window.isOpen() && !states.empty()) {
        float dt = clock.restart().asSeconds();

        // Manejar eventos, actualizar y dibujar el estado actual
        states.top()->handleInput();
        states.top()->update(dt);
        
        window.clear(sf::Color(255, 240, 245)); // Un color de fondo rosa pastel
        states.top()->draw();
        window.display();
    }
}