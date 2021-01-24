#include <iostream>
#include <thread>
#include <chrono>         // std::chrono::seconds
#include "game_state.h"
#include "menu_state.h"

game_state coreState;

void db_thread(sf::RenderWindow* window) {
	DataBaseManager* db_manager = coreState.getDataBaseManager();
	while (window->isOpen()) {
		if(db_manager != nullptr)
			db_manager->Listening();
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}

int main() {

	sf::RenderWindow window(sf::VideoMode(1200u, 800u), "Transpol analytics", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60u);
	coreState.setWindow(&window);
	coreState.setState(new menu_state());

	std::thread DB_thread(&db_thread, &window);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				//coreState.setState(nullptr);
				window.close();
				if (DB_thread.joinable())
					DB_thread.join();
				coreState.setState(nullptr);
				return 0;
			}
			else if (event.type == sf::Event::TextEntered)
			{
				//if (event.text.unicode < sf::Uint32(128)) {
					coreState.TextEntered(event.text.unicode);
				//} else if (event.text.unicode == sf::Uint32(66))
					//coreState.TextEntered(sf::Uint32(321));
				//if (event.text.unicode < 128 || event.text.unicode == 163) {
					// std::cout << "ASCII character typed: " << static_cast<char>(event.text.unicode) << std::endl;
					// coreState.TextEntered(static_cast<char>(event.text.unicode));
					// what if clear virtual TextEntered
				//if(event.text.unicode == 66)
				//	coreState.TextEntered(static_cast < char>(321));
				//else
				//	coreState.TextEntered(event.text.unicode);
				//}
			}
		}

		window.clear(sf::Color::Blue);
		coreState.Update();
		coreState.Render();
		window.display();
	}
	if(DB_thread.joinable())
		DB_thread.join();
	return 0;
}