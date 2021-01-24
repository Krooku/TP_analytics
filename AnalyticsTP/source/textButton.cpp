#include "textButton.h"
#include <iostream>

textButton::textButton(sf::Font* font, const std::string str, float x, float y, sf::Color color, sf::Color colorHover, unsigned int fontSize) {
	this->setCharacterSize(fontSize);
	this->setFont(*font);
	this->setString(str);
	this->setPosition(x, y);
	this->setFillColor(color);
	this->color = color;
	this->colorHover = colorHover;
	this->selected = false;
}

void textButton::Update(sf::RenderWindow* window) {
	if (this->Hover(window) || this->selected) {
		this->setFillColor(this->colorHover);
	}
	else {
		this->setFillColor(this->color);
	}
}

bool textButton::Hover(sf::RenderWindow* window) {
	sf::Vector2i mouse_pos = sf::Mouse::getPosition(*window);
	if ((mouse_pos.x >= static_cast<int>(this->getPosition().x)) && (mouse_pos.x <= static_cast<int>(this->getPosition().x + this->getGlobalBounds().width)) &&
		(mouse_pos.y >= static_cast<int>(this->getPosition().y)) && (mouse_pos.y <= static_cast<int>(this->getPosition().y + this->getGlobalBounds().height + this->getLocalBounds().height)))
		return true;
	return false;
}

bool textButton::onClick(sf::RenderWindow* window) {
	if (this->Hover(window) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		return true;
	return false;
}

void textButton::setSelected() {
	this->selected = !this->selected;
}

bool textButton::getSelected() {
	return this->selected;
}

textButton::~textButton() {

}