#pragma once

#include "../Engine/Components/PlayerControllerComponent.hpp"
#include "../Engine/Components/SpriteRendererComponent.hpp"
#include "../Engine/Components/ColliderComponent.hpp"
#include "../Engine/Components/HealthComponent.hpp"

#include "../Engine/System/Managers/TexturesManager.hpp"
#include "../Engine/System/Managers/EntityManager.hpp"
#include "../Engine/System/Managers/InputManager.hpp"

#include "../Engine/Entities/PlayerEntity.hpp"
#include "../Engine/Entities/Enemy.hpp"

#include "../Engine/System/Libraries/Maths/Vector2.h"
#include "../Engine/API/RequestManager.hpp"

#include "FileReader.hpp"
#include "Level.hpp"
#include "Menu.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>

class GameManager
{
public:
	EntityManager* EM = new EntityManager();
	
	bool menuIsOpen = false;

	Level* level;

	GameManager()
	{
		
		Init();
	}

	void Init()
	{
		sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");
		level = new Level(window, EM);
		Update(window);
	}

	void Update(sf::RenderWindow& window)
	{

		sf::Event event{};
		InputManager inputManager(event);

		Menu menu;


		EM->Purge();
		while (window.isOpen())
		{
			sf::Clock clock;

			EM->Purge();

			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			if (level->ingame) {
				level->UpdateLevel(window, event, inputManager);
			}
			else if (level->gameWin) {
				menu.scoreMenu(window, event, level->score);
				
			}

			else
			{

				if (!menuIsOpen)
				{
					menu.mainMenu(window);
					menuIsOpen = true;
				}


				
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					if (menu.onClick(window)) {
						StartGame(window);
					}
				}
			}


		}

		//clean all when window is closed

		EM->PurgeAll();
		delete EM;
		delete level;
	}

	void StartGame(sf::RenderWindow& window)
	{
		menuIsOpen = false;
		level->InitLevel(window);
		level->ingame = true;
		std::cout << "Starting Game !!!!" << std::endl;
	}
};
