#pragma once

#include <SFML/Audio.hpp>
#include <iostream>

class AudioManager
{
public:
	static sf::SoundBuffer getBuffer(const int& texEnum)
	{
		switch (texEnum)
		{
		case 0:
			return loadBuffer("Assets/Audio/sound.wav");
			break;
		case 1:
			return loadBuffer("Assets/Audio/sound.wav");
			break;
		case 2:
			return loadBuffer("Assets/Audio/sound.wav");
			break;
		case 3:
			return loadBuffer("Assets/Audio/sound.wav");
			break;
		case 5:
			return loadBuffer("Assets/Audio/sound.wav");
			break;
		case 6:
			return loadBuffer("Assets/Audio/sound.wav");
			break;
		case 7:
			return loadBuffer("Assets/Audio/sound.wav");
			break;
		case 8:
			return loadBuffer("Assets/Audio/sound.wav");
			break;
		default:
			break;
		}
	}

	static sf::SoundBuffer loadBuffer(const std::string& filename)
	{

		sf::SoundBuffer buffer;
		if (!buffer.loadFromFile(filename))
			std::cerr << "Failed to load audio from file : " << filename << std::endl;


		return buffer;
	}

};