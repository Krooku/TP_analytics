#include "navBar.h"
#include <iostream>
#include "game_state.h"

navBar::navBar(sf::Font* font, float x, float y, float width) {
	this->font = font;
	this->setPosition(x, y);
	this->setSize(sf::Vector2f(width, 50.f));
	this->setFillColor(sf::Color::Green);

	this->text = new sf::Text(L"£adowanie danych", *this->font, 30U);
	this->text->setOrigin(this->text->getGlobalBounds().width / 2.f, 0.f);
	this->text->setPosition(this->getGlobalBounds().width / 2.f, this->getPosition().y + 7.f);
	this->text->setFillColor(sf::Color::Black);

	this->selected = nullptr;
	this->newSelected = false;
	this->lClick = false;
}

void navBar::Update(sf::RenderWindow* window) {
	for (size_t i = 0u; i < this->options.size(); i++) {
		if (this->options[i]->onClick(window) && !this->lClick) {
			if (this->selected != nullptr)
				this->selected->setSelected();
			this->selected = this->options[i];
			this->selected->setSelected();
			this->newSelected = true;
			coreState.getDataBaseManager()->isResultsReady();
		}
		this->options[i]->Update(window);
	}
	this->lClick = sf::Mouse::isButtonPressed(sf::Mouse::Left);
}

void navBar::Render(sf::RenderWindow* window) {
	window->draw(*this);
	if (this->text != nullptr)
		window->draw(*this->text);
	for (size_t i = 0u; i < this->options.size(); i++) {
		window->draw(*this->options[i]);
	}
}

void navBar::loadOptions(std::vector<std::string> options) {
	this->options.clear();
	if (!options.empty()) {
		this->options.push_back(new textButton(this->font, options[0], 15.f, this->getPosition().y + 5.f, sf::Color::Black, sf::Color::Yellow, 30u));
		this->selected = this->options[0u];
		this->selected->setSelected();
		for (size_t i = 1u; i < options.size(); i++)
			this->options.push_back(new textButton(this->font, options[i], this->options[i - 1u]->getPosition().x + this->options[i - 1u]->getGlobalBounds().width + 15.f, this->getPosition().y + 5.f, sf::Color::Black, sf::Color::Yellow, 30u));
	}
	if (this->options.empty()) {
		this->text->setString(L"Brak opcji do wyœwietlenia");
	}
	else {
		delete this->text;
		this->text = nullptr;
	}
}

textButton* navBar::getSelected() {
	return this->selected;
}

bool navBar::isNewSelected() {
	return this->newSelected;
}

void navBar::setNewSelected() {
	this->newSelected = !this->newSelected;
}

void navBar::clearOptions() {
	for (size_t i = 0u; i < this->options.size(); i++) {
		delete this->options[i];
	}
	this->options.clear();
}

navBar::~navBar() {
	this->selected = nullptr;
	for (size_t i = 0u; i < this->options.size(); i++) {
		delete this->options[i];
	}
	this->options.clear();
	if (this->text != nullptr)
		delete this->text;
}