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
	bool gameOver = false;

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

		std::map<char, sf::Texture> gameMap;
		ReadMap mapReader;

		Vector2<int> mapDimensions = mapReader.ReadFile("Map.txt", gameMap, EM);

		PlayerEntity* player = new PlayerEntity(EM, window, mapDimensions, { 1000,500 });

		EM->Purge();
		while (window.isOpen())
		{
			if (!gameOver) {
				sf::Clock clock;

				while (window.pollEvent(event))
				{
					if (event.type == sf::Event::Closed)
						window.close();
				}

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
					for (Component* currentComponent : EM->componentMapping[ent])
					{
						if (currentComponent->Tag == "SPRITE_RENDERER")
						{
							SpriteRendererComponent* sprite = static_cast<SpriteRendererComponent*>(currentComponent);
							window.draw(sprite->loadSprite());

							if (ent->Tag != "PLAYER")
							{
								player->colliderComponent->Collision(sprite->getSprite());
							}

							if (ent->Tag != "ENEMY") {
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
						else if (currentComponent->Tag == "HEALTH") {
							HealthComponent* entityHealth = static_cast<HealthComponent*>(currentComponent);
							if (entityHealth->GetisDead() == true)
							{
								if (ent->Tag != "PLAYER") {
									EM->destroyQueue.push_back(ent);
								}
								else {
									gameOver = true;
									std::cout << "GameOver" << std::endl;
								}

							}
						}
					}
				}
				player->Move(inputManager.GetDirection(), deltaTime, window);

				window.display();
				deltaTime = clock.getElapsedTime();
				timeSinceStart += deltaTime;
			}
			else
			{
				EM->PurgeAll();
				ShowMainMenu(window);
			}
		}

		EM->PurgeAll();
		delete EM;
	}


	void ShowMainMenu(sf::RenderWindow& window)
	{
		sf::View mainMenuView;
		mainMenuView.setCenter(sf::Vector2f(0, 0));
		mainMenuView.setSize(sf::Vector2f(400.f, 400.f));
		mainMenuView.zoom(5.0f);
		window.clear();
		window.setView(mainMenuView);

		sf::Font TextFont;
		if (!TextFont.loadFromFile("Assets/Fonts/FORCED_SQUARE.ttf"))
			std::cout << "error";

		sf::RectangleShape playButton(sf::Vector2f(500, 150));
		playButton.setFillColor(sf::Color::White);
		playButton.setPosition(sf::Vector2f(-playButton.getSize().x / 2, -200));
		sf::Vector2f playButtonPosition = { playButton.getPosition().x + playButton.getSize().x / 2 , playButton.getPosition().y + playButton.getSize().y / 2 };
		window.draw(playButton);
		sf::Text playText;
		playText.setPosition(playButtonPosition);
		playText.setCharacterSize(75);
		playText.setFillColor(sf::Color::Black);
		playText.setString("PLAY");
		playText.setFont(TextFont);
		window.draw(playText);

		sf::RectangleShape quitButton(sf::Vector2f(500, 150));
		quitButton.setFillColor(sf::Color::White);
		quitButton.setPosition(sf::Vector2f(-quitButton.getSize().x / 2, 200));
		sf::Vector2f quitButtonPosition = { quitButton.getPosition().x + quitButton.getSize().x / 2 , quitButton.getPosition().y + quitButton.getSize().y / 2 };
		window.draw(quitButton);
		sf::Text quitText;
		quitText.setPosition(quitButtonPosition);
		quitText.setCharacterSize(75);
		quitText.setFillColor(sf::Color::Black);
		quitText.setString("QUIT");
		quitText.setFont(TextFont);
		window.draw(quitText);

		window.display();
	}
};
