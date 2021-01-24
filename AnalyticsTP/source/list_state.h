#pragma once
#include "game_state.h"
#include "navBar.h"
#include "summary.h"

class list_state : public tiny_state {
public:
	void Initialize(sf::RenderWindow* window);
	void Update(sf::RenderWindow* window);
	void Render(sf::RenderWindow* window);
	void Destroy(sf::RenderWindow* window);
private:
	enum class loadingStates { NONE, LOADING, LOADED};

	sf::Text* title;
	sf::Font* font;
	navBar* topBar;
	navBar* monthsBar;

	loadingStates loadingYears;
	loadingStates loadingMonths;
	loadingStates loadingDrivers;

	std::vector<std::string> years;
	std::vector<std::string> months;

	Summary* summary;

	bool lClick;
	bool escKey;
};