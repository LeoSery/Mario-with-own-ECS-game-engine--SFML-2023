#pragma once

#include <iostream>

class Entity
{
public:
	std::uint32_t UUID;
	std::string Name;
	std::string Tag;
	Entity() = default;
	Entity(std::uint32_t UUID, std::string Name, std::string Tag)
	{
		this->UUID = UUID;
		this->Name = Name;
		this->Tag = Tag;
	}
	bool operator ==(const Entity& en2) const
	{
		return UUID == en2.UUID;
	}
	bool operator <(const Entity& en2) const
	{
		return UUID < en2.UUID;
	}
};
