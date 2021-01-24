#include "leftBar.h"

leftBar::leftBar(sf::RenderWindow* window, sf::Font* font, float heigth, std::vector<textButton*> options) {
	this->setPosition(0.f, static_cast<float>(window->getSize().y) - heigth);
	this->setSize(sf::Vector2f(200.f, heigth));
	this->setFillColor(sf::Color::Blue);

	this->currentAction = Action::NONE;

	this->chosen = nullptr;
	this->isHidden = false;
}

void leftBar::Update(sf::RenderWindow* window) {
	switch (this->currentAction) {
	case Action::HIDE:
		this->AnimationHide();
		break;
	case Action::SHOW:
		this->AnimationShow();
		break;
	}
	if (this->Hover(window))
		this->Show();
	else
		this->Hide();
}
void leftBar::Render(sf::RenderWindow* window) {
	window->draw(*this);
}

bool leftBar::Hover(sf::RenderWindow* window) {
	sf::Vector2i mouse_pos = sf::Mouse::getPosition(*window);
	if ((mouse_pos.x >= static_cast<int>(this->getPosition().x)) && (mouse_pos.x <= static_cast<int>(this->getPosition().x + this->getGlobalBounds().width)) &&
		(mouse_pos.y >= static_cast<int>(this->getPosition().y)) && (mouse_pos.y <= static_cast<int>(this->getPosition().y + this->getGlobalBounds().height + this->getLocalBounds().height)))
		return true;
	return false;
}

void leftBar::Hide() {
	this->currentAction = Action::HIDE;
}

void leftBar::Show() {
	this->currentAction = Action::SHOW;
}

void leftBar::AnimationHide() {
	if (this->getPosition().x > -150.f) {
		this->move(-5.1f, 0.f);
	}
	else {
		this->isHidden = true;
		this->currentAction = Action::NONE;
	}
}

void leftBar::AnimationShow() {
	if (this->getPosition().x < 0.f) {
		this->move(5.1f, 0.f);
		if (this->getPosition().x > 0.f)
			this->setPosition(0.f, this->getPosition().y);
	}
	else {
		this->isHidden = false;
		this->currentAction = Action::NONE;
	}
}

leftBar::~leftBar() {

}