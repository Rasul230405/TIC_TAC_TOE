#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <functional>
#include <string>

class Button {
private:
    sf::RectangleShape button;
    sf::Text text;

    std::function<void()> onClick;

    void handleEvent(sf::RenderWindow& window);
    void setOnclick(std::function<void()> callback);

public:
    Button(float length, float width, sf::Vector2f position, sf::Color color, std::string text_str, sf::Font& font, sf::Color text_color)
    {
        button.setSize(sf::Vector2f(length, width));
        button.setPosition(position);
        button.setFillColor(color);

        button.setOutlineThickness(10.f);
        button.setOutlineColor(sf::Color::Black);

        // configure text inside button
        text.setString(text_str);
        text.setFont(font);
        text.setCharacterSize(44);
        text.setFillColor(text_color);

        // get the text to center of button
        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        text.setPosition(position.x + length / 2.0f, position.y + width / 2.0f);
    }

    void render(sf::RenderWindow& window) const;
    bool is_clicked(sf::RenderWindow& window);
};
