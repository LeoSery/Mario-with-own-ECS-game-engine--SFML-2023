#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <map>

using MapData = std::vector<std::vector<sf::Sprite*>>;

class ReadMap
{
public:
	MapData ReadFile(std::string path, std::map<char, sf::Texture>& targetMap)
	{
		std::string filename(path);
		std::ifstream inputFile(filename);
		std::vector<char> bytes;
		std::string line;
		char byte = 0;
		MapData res;

		if (!inputFile.is_open())
		{
			std::cerr << "Could not open the file - '" << filename << "'" << std::endl;
			throw std::runtime_error("ckc");
		}

		while (std::getline(inputFile, line))
		{
			std::vector<sf::Sprite*> lineSprites;
			for (auto lineChar : line)
			{
				std::map<char, sf::Texture>::iterator it = targetMap.end();
				switch (lineChar)
				{
				case '0':
				{
					std::cout << "void " << std::endl;
					break;
				}
				case '1':
				{
					std::cout << "ground " << std::endl;
					break;
				}
				case '2':
					std::cout << "bloc " << std::endl;
					break;
				default:
				{
					lineSprites.push_back(nullptr);
					break;
				}
				}
				if (it != targetMap.end())
				{
					sf::Sprite* sprite = new sf::Sprite();
					sprite->setTexture(it->second);
					lineSprites.push_back(sprite);
				}
			}
			res.push_back(lineSprites);
		}
		std::cout << std::endl;
		inputFile.close();
		return res;
	}
};