#include "list_state.h"
#include "menu_state.h"
#include <iostream>

void list_state::Initialize(sf::RenderWindow* window) {
	this->font = new sf::Font();

	if (!this->font->loadFromFile("Fonts/Roboto-Light.ttf")) {
		std::cerr << "Cannot load the font" << std::endl;
		return;
	}

	this->title = new sf::Text("", *this->font, 48U);
	this->title->setOrigin(this->title->getGlobalBounds().width / 2.f, this->title->getGlobalBounds().height / 2.f);
	this->title->setPosition(static_cast<float>(window->getSize().x / 2u), 40.f);

	this->topBar = new navBar(this->font, 0.f, 0.f, static_cast<float>(window->getSize().x));
	this->monthsBar = new navBar(this->font, 0.f, 40.f, static_cast<float>(window->getSize().x));

	this->loadingYears = loadingStates::NONE;
	this->loadingMonths = loadingStates::NONE;
	this->loadingDrivers = loadingStates::NONE;

	this->years.clear();

	this->summary = new Summary(window, font, 80.f);

	this->lClick = false;
	this->escKey = false;
}

void list_state::Update(sf::RenderWindow* window) {

	// NAV BAR TOP YEARS
	if (this->loadingYears == loadingStates::NONE) {
		this->loadingYears = loadingStates::LOADING;
		std::string query;
		query = u8"SELECT DISTINCT YEAR(data) FROM errands ORDER BY YEAR(data) ASC;";

		coreState.getDataBaseManager()->setQuery(DataBaseManager::Action::SELECT, query);
	}
	else if (this->loadingYears == loadingStates::LOADING && coreState.getDataBaseManager()->isResultsReady()) {
		std::cout << coreState.getDataBaseManager()->getResults().size() << std::endl;
		this->loadingYears = loadingStates::LOADED;
		if (!coreState.getDataBaseManager()->getResults().empty()) {
			std::vector<std::string> years;
			for (size_t i = 0u; i < coreState.getDataBaseManager()->getResults().size(); i++) {
				if (!coreState.getDataBaseManager()->getResults()[i].empty()) {
					years.push_back(coreState.getDataBaseManager()->getResults()[i][0]);
					std::cout << "Rok[" << i << "] = " << years[i] << std::endl;
				}
			}
			this->years = years;
			this->topBar->loadOptions(this->years);
		}
	}

	// NAV BAR TOP MONTHS
	if (this->loadingMonths == loadingStates::NONE && this->loadingYears == loadingStates::LOADED && this->topBar->getSelected() != nullptr) {
		this->loadingMonths = loadingStates::LOADING;

		std::string query = u8"SELECT DISTINCT MONTH(data) FROM errands where YEAR(data) = YEAR('" + this->topBar->getSelected()->getString() + "-01-01') ORDER BY MONTH(data) ASC;";
		coreState.getDataBaseManager()->setQuery(DataBaseManager::Action::SELECT, query);
	}
	else if (this->loadingMonths == loadingStates::LOADING && coreState.getDataBaseManager()->isResultsReady()) {
		std::cout << coreState.getDataBaseManager()->getResults().size() << std::endl;
		this->loadingMonths = loadingStates::LOADED;
		if (!coreState.getDataBaseManager()->getResults().empty()) {
			std::vector<std::string> months;
			for (size_t i = 0u; i < coreState.getDataBaseManager()->getResults().size(); i++) {
				if (!coreState.getDataBaseManager()->getResults()[i].empty()) {
					months.push_back(coreState.getDataBaseManager()->getResults()[i][0]);
					std::cout << "Miesiac[" << i << "] = " << months[i] << std::endl;
				}
			}
			this->months = months;
			this->monthsBar->loadOptions(this->months);
		}
	}

	// SUMMARY  DRIVERS LOADING
	if (this->loadingDrivers == loadingStates::NONE && this->loadingMonths == loadingStates::LOADED && this->loadingYears == loadingStates::LOADED && this->topBar->getSelected() != nullptr && this->monthsBar->getSelected() != nullptr) {
		this->loadingDrivers = loadingStates::LOADING;
		std::string query;
		if (true) // jesli holowanie
			query = u8"SELECT DISTINCT(kierowca) FROM errands WHERE MONTH(data) = MONTH('" + this->topBar->getSelected()->getString() + "-" + this->monthsBar->getSelected()->getString() + "-01') and YEAR(data) = YEAR('" + this->topBar->getSelected()->getString() + "-" + this->monthsBar->getSelected()->getString() + "-01') and transport_osob = '0';";
		else //tr osob
			query = u8"SELECT DISTINCT(kierowca) FROM errands WHERE MONTH(data) = MONTH('" + this->topBar->getSelected()->getString() + "-" + this->monthsBar->getSelected()->getString() + "-01') and YEAR(data) = YEAR('" + this->topBar->getSelected()->getString() + "-" + this->monthsBar->getSelected()->getString() + "-01') and transport_osob = '1';";

		coreState.getDataBaseManager()->setQuery(DataBaseManager::Action::SELECT, query);
	}
	else if (this->loadingDrivers == loadingStates::LOADING && coreState.getDataBaseManager()->isResultsReady()) {
		std::cout << coreState.getDataBaseManager()->getResults().size() << std::endl;
		this->loadingDrivers = loadingStates::LOADED;
		if (!coreState.getDataBaseManager()->getResults().empty()) {
			std::vector<std::string> drivers;
			for (size_t i = 0u; i < coreState.getDataBaseManager()->getResults().size(); i++) {
				if (!coreState.getDataBaseManager()->getResults()[i].empty()) {
					drivers.push_back(coreState.getDataBaseManager()->getResults()[i][0]);
					std::cout << "Kierowca[" << i << "] = " << drivers[i] << std::endl;
				}
			}
			//this->months = months;
			//this->monthsBar->loadOptions(this->months);
		}
	}



	if (this->loadingYears == loadingStates::LOADED) {
		this->topBar->Update(window);
		if (this->topBar->isNewSelected()) {
			this->monthsBar->clearOptions();
			this->loadingMonths = loadingStates::NONE;
			this->topBar->setNewSelected();

			//clear drivers TODO

			this->loadingDrivers = loadingStates::NONE;
		}
	}
	if (this->loadingMonths == loadingStates::LOADED) {
		this->monthsBar->Update(window);
		if (this->monthsBar->isNewSelected()) {
			// clear drivers in summary TODO
			this->loadingDrivers = loadingStates::NONE;
			this->monthsBar->setNewSelected();
		}
	}

	this->summary->Update(window);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape) && !this->escKey) {
		coreState.setState(new menu_state());
	}
	this->escKey = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape);
}

void list_state::Render(sf::RenderWindow* window) {
	this->topBar->Render(window);
	this->monthsBar->Render(window);
	window->draw(*this->title);
	this->summary->Render(window);
}

void list_state::Destroy(sf::RenderWindow* window) {
	delete this->title;
	delete this->summary;
	delete this->topBar;
	delete this->monthsBar;
	delete this->font;
}