#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "textButton.h"

class navBar : public sf::RectangleShape {
public:
	navBar(sf::Font* font, float x, float y, float width);
	~navBar();

	void Update(sf::RenderWindow* window);
	void Render(sf::RenderWindow* window);

	void loadOptions(std::vector<std::string> options);

	textButton* getSelected();

	bool isNewSelected();
	void setNewSelected();

	void clearOptions();

private:
	sf::Font* font;
	sf::Text* text;


	std::vector<textButton*> options;
	textButton* selected;
	bool newSelected;

	bool lClick;
};