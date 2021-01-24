#pragma once
#include <SFML/Graphics.hpp>


class textButton : public sf::Text {
public:
	textButton(sf::Font* font, const std::string str, float x, float y, sf::Color color, sf::Color colorHover, unsigned int fontSize);
	~textButton();

	void Update(sf::RenderWindow* window);
	bool onClick(sf::RenderWindow* window);

	void setSelected();
	bool getSelected();

private:
	sf::Color color;
	sf::Color colorHover;

	bool Hover(sf::RenderWindow* window);
	bool selected;
};