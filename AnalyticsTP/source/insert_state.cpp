#include "insert_state.h"
#include "menu_state.h"
#include <iostream>
#include <string>

void insert_state::Initialize(sf::RenderWindow* window) {
	this->font = new sf::Font();

	if (!this->font->loadFromFile("Fonts/Roboto-Light.ttf")) {
		std::cerr << "Cannot load the font" << std::endl;
		return;
	}

	this->activeField = nullptr;
	this->form.clear();

	this->form.push_back(new textField(this->font, 100.f, 100.f, 300.f, 40.f, "Nazwa", sf::Color::White, sf::Color::Green));
	
	this->form.push_back(new textField(this->font, 100.f, 160.f, 300.f, 40.f, "Data", sf::Color::White, sf::Color::Green));
	this->form.push_back(new textField(this->font, 100.f, 220.f, 300.f, 40.f, "Dojazd", sf::Color::White, sf::Color::Green));
	this->form.push_back(new textField(this->font, 100.f, 280.f, 300.f, 40.f, "Holowanie", sf::Color::White, sf::Color::Green));
	this->form.push_back(new textField(this->font, 100.f, 340.f, 300.f, 40.f, "Powrot", sf::Color::White, sf::Color::Green));
	this->form.push_back(new textField(this->font, 100.f, 400.f, 300.f, 40.f, "Cena", sf::Color::White, sf::Color::Green));
	this->form.push_back(new textField(this->font, 100.f, 460.f, 300.f, 40.f, "Kierowca", sf::Color::White, sf::Color::Green));

	if (!this->form.empty())
		this->it = this->form.begin();

	this->taxi = new checkBox(this->font, 400.f, 100.f, 30.f, sf::Color::White, "Transport osob");
	this->transport = new textField(this->font, 500.f, 260.f, 300.f, 40.f, "Transport osob", sf::Color::White, sf::Color::Green);

	this->tabKey = false;
	this->enterKey = false;
	this->escKey = false;
	this->inserted = false;
	this->lClick = false;

}

void insert_state::Update(sf::RenderWindow* window) {

	if (!this->lClick && this->taxi->onClick(window)) {
		//this->taxi->onClick(window);

		if (this->taxi->getValue()) {
			this->form.push_back(this->transport);
		}
		else {
			this->form.pop_back();
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Tab) && !this->tabKey) {
		if (this->activeField == nullptr) {
			this->activeField = *this->it;
			this->activeField->setActive();
		}
		else if (this->form.begin() != this->form.end()) {
			this->activeField->setActive();
			++this->it;
			if (this->it == this->form.end())
				this->it = this->form.begin();
			this->activeField = *this->it;
			this->activeField->setActive();
		}
		else {
			this->activeField->setActive();
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter) && !this->enterKey) {
		std::string query = u8"";
		if (!this->taxi->getValue())
			query = u8"INSERT INTO `errands` (`id`, `nazwa`, `data`, `dojazd`, `holowanie`, `powrot`, `kierowca`, `cena`) VALUES (NULL, '" + this->form[0]->getString() + u8"', '" +
			this->form[1]->getString() + u8"', '" + this->form[2]->getString() + u8"', '" + this->form[3]->getString() + u8"', '" + this->form[4]->getString() + u8"', '" + this->form[6]->getString()
			+ u8"', '" + this->form[5]->getString() + u8"');";
		else {
			query = u8"INSERT INTO `errands` (`id`, `nazwa`, `data`, `dojazd`, `holowanie`, `powrot`, `kierowca`, `cena`, `transport_osob`, `cena_transport`) VALUES (NULL, '" + this->form[0]->getString() + u8"', '" +
				this->form[1]->getString() + u8"', '" + this->form[2]->getString() + u8"', '" + this->form[3]->getString() + u8"', '" + this->form[4]->getString() + u8"', '" + this->form[6]->getString()
				+ u8"', '" + this->form[5]->getString() + u8"', '1', '" + this->form[7]->getString() + u8"');";
		}
		coreState.getDataBaseManager()->setQuery(DataBaseManager::Action::INSERT, query);
		//if (this->InsertErrand())
			//this->inserted = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape) && !this->escKey) {
		coreState.setState(new menu_state());
	}

	for (size_t i = 0u; i < this->form.size(); i++)
		this->form[i]->Update(window);


	this->tabKey = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Tab);
	this->enterKey = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter);
	this->escKey = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape);
	this->lClick = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
}

void insert_state::Render(sf::RenderWindow* window) {
	for (size_t i = 0u; i < this->form.size(); i++)
		this->form[i]->Render(window);
	this->taxi->Render(window);
	if (this->taxi->getValue())
		this->transport->Render(window);
}


void insert_state::TextEntered(sf::Uint32 unicode) {
	if (this->activeField != nullptr)
		this->activeField->TextEntered(unicode);
}

void insert_state::Destroy(sf::RenderWindow* window) {
	this->activeField = nullptr;
	for (size_t i = 0u; i < this->form.size(); i++)
		if (this->transport != this->form[i])
			delete this->form[i];
	this->form.clear();
	delete this->taxi;
	delete this->transport;
}

bool insert_state::InsertErrand() {

	return true;
}