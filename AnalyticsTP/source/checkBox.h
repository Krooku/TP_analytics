#pragma once
#include <SFML/Graphics.hpp>

class checkBox : public sf::RectangleShape {
public:
	checkBox(sf::Font* font, float x, float y, float width, sf::Color bg_color, const std::string title);
	~checkBox();

	void Render(sf::RenderWindow* window);
	void Update(sf::RenderWindow* window);

	bool getActive();
	bool getValue();

	void setActive();

	bool onClick(sf::RenderWindow* window);
private:
	bool active;
	bool value;
	sf::Text* title;
	sf::RectangleShape* insideShape;

	bool Hover(sf::RenderWindow* window);
};