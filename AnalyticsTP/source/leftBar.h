#pragma once
#include "textButton.h"
#include <vector>

class leftBar : public sf::RectangleShape {
public:
	leftBar(sf::RenderWindow* window, sf::Font* font, float heigth, std::vector<textButton*> options);
	~leftBar();

	void Update(sf::RenderWindow* window);
	void Render(sf::RenderWindow* window);

	void Show();
	void Hide();

	bool Hover(sf::RenderWindow* window);

private:
	enum class Action { NONE, HIDE, SHOW};
	Action currentAction;

	std::vector<textButton*> options;
	textButton* chosen;

	void AnimationShow();
	void AnimationHide();

	bool isHidden;
};