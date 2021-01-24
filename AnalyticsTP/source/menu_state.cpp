#include "menu_state.h"
#include <iostream>

#include "insert_state.h"
#include "list_state.h"

void menu_state::Initialize(sf::RenderWindow* window) {
	this->font = new sf::Font();

	if (!this->font->loadFromFile("Fonts/Roboto-Light.ttf")) {
		std::cerr << "Cannt load the font" << std::endl;
		return;
	}
	this->title = new sf::Text("TRANSPOL", *this->font, 48U);
	this->title->setOrigin(this->title->getGlobalBounds().width / 2.f, this->title->getGlobalBounds().height / 2.f);
	this->title->setPosition(static_cast<float>(window->getSize().x / 2u), 40.f);

	this->insertErrand = new textButton(this->font, "Dodaj zlecenie", 70.f, 180.f, sf::Color::Black, sf::Color::Yellow, 30u);
	this->listErrand = new textButton(this->font, "Podsumowania", 70.f, 250.f, sf::Color::Black, sf::Color::Yellow, 30u);

	this->lClick = false;
}
void menu_state::Update(sf::RenderWindow* window) {
	this->insertErrand->Update(window);
	this->listErrand->Update(window);

	if (this->insertErrand->onClick(window) && !this->lClick) {
		std::cout << "insertErrand" << std::endl;
		coreState.setState(new insert_state());
	}
	else if (this->listErrand->onClick(window) && !this->lClick) {
		std::cout << "listErrand" << std::endl;
		coreState.setState(new list_state());
	}

	this->lClick = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
}
void menu_state::Render(sf::RenderWindow* window) {
	window->draw(*this->title);
	window->draw(*this->insertErrand);
	window->draw(*this->listErrand);
}
void menu_state::Destroy(sf::RenderWindow* window) {
	delete this->title;
	delete this->insertErrand;
	delete this->listErrand;

	delete this->font;
}