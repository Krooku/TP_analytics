#pragma once
#include "game_state.h"
#include "textField.h"
#include "checkBox.h"

class insert_state : public tiny_state {
public:
	void Initialize(sf::RenderWindow* window);

	void Update(sf::RenderWindow* window);

	void Render(sf::RenderWindow* window);

	void Destroy(sf::RenderWindow* window);

	void TextEntered(sf::Uint32 unicode);
private:
	sf::Font* font;

	textField* activeField;
	checkBox* taxi;

	textField* transport;

	std::vector<textField*> form;
	std::vector<textField*>::iterator it;

	bool InsertErrand();
	bool inserted;

	bool tabKey;
	bool enterKey;
	bool escKey;
	bool lClick;
};