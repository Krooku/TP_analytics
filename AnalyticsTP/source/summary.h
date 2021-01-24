#pragma once

#include "textButton.h"
#include "leftBar.h"
#include <vector>
#include <unordered_map>


enum class status { NONE, LOADING, LOADED };

class Month {
public:
	Month();
private:
	std::pair<std::string, std::vector<std::string>> errands;
	status loading;
};

class Summary : public sf::RectangleShape {
public:
	Summary(sf::RenderWindow* window, sf::Font* font,  float margin_top);
	//					drivers							{	ubezpieczalnia,     dane}
	//std::unordered_map<textButton*, Month*> dataMonths;

	void Update(sf::RenderWindow* window);
	void Render(sf::RenderWindow* window);

	~Summary();
private:
	int test;

	void changeLoadingText(std::wstring text);

	std::vector<textButton*> drivers;
	status loading;
	
	leftBar* left_bar;

	textButton* chosen;

	sf::Text* loadingText;

	sf::Clock clock;
	sf::Time timer;
};