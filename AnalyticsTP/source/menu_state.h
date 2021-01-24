#pragma once

#include "game_state.h"
#include "textButton.h"

class menu_state : public tiny_state
{
public:
	void Initialize(sf::RenderWindow* window);
	void Update(sf::RenderWindow* window);
	void Render(sf::RenderWindow* window);
	void Destroy(sf::RenderWindow* window);
private:
	sf::Text* title;
	sf::Font* font;

	textButton* insertErrand;
	textButton* listErrand;

	bool lClick;
};