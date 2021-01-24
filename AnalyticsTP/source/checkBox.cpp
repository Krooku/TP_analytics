#include "checkBox.h"
#include <iostream>

checkBox::checkBox(sf::Font* font, float x, float y, float width, sf::Color bg_color, const std::string title) {
	this->title = new sf::Text(title, *font, 22u);
	this->title->setOrigin(this->title->getGlobalBounds().width / 2.f, this->title->getGlobalBounds().height / 2.f);
	this->title->setPosition(x, y - width - 5.f);
	this->title->setFillColor(sf::Color::Black);

	this->setSize(sf::Vector2f(width, width));
	this->setOrigin(this->getGlobalBounds().width / 2.f, this->getGlobalBounds().height / 2.f);
	this->setPosition(x, y);
	this->setFillColor(bg_color);
	this->setOutlineColor(sf::Color::Black);
	this->setOutlineThickness(2.f);

	if ((width - 4.f) < 1.f)
		std::cout << "Error! Checkbox size is too little." << std::endl;
	this->insideShape = new sf::RectangleShape(sf::Vector2f(width / 1.5f, width / 1.5f));
	this->insideShape->setOrigin(this->insideShape->getGlobalBounds().width / 2.f, this->insideShape->getGlobalBounds().height / 2.f);
	this->insideShape->setPosition(x, y);
	this->insideShape->setFillColor(sf::Color::Green);

	this->value = false;
	this->active = true;
}

void checkBox::Render(sf::RenderWindow* window) {
	window->draw(*this);
	if(this->value)
		window->draw(*this->insideShape);
	window->draw(*this->title);
}

void checkBox::Update(sf::RenderWindow* window) {

}

bool checkBox::Hover(sf::RenderWindow* window) {
	sf::Vector2i mouse_pos = sf::Mouse::getPosition(*window);
	if ((mouse_pos.x >= static_cast<int>(this->getPosition().x - this->getGlobalBounds().width / 2.f)) && (mouse_pos.x <= static_cast<int>(this->getPosition().x + this->getGlobalBounds().width / 2.f)) &&
		(mouse_pos.y >= static_cast<int>(this->getPosition().y - this->getGlobalBounds().height / 2.f)) && (mouse_pos.y <= static_cast<int>(this->getPosition().y + this->getGlobalBounds().height / 2.f )))
		return true;
	return false;
}

bool checkBox::onClick(sf::RenderWindow* window) {
	if (this->Hover(window) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		this->value = !this->value;
		return true;
	}
	return false;
}

bool checkBox::getActive() {
	return this->active;
}

bool checkBox::getValue() {
	return this->value;
}

void checkBox::setActive() {
	this->active = !this->active;
}

checkBox::~checkBox() {
	delete this->insideShape;
	delete this->title;
}