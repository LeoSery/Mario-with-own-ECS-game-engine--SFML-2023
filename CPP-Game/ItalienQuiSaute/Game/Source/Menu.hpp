
#pragma once

#include "../../Engine/API/RequestManager.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

class Menu {
public:
	//Input text for scores
	sf::String playerInput;
	sf::Text playerText;
	sf::Font TextFont;
	int baseTextSize;

	RequestManager requestManager;


	int count = 0;

	//Values needed for the API request
	std::string email;
	std::string pseudo;
	std::string password;
	std::string token;

	//Main menu buttons
	sf::RectangleShape playButton;
	sf::RectangleShape quitButton;

	Menu()
	{
		//Setting base values
		if (!TextFont.loadFromFile("Game/Assets/Fonts/FORCED_SQUARE.ttf"))
			std::cout << "error";

		playerText.setPosition(6, 9);
		playerText.setCharacterSize(24);
		playerText.setFillColor(sf::Color::White);
		playerText.setString("Email: ");
		playerText.setFont(TextFont);
		baseTextSize = playerText.getString().getSize();
		playButton.setSize(sf::Vector2f(200, 60));
		quitButton.setSize(sf::Vector2f(200, 60));
	}

	void scoreMenu(sf::RenderWindow& window, sf::Event& event, int score)
	{
		
		window.clear();
		

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::TextEntered)
			{
				//Delete Key
				if (event.text.unicode == 8)
				{
					playerInput = playerText.getString();
					if (playerInput.getSize() <= baseTextSize) { return; }

					playerInput.erase(playerInput.getSize() - 1, 1);
					playerText.setString(playerInput);

				}
				//Any other keys 
				else if (event.text.unicode < 128 && event.text.unicode != 13)
				{

					playerInput = playerText.getString();
					playerInput += event.text.unicode;
					playerText.setString(playerInput);

				}

				//Enter key (submit)
				else if (event.text.unicode == 13)
				{
					//switch on all steps of login
					switch (count)
					{
					case 2:

						password = (std::string)playerText.getString().toAnsiString();
						password.erase(0, baseTextSize);
						pseudo.erase(std::remove(pseudo.begin(), pseudo.end(), '\r'), pseudo.end());
						password.erase(std::remove(password.begin(), password.end(), '\r'), password.end());
						requestManager.signIn(pseudo, email, password);
						token = requestManager.login(pseudo, email, password);
						requestManager.newscore(score, "MARIO", token);
						playerText.setString(requestManager.Scorelist());
						std::cout << token << "\n";
						count++;

						break;
					case 1:

						pseudo = (std::string)playerText.getString().toAnsiString();
						pseudo.erase(0, baseTextSize);
						playerText.setString("Password: ");
						baseTextSize = playerText.getString().getSize();
						count++;

						break;
					case 0:

						email = (std::string)playerText.getString().toAnsiString();
						email.erase(0, baseTextSize);
						playerText.setString("Name: ");
						baseTextSize = playerText.getString().getSize();
						count++;

						break;
					default:
						break;
					}
				}
				
			}
			
		}
		window.draw(playerText);
		window.display();
	}

	void mainMenu(sf::RenderWindow& window)
	{
		std::cout << "IN DISPLAY MAIN MENU" << std::endl;
		sf::View mainMenuView;
		window.clear();
		window.setView(mainMenuView);

		sf::Font TextFont;
		if (!TextFont.loadFromFile("Game/Assets/Fonts/FORCED_SQUARE.ttf"))
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

	bool onClick(sf::RenderWindow& window)
	{
		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
		sf::Vector2f mousePositionVector = { static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y) };

		if (playButton.getGlobalBounds().contains(mousePositionVector))
		{
			std::cout << "MOUSE IN PLAY BUTTON" << std::endl;
			return true;
		}

		else if (quitButton.getGlobalBounds().contains(mousePositionVector))
		{
			std::cout << "MOUSE IN QUIT BUTTON" << std::endl;
			window.close();
		}
		return false;
	}
};