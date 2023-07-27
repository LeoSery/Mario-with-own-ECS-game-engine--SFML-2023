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

#include <SFML/Graphics.hpp>
#include <iostream>

class Level
{
public:
	EntityManager* EM;

	bool ingame = false;
	bool gameOver = false;
	bool gameWin = false;

	int score = 0;

	std::map<char, sf::Texture> gameMap;
	ReadMap mapReader;

	sf::Time deltaTime = sf::Time(sf::microseconds(1.1f));
	sf::Time timeSinceStart = sf::Time(sf::microseconds(0));

	Vector2<int> mapDimensions;
	Background* bg;
	PlayerEntity* player;

	Level(sf::RenderWindow& window, EntityManager* EM)
	{
		this->EM = EM;
	}

	void InitLevel(sf::RenderWindow& window)
	{
		EM->PurgeAll();
		bg = new Background(EM, TexturesManager::getTexture(8), { 0,-8 });
		mapDimensions = mapReader.ReadFile("Game/Assets/Resources/MapPatern.txt", gameMap, EM);
		player = new PlayerEntity(EM, window, mapDimensions, { 1000,500 });
	}

	void UpdateLevel(sf::RenderWindow& window, sf::Event& event, InputManager& inputManager)
	{
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
			Component* currentComponent = EM->GetComponentByTag(ent, "SPRITE_RENDERER");
			if (currentComponent != NULL)
			{
				SpriteRendererComponent* sprite = static_cast<SpriteRendererComponent*>(currentComponent);
				window.draw(sprite->loadSprite());

				Component* collidercomp = EM->GetComponentByTag(ent, "COLLIDER");
				if (collidercomp != NULL && ent->Tag != "PLAYER")
				{
					player->colliderComponent->Collision(sprite->getSprite());
					if (ent->Tag == "FLAG" && player->colliderComponent->collided)
					{
						gameWin = true;
						sf::View mainMenuView;
						window.setView(mainMenuView);
						ingame = false;
						std::cout << "win";
						EM->PurgeAll();
						return;
					}
				}

				if (currentComponent != NULL && ent->Tag != "ENEMY")
				{
					for (Entity* enemy : allEnemies)
					{
						Enemy* enemyEntity = static_cast<Enemy*>(enemy);
						enemyEntity->colliderComponent->Collision(sprite->getSprite());

						if (ent->Tag == "PLAYER")
						{
							if (enemyEntity->colliderComponent->collided)
							{
								if (std::find(enemyEntity->colliderComponent->activeDirections.begin(), enemyEntity->colliderComponent->activeDirections.end(), "TOP") != enemyEntity->colliderComponent->activeDirections.end())
								{
									enemyEntity->healthComponent->TakeDamage(100);
									player->playerControllerComponent->addJump(1.0f);
									auto itr = std::find(player->colliderComponent->activeDirections.begin(), player->colliderComponent->activeDirections.end(), "FLOOR");

									if (itr != player->colliderComponent->activeDirections.end()) player->colliderComponent->activeDirections.erase(itr);
									score++;
								}
								else
									player->healthComponent->TakeDamage(100);
							}
						}
					}
				}
			}

			currentComponent = EM->GetComponentByTag(ent, "HEALTH");
			if (currentComponent != NULL)
			{
				HealthComponent* entityHealth = static_cast<HealthComponent*>(currentComponent);

				if (entityHealth->GetisDead() == true)
				{
					if (ent->Tag != "PLAYER")
						EM->destroyQueue.push_back(ent);
					else
					{
						GameOver();
						return;
					}
				}
			}
		}

		player->Move(inputManager.GetDirection(), deltaTime, window, bg);

		if (player->spriteRendererComponent->getPosition().y > mapDimensions.y)
		{
			GameOver();
			return;
		}

		window.display();
		deltaTime = clock.getElapsedTime();
		timeSinceStart += deltaTime;
	}

	void GameOver()
	{
		ingame = false;
		gameOver = true;
		std::cout << "GameOver" << std::endl;
		EM->PurgeAll();
	}
};
