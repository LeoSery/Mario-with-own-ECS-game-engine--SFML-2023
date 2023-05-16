#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <map>
#include "GameObject.hpp"
#include "TexturesManager.hpp"
#include "Enemy.hpp"

#include "TexturesManager.hpp"
#include "GameObject.hpp"

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
			throw std::runtime_error("ckc");
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
					GameObject* gobj = new GameObject(EM, TexturesManager::getTexture(0), { x,y });
					break;
				}
				case '*':
				{
					Enemy* enemy = new Enemy(EM, { static_cast<float>(x * blockSize), static_cast<float>(y * blockSize) });
					break;
				}
				case '2':
					break;
				default:
				{
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