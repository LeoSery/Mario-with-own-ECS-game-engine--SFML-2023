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
#include "API/RequestManager.hpp"

class GameManager
{
public:
	EntityManager* EM = new EntityManager();
	sf::Texture tex = TexturesManager::getTexture(0);
	bool ingame = false;
	bool gameOver = false;
	bool scoreSubmitted = false;
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

		std::map<char, sf::Texture> gameMap;
		ReadMap mapReader;

		sf::RectangleShape playButton(sf::Vector2f(200, 60));
		sf::RectangleShape quitButton(sf::Vector2f(200, 60));

		Background* bg = new Background(EM, TexturesManager::getTexture(8), { 0,-8});
		Vector2<int> mapDimensions = mapReader.ReadFile("Map.txt", gameMap, EM);
		std::cout << mapDimensions.y;
		PlayerEntity* player = new PlayerEntity(EM, window, mapDimensions, { 1000,500 });


		//Creation du texte pour l'input des scores
		sf::String playerInput;
		sf::Text playerText;
		sf::Font TextFont;
		if (!TextFont.loadFromFile("Assets/Fonts/FORCED_SQUARE.ttf"))
		{
			std::cout << "error";
		}
		playerText.setPosition(6, 9);
		playerText.setCharacterSize(24);
		playerText.setFillColor(sf::Color::White);
		playerText.setString("Email: ");
		int baseTextSize = playerText.getString().getSize();
		playerText.setFont(TextFont);


		RequestManager* requestManager = new RequestManager();


		sf::Clock clock2;
		int count = 0;

		std::string email;
		std::string pseudo;
		std::string password;
		std::string token;


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
											player->playerControllerComponent->addJump(3.0f);
											auto itr = std::find(player->colliderComponent->activeDirections.begin(), player->colliderComponent->activeDirections.end(), "FLOOR");
											if (itr != player->colliderComponent->activeDirections.end()) player->colliderComponent->activeDirections.erase(itr);
										}
										else {
											player->healthComponent->TakeDamage(100);
										}
									}


								}
							}
						}
						
						
					}

					currentComponent = EM->GetComponentByTag(ent, "HEALTH");
					if (currentComponent != NULL) {
						HealthComponent* entityHealth = static_cast<HealthComponent*>(currentComponent);
						if (entityHealth->GetisDead() == true)
						{
							if (ent->Tag != "PLAYER") {
								EM->destroyQueue.push_back(ent);
							}
							else {
								ingame = false;
								gameOver = true;
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
			else if (gameOver) {
				
				bool cd = false;
				sf::Time cooldown = sf::Time(sf::seconds(0.1f));
				sf::View mainMenuView;
				window.clear();
				window.setView(mainMenuView);
				
				
				if (event.type == sf::Event::TextEntered)
				{
					
					
					if (scoreSubmitted)
					{
						break;
					}

					
					
					if (clock2.getElapsedTime() < cooldown) {
						cd = true;
					}
					else {
						cd = false;
					}

					if (event.text.unicode == 8)
					{
						if (!cd) {
							playerInput = playerText.getString();
							if (playerInput.getSize() <= baseTextSize) { break; }
							playerInput.erase(playerInput.getSize() - 1, 1);
							playerText.setString(playerInput);
							clock2.restart();
						}
						
					}

					if (event.text.unicode == 13)
					{
						
						if (!cd) {
							
							switch (count)
							{
							case 0:
								email = (std::string)playerText.getString().toAnsiString();
								email.erase(0, baseTextSize);
								
								count++;
								break;
							case 1:
								playerText.setString("Name: ");
								baseTextSize = playerText.getString().getSize() - 1;
								pseudo = (std::string)playerText.getString().toAnsiString();
								pseudo.erase(0, baseTextSize);
								
								count++;
								break;
							case 2:
								playerText.setString("Password: ");
								baseTextSize = playerText.getString().getSize() - 1;
								password = (std::string)playerText.getString().toAnsiString();
								password.erase(0, baseTextSize);
								
								
								std::cout << pseudo << email << password << "\n";
								requestManager->signIn(pseudo, email, password);
								token = requestManager->login(pseudo, email, password);
								requestManager->newscore(1, "MARIO", token);

								playerText.setString(requestManager->Scorelist());
								std::cout << token << "\n";
								count++;
								break;

							default:
								break;
							}
						
							clock2.restart();
						}
						
					
					}

					if (event.text.unicode < 128)
					{
						if (!cd) {
							playerInput = playerText.getString();
							playerInput += event.text.unicode;
							playerText.setString(playerInput);
							clock2.restart();
						}
						
					}

					
				}
				window.draw(playerText);
				window.display();
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
