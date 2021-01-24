#include "textField.h"
#include <string>
#include <iostream>

textField::textField(sf::Font* font, float x, float y, float width, float height, std::string placeholder, sf::Color color, sf::Color activeColor) {
	this->setSize(sf::Vector2f(width, height));
	this->setPosition(x, y);
	this->setFillColor(color);

	this->s_text = u8"³ó¿æ";
	this->renderText = "";
	sf::String c;// (u8"³ó¿æ", std::locale("³ó¿æ"));

	c = sf::String::fromUtf8(this->s_text.begin(), this->s_text.end());
	
	this->text = new sf::Text(this->renderText, *font, 30u);
	
	std::cout << "length: " << this->text->getString().toUtf8().size() << std::endl;
	//test
	this->s_text = std::string(this->text->getString().begin(), this->text->getString().end());
	//--test

	this->text->setFillColor(sf::Color::Black);
	this->placeholder = new sf::Text(placeholder, *font, 30u);
	this->placeholder->setFillColor(sf::Color::Black);

	this->text->setPosition(x, y);
	this->placeholder->setPosition(x, y);

	this->color = color;
	this->activeColor = activeColor;

	this->active = false;
	this->move_top = false;
	this->move_bot = false;
}

void textField::Update(sf::RenderWindow* window) {
	if (this->active) {
		//todo znak zachety
		if (this->move_top) {
			if (this->placeholder->getPosition().y >= (this->getPosition().y - 23.f)) {
				this->placeholder->move(sf::Vector2f(-0.5f, -1.01f));
			}
			else {
				this->move_top = false;
			}
		}
	}
	else {
		if (this->move_bot && this->renderText.isEmpty()) {
			if (this->placeholder->getPosition().y < this->getPosition().y) {
				this->placeholder->move(sf::Vector2f(0.5f, 1.01f));
			}
			else {
				this->move_bot = false;
			}
		}
	}

}

void textField::Render(sf::RenderWindow* window) {
	window->draw(*this);

	// if (this->active || !this->s_text.empty()) {
		window->draw(*this->text);
	// }
	// else {
		window->draw(*this->placeholder);
	// }
}

void textField::TextEntered(sf::Uint32 unicode) {
	if (this->active) {
		char32_t z = static_cast<char32_t>(unicode);

		if (unicode == 8u && !this->renderText.isEmpty()) {
			this->renderText.erase(this->renderText.getSize() - 1u, 1u);
			this->text->setString(this->renderText);
		}
		else if ((unicode != 8u) && (unicode != 9u)) {
			this->renderText += z;
			this->text->setString(this->renderText);

		}
	}
}

void textField::setActive() {
	if (this->active) {
		this->setFillColor(this->color);
		this->move_bot = true;
	}
	else {
		this->setFillColor(this->activeColor);
		this->move_top = true;
	}
	this->active = !this->active;
}

bool textField::verify() {
	if (this->s_text.empty())
		return true;
	return true;
}

std::string textField::getString() {
	std::basic_string u8string = this->renderText.toUtf8();
	/*std::string retString = u8"";
	for (size_t i = 0u; i < u8string.size(); i++) {
		std::wcout << static_cast<char>(u8string[i]) << std::endl;
		retString += static_cast<char>(u8string[i]);
	}*/

	//return retString;
	std::string str(u8string.begin(), u8string.end());
	return str;
}

textField::~textField() {
	delete this->text;
	delete this->placeholder;
}