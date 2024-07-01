#include "Button.h"

void Button::render(sf::RenderWindow& window) const {
    window.draw(button);
    window.draw(text);
}

bool Button::is_clicked(sf::RenderWindow& window) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
        sf::Vector2f mouse_posf(static_cast<float>(mouse_pos.x), static_cast<float>(mouse_pos.y));

        if (button.getGlobalBounds().contains(mouse_posf)) {
            return true;
        }
    }
    return false;
}

void Button::setOnclick(std::function<void()> callback) {
    onClick = callback;
}

void Button::handleEvent(sf::RenderWindow& window) {
    if (is_clicked(window) && onClick)
        onClick();
}