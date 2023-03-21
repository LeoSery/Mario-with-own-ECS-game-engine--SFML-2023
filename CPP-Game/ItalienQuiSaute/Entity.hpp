#pragma once
#include <iostream>

class Entity
{
public:
	std::uint32_t UUID;
	std::string Name;
	std::string Tag;
	Entity(std::uint32_t UUID, std::string Name, std::string Tag)
	{
		this->UUID = UUID;
		this->Name = Name;
		this->Tag = Tag;
	}
};
