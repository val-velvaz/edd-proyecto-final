#include "states/MainMenuState.hpp" // <-- LÍNEA CORREGIDA
#include <iostream>

MainMenuState::MainMenuState(Game& game) : State(game) {
    loadAssets();
    setupText();
}

void MainMenuState::loadAssets() {
    if (!font.loadFromFile("assets/font.ttf")) {
        std::cerr << "Error: No se pudo cargar la fuente 'assets/font.ttf'" << std::endl;
    }
}

void MainMenuState::setupText() {
    titleText.setFont(font);
    titleText.setString("Recetario Kawaii");
    titleText.setCharacterSize(50);
    titleText.setFillColor(sf::Color(255, 105, 180)); // Rosa fuerte
    // Centrar texto
    sf::FloatRect titleRect = titleText.getLocalBounds();
    titleText.setOrigin(titleRect.left + titleRect.width / 2.0f, titleRect.top + titleRect.height / 2.0f);
    titleText.setPosition(sf::Vector2f(800 / 2.0f, 150.0f));

    viewButton.setFont(font);
    viewButton.setString("Ver Recetas");
    viewButton.setCharacterSize(30);
    viewButton.setFillColor(sf::Color::Black);
    sf::FloatRect viewRect = viewButton.getLocalBounds();
    viewButton.setOrigin(viewRect.left + viewRect.width / 2.0f, viewRect.top + viewRect.height / 2.0f);
    viewButton.setPosition(sf::Vector2f(800 / 2.0f, 250.0f));

    // Repetir para los otros botones
    addButton.setFont(font);
    addButton.setString("Agregar Receta");
    addButton.setCharacterSize(30);
    addButton.setFillColor(sf::Color::Black);
    sf::FloatRect addRect = addButton.getLocalBounds();
    addButton.setOrigin(addRect.left + addRect.width / 2.0f, addRect.top + addRect.height / 2.0f);
    addButton.setPosition(sf::Vector2f(800 / 2.0f, 320.0f));


    exitButton.setFont(font);
    exitButton.setString("Salir");
    exitButton.setCharacterSize(30);
    exitButton.setFillColor(sf::Color::Black);
    sf::FloatRect exitRect = exitButton.getLocalBounds();
    exitButton.setOrigin(exitRect.left + exitRect.width / 2.0f, exitRect.top + exitRect.height / 2.0f);
    exitButton.setPosition(sf::Vector2f(800 / 2.0f, 390.0f));
}

void MainMenuState::handleInput() {
    sf::Event event;
    while (game.getWindow().pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            game.getWindow().close();
        }

        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos = game.getWindow().mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
                if (exitButton.getGlobalBounds().contains(mousePos)) {
                    game.getWindow().close();
                }
            }
        }
    }
}

void MainMenuState::update(float dt) {
    sf::Vector2f mousePos = game.getWindow().mapPixelToCoords(sf::Mouse::getPosition(game.getWindow()));
    
    // Efecto hover para botones
    if (viewButton.getGlobalBounds().contains(mousePos)) viewButton.setFillColor(sf::Color(255, 182, 193));
    else viewButton.setFillColor(sf::Color::Black);
    
    if (addButton.getGlobalBounds().contains(mousePos)) addButton.setFillColor(sf::Color(255, 182, 193));
    else addButton.setFillColor(sf::Color::Black);

    if (exitButton.getGlobalBounds().contains(mousePos)) exitButton.setFillColor(sf::Color(255, 182, 193));
    else exitButton.setFillColor(sf::Color::Black);
}

void MainMenuState::draw() {
    game.getWindow().draw(titleText);
    game.getWindow().draw(viewButton);
    game.getWindow().draw(addButton);
    game.getWindow().draw(exitButton);
}