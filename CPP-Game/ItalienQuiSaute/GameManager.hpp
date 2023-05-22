#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "PlayerControllerComponent.hpp"
#include "SpriteRendererComponent.hpp"
#include "ColliderComponent.hpp"
#include "HealthComponent.hpp"
#include "TexturesManager.hpp"
#include "EntityManager.hpp"
#include "InputManager.hpp"
#include "PlayerEntity.hpp"
#include "Maths/Vector2.h"
#include "FileReader.hpp"
#include "Enemy.hpp"

class GameManager
{
public:
	EntityManager* EM = new EntityManager();
	sf::Texture tex = TexturesManager::getTexture(0);
	bool ingame = false;
	bool menuIsOpen = false;

	GameManager()
	{
		Init();
	}

	void Init()
	{
		Update();
	}

	void Update()
	{
		sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");

		sf::Event event{};
		InputManager inputManager(event);

		sf::Time deltaTime = sf::Time(sf::microseconds(1.1f));
		sf::Time timeSinceStart = sf::Time(sf::microseconds(0));

		sf::RectangleShape playButton(sf::Vector2f(200, 60));
		sf::RectangleShape quitButton(sf::Vector2f(200, 60));

		std::map<char, sf::Texture> gameMap;
		ReadMap mapReader;

		Background* bg = new Background(EM, TexturesManager::getTexture(8), { 0,0 });
		Vector2<int> mapDimensions = mapReader.ReadFile("Map.txt", gameMap, EM);
		std::cout << mapDimensions.y;
		PlayerEntity* player = new PlayerEntity(EM, window, mapDimensions, { 1000,500 });

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

			if (ingame) {
				sf::Clock clock;

				inputManager.UpdateEvent(event);
				window.clear();
				EM->Purge();

				std::vector<Entity*> allEnemies = EM->GetAllEntityByTag("ENEMY");


				for (Entity* entity : allEnemies)
				{
					Enemy* enemy = static_cast<Enemy*>(entity);
					enemy->Move(sf::Time(sf::microseconds(2000)));
				}

				


				for (Entity* ent : EM->livingEntityList)
				{
					if (ent->Tag == "BACKGROUND") {
						bg = static_cast<Background*>(ent);
					}
					Component* currentComponent = EM->GetComponentByTag(ent, "SPRITE_RENDERER");
					if (currentComponent != NULL) {
						SpriteRendererComponent* sprite = static_cast<SpriteRendererComponent*>(currentComponent);
						window.draw(sprite->loadSprite());

						Component* collidercomp = EM->GetComponentByTag(ent, "COLLIDER");
						if (collidercomp != NULL && ent->Tag != "PLAYER") {
							player->colliderComponent->Collision(sprite->getSprite());
						}

						if (currentComponent != NULL && ent->Tag != "ENEMY") {
							for (Entity* enemy : allEnemies) {
								Enemy* enemyEntity = static_cast<Enemy*>(enemy);
								enemyEntity->colliderComponent->Collision(sprite->getSprite());
								if (ent->Tag == "PLAYER")
								{
									if (enemyEntity->colliderComponent->collided) {
										if (std::find(enemyEntity->colliderComponent->activeDirections.begin(), enemyEntity->colliderComponent->activeDirections.end(), "TOP") != enemyEntity->colliderComponent->activeDirections.end()) {
											enemyEntity->healthComponent->TakeDamage(100);
										}
										else {
											player->healthComponent->TakeDamage(100);
										}
									}


								}
							}
						}

						

					}

					ccurrentComponent = EM->GetComponentByTag(ent, "HEALTH");
						if (currentComponent != NULL) {
							HealthComponent* entityHealth = static_cast<HealthComponent*>(currentComponent);
							if (entityHealth->GetisDead() == true)
							{
								if (ent->Tag != "PLAYER") {
									EM->destroyQueue.push_back(ent);
								}
								else {
									ingame = false;
									std::cout << "GameOver" << std::endl;
								}

							}
						}

				}

				player->Move(inputManager.GetDirection(), deltaTime, window, bg);

				window.display();
				deltaTime = clock.getElapsedTime();
				timeSinceStart += deltaTime;
			}
			else
			{
				
				if (!menuIsOpen)
				{
					ShowMainMenu(window, playButton, quitButton);
				}

				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
					sf::Vector2f mousePositionVector = { static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y) };

					if (playButton.getGlobalBounds().contains(mousePositionVector))
					{
						std::cout << "MOUSE IN PLAY BUTTON" << std::endl;
						StartGame();
					}
					else if (quitButton.getGlobalBounds().contains(mousePositionVector))
					{
						std::cout << "MOUSE IN QUIT BUTTON" << std::endl;
						window.close();
					}
				}
			}


		}
		EM->PurgeAll();
		delete EM;
	}

	void ShowMainMenu(sf::RenderWindow& window, sf::RectangleShape& playButton, sf::RectangleShape& quitButton)
	{
		std::cout << "IN DISPLAY MAIN MENU" << std::endl;
		menuIsOpen = true;

		sf::View mainMenuView;
		window.clear();
		window.setView(mainMenuView);

		sf::Font TextFont;
		if (!TextFont.loadFromFile("Assets/Fonts/FORCED_SQUARE.ttf"))
			std::cout << "error";


		playButton.setFillColor(sf::Color::White);
		playButton.setPosition(sf::Vector2f((window.getSize().x / 2) - (playButton.getSize().x / 2), (window.getSize().y / 2) - (playButton.getSize().y / 2) - 100));
		sf::Vector2f playTextPosition = { playButton.getPosition().x + playButton.getSize().x / 3, playButton.getPosition().y + playButton.getSize().y / 5 };
		window.draw(playButton);
		sf::Text playText;
		playText.setPosition(playTextPosition);
		playText.setCharacterSize(30);
		playText.setFillColor(sf::Color::Black);
		playText.setString("PLAY");
		playText.setFont(TextFont);
		window.draw(playText);


		quitButton.setFillColor(sf::Color::White);
		quitButton.setPosition(sf::Vector2f((window.getSize().x / 2) - (playButton.getSize().x / 2), (window.getSize().y / 2) - (playButton.getSize().y / 2) + 100));
		sf::Vector2f quitButtonPosition = { quitButton.getPosition().x + quitButton.getSize().x / 3 , quitButton.getPosition().y + quitButton.getSize().y / 5 };
		window.draw(quitButton);
		sf::Text quitText;
		quitText.setPosition(quitButtonPosition);
		quitText.setCharacterSize(30);
		quitText.setFillColor(sf::Color::Black);
		quitText.setString("QUIT");
		quitText.setFont(TextFont);
		window.draw(quitText);

		window.display();
	}

	void StartGame()
	{
		menuIsOpen = false;
		ingame = true;
		std::cout << "Starting Game !!!!" << std::endl;
	}

};
