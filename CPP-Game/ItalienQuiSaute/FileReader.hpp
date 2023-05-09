#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <map>
#include "GameObject.hpp"
#include "Textures.hpp"


class ReadMap
{
public:
	void ReadFile(std::string path, std::map<char, sf::Texture>& targetMap, EntityManager* EM)
	{
		std::string filename(path);
		std::ifstream inputFile(filename);
		std::vector<char> bytes;
		std::string line;
		char byte = 0;

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
					GameObject* gobj = new GameObject(EM, Textures::getTexture(0), { x,y });
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
			}
			std::cout << x * 64 << std::endl;
			y++;
		}
		std::cout << y * 64<< std::endl;
		inputFile.close();
	}
};