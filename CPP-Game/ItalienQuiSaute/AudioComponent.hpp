#pragma once

#include "Component.hpp";
#include "Maths/Vector2.h";
#include "AudioManager.hpp";

class AudioComponent : public Component
{
public:
	AudioComponent(int index)
	{
		buffer = AudioManager::getBuffer(index);

	}




private:
	sf::SoundBuffer buffer;
	sf::Sound sound;

};