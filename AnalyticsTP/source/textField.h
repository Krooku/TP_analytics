#pragma once

#include <SFML/Graphics.hpp>

class textField : public sf::RectangleShape {
public:
	textField(sf::Font* font, float x, float y, float width, float height, std::string placeholder, sf::Color color, sf::Color activeColor);
	~textField();

	void Update(sf::RenderWindow* window);
	void Render(sf::RenderWindow* window);
	void TextEntered(sf::Uint32 unicode);
	void setActive();
	bool verify();

	std::string getString();
private:
	std::string s_text;
	sf::String renderText;

	sf::Text* text;
	sf::Text* placeholder;
	sf::Color color;
	sf::Color activeColor;

	bool active;
	bool move_top;
	bool move_bot;
};