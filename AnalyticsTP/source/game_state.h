#pragma once

#include <SFML/Graphics.hpp>
#include "DataBaseManager.h"

class tiny_state
{
public:
	virtual void Initialize(sf::RenderWindow* window) {}

	virtual void Update(sf::RenderWindow* window) {}

	virtual void Render(sf::RenderWindow* window) {}

	virtual void Destroy(sf::RenderWindow* window) {}

	virtual void TextEntered(sf::Uint32 unicode) {}
};

class game_state
{
private:
	sf::RenderWindow* window;
	tiny_state* state;
	DataBaseManager* db_manager;
public:
	game_state() {
		this->state = nullptr;
		this->window = nullptr;
		this->db_manager = new DataBaseManager();
	}
	void TextEntered(sf::Uint32 unicode) {
		if (this->state != nullptr) {
			this->state->TextEntered(unicode);
		}
	}
	void setWindow(sf::RenderWindow* window) {
		if (this->window == nullptr)
			this->window = window;
	}
	void setState(tiny_state* state) {
		if (this->state != nullptr) {
			this->state->Destroy(this->window);
			this->db_manager->clear();
		}
		this->state = state;
		if (this->state != nullptr)
			this->state->Initialize(this->window);
	}

	DataBaseManager* getDataBaseManager() {
		return this->db_manager;
	}

	void Update() {
		if (this->state != nullptr)
			this->state->Update(this->window);
	}
	void Render() {
		if (this->state != nullptr)
			this->state->Render(this->window);
	}

	~game_state() {
		if (this->state != nullptr)
			this->state->Destroy(this->window);
		delete this->db_manager;
	}

};

extern game_state coreState;