#pragma once

#include "../../Engine/System/Managers/TexturesManager.hpp"
#include "../../Engine/Entities/GameObject.hpp"
#include "../../Engine/Entities/Entity.hpp"
#include "../../Engine/Entities/Flag.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <map>

class ReadMap
{
public:
	Vector2<int> ReadFile(std::string path, std::map<char, sf::Texture>& targetMap, EntityManager* EM)
	{
		Vector2<int> dimensions = { 0,0 };
		std::string filename(path);
		std::ifstream inputFile(filename);
		std::vector<char> bytes;
		std::string line;
		char byte = 0;
		int blockSize = 64;

		if (!inputFile.is_open())
		{
			std::cerr << "Could not open the file - '" << filename << "'" << std::endl;
			throw std::runtime_error("Error occurred while trying to open file.");
		}

		int y = 1;
		while (std::getline(inputFile, line))
		{
			int x = 1;

			for (auto lineChar : line)
			{
				switch (lineChar)
				{
				case ' ':
				{
					break;
				}
				case '1':
				{
					GameObject* gobj = new GameObject(EM, TexturesManager::getTexture(1), { x,y });
					break;
				}
				case '2':
				{
					GameObject* gobj = new GameObject(EM, TexturesManager::getTexture(2), { x,y });
					break;
				}
				case '4':
				{
					Flag* gobj = new Flag(EM, { x,y }, 4);
					break;
				}
				case '5':
				{
					Flag* gobj = new Flag(EM, { x,y }, 5);
					break;
				}
				case '6':
				{
					Enemy* enemy = new Enemy(EM, { static_cast<float>(x * blockSize), static_cast<float>(y * blockSize) });
					break;
				}
				case '7':
				{
					GameObject* gobj = new GameObject(EM, TexturesManager::getTexture(7), { x,y });
					break;
				}

				}
				x++;
				dimensions.x = x * blockSize;
			}
			y++;
		}
		dimensions.y = y * blockSize;
		inputFile.close();
		return dimensions;
	}
};