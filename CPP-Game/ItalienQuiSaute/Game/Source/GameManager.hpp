#pragma once

#include "../../Engine/Components/PlayerControllerComponent.hpp"
#include "../../Engine/Components/SpriteRendererComponent.hpp"
#include "../../Engine/Components/ColliderComponent.hpp"
#include "../../Engine/Components/HealthComponent.hpp"

#include "../../Engine/System/Managers/TexturesManager.hpp"
#include "../../Engine/System/Managers/EntityManager.hpp"
#include "../../Engine/System/Managers/InputManager.hpp"

#include "../../Engine/Entities/PlayerEntity.hpp"
#include "../../Engine/Entities/Enemy.hpp"

#include "../../Engine/System/Libraries/Maths/Vector2.h"
#include "../../Engine/API/RequestManager.hpp"

#include "FileReader.hpp"
#include "Level.hpp"
#include "Menu.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>

class GameManager
{
public:
	EntityManager* EM;
	bool menuIsOpen = false;
	Level* level;

	GameManager()
	{
		Init();
	}

	void Init()
	{
		sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");
		EM = new EntityManager();
		level = new Level(window, EM);
		Update(window);
	}

	//Main loop
	void Update(sf::RenderWindow& window)
	{
		sf::Event event{};
		InputManager inputManager(event);

		Menu menu;

		while (window.isOpen())
		{
			
			
			//Score Menu loop
			if (level->gameWin) {


				menu.scoreMenu(window, event, level->score);
			}

			//Game loop
			else if (level->ingame) {
				
				level->UpdateLevel(window, event, inputManager);
				//Remove entities in destroy queue just in case
				EM->Purge();
			}
			

			//Main menu / Game Over loop
			else
			{
				if (!menuIsOpen)
				{
					menu.mainMenu(window);
					menuIsOpen = true;
				}

				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					if (menu.onClick(window))
						StartGame(window);
				}
			}
			while (window.pollEvent(event) && !level->gameWin)
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}
		}
		//clean all when window is closed
		EM->PurgeAll();
		delete EM;
		delete level;
	}

	//Make a new level
	void StartGame(sf::RenderWindow& window)
	{
		menuIsOpen = false;
		level->InitLevel(window);
		level->ingame = true;
		std::cout << "Starting Game !!!!" << std::endl;
	}
};
