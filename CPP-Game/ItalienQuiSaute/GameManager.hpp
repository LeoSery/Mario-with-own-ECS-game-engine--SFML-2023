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
	sf::Texture tex2 = TexturesManager::getTexture(1);
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
		sf::Time timer = sf::Time(sf::microseconds(0));
		sf::Time framerate = sf::Time(sf::microseconds(1000));

		std::map<char, sf::Texture> gameMap;
		ReadMap mapReader;

		Vector2<int> mapDimensions = mapReader.ReadFile("Map.txt", gameMap, EM);
		std::cout << mapDimensions.x << " " << mapDimensions.y;

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

				if (timer.asMicroseconds() <= timeSinceStart.asMicroseconds())
				{
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
											if (enemyEntity->colliderComponent->collided)
												player->healthComponent->TakeDamage(100);
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
										//gameOver = true;
										std::cout << "GameOver" << std::endl;
									}

								}
							}
						}
					}
					player->Move(inputManager.GetDirection(), deltaTime, window);
					timer += framerate;
				}
				window.display();
				deltaTime = clock.getElapsedTime();
				timeSinceStart += deltaTime;
			}

		}

		//clean pointers
		for (Entity* ent : EM->livingEntityList)
		{
			EM->destroyQueue.push_back(ent);
		}
		EM->Purge();
		delete EM;
	}
};
