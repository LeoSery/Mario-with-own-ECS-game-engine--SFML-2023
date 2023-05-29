#pragma once

#include <iostream>

class Entity
{
public:
	std::uint32_t UUID; //Is unique
	std::string Name;
	std::string Tag;  //TODO: use RTTI and remove tags to avoid casting

	Entity() = default;

	Entity(std::uint32_t UUID, std::string Name, std::string Tag)
	{
		this->UUID = UUID;
		this->Name = Name;
		this->Tag = Tag;
	}

	//operators used to loop through vector in EntityManager
	bool operator ==(const Entity& en2) const
	{
		return UUID == en2.UUID;
	}

	bool operator <(const Entity& en2) const
	{
		return UUID < en2.UUID;
	}
};
