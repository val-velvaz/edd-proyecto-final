#pragma once
#include "../State.hpp"
#include <SFML/Graphics.hpp>

class MainMenuState : public State {
public:
    MainMenuState(Game& game);
    void handleInput() override;
    void update(float dt) override;
    void draw() override;

private:
    sf::Font font;
    sf::Text titleText;
    sf::Text viewButton;
    sf::Text addButton;
    sf::Text exitButton;

    void loadAssets();
    void setupText();
};