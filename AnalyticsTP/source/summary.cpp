#include "summary.h"
#include <iostream>


Summary::Summary(sf::RenderWindow* window, sf::Font* font, float margin_top) {
	this->setPosition(0.f, margin_top);
	this->setSize(sf::Vector2(static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y - margin_top)));
	this->setFillColor(sf::Color::Black);

	this->left_bar = new leftBar(window, font, this->getGlobalBounds().height, this->drivers);
	this->left_bar->Hide();

	this->loading = status::LOADING;
	this->chosen = nullptr;

	//this->dataMonths.clear();

	this->loadingText = new sf::Text(u8"£adowanie...", *font, 30u);
	this->loadingText->setOrigin(this->loadingText->getGlobalBounds().width / 2.f, this->loadingText->getGlobalBounds().height / 2.f);
	this->loadingText->setPosition(this->getGlobalBounds().width / 2.f, this->getGlobalBounds().height / 2.f);

	this->clock.restart();
	this->timer = this->clock.getElapsedTime();

	this->test = 0;
}

void Summary::changeLoadingText(std::wstring text) {
	this->loadingText->setString(sf::String(text));

	//fix_pos
	//this->loadingText->setOrigin(this->loadingText->getGlobalBounds().width / 2.f, this->loadingText->getGlobalBounds().height / 2.f);
	//this->loadingText->setPosition(this->getGlobalBounds().width / 2.f, this->getGlobalBounds().height / 2.f);
}

void Summary::Update(sf::RenderWindow* window) {
	this->left_bar->Update(window);

	switch (this->loading) {
	case status::NONE:
		break;
	case status::LOADING:
		this->timer = this->clock.getElapsedTime();
		//static bool test = false;
		//std::cout << this->timer.asSeconds() << std::endl;
		if (test == 0) {
			this->changeLoadingText(L"£adowanie.  ");
			this->test = 1;
		}
		else if (this->timer.asSeconds() > 3.f && test == 3) {
			this->clock.restart();
			this->timer = this->clock.getElapsedTime();
			this->test = 0;
		}
		else if (this->timer.asSeconds() > 2.f && test == 2) {
			this->changeLoadingText(L"£adowanie...");
			this->test = 3;
		}
		else if (this->timer.asSeconds() >= 1.f && test == 1) {
			this->changeLoadingText(L"£adowanie.. ");
			this->test = 2;
		}

			break;
	case status::LOADED:
		break;
	default:
		break;
	}
	this->timer = this->clock.getElapsedTime();
}

void Summary::Render(sf::RenderWindow* window) {
	window->draw(*this);
	window->draw(*this->loadingText);
	this->left_bar->Render(window);
}

Summary::~Summary() {

	delete this->loadingText;
	delete this->left_bar;
}