#pragma once

#include "Component.hpp";

class HealthComponent : public Component
{
public:
	bool isDead;
	HealthComponent()
	{
		Tag = "HEALTH";
		Health = 100;
		isDead = false;
	}

	float GetHealth()
	{
		return Health;
	}

	float SetHealth(int newHealth)
	{
		Health = newHealth;
	}

	void TakeDamage(int amount)
	{
		Health -= amount;
		if (Health <= 0) {
			isDead = true;
			std::cout << "is dead : " << isDead << std::endl;
		}
		std::cout << "Health : " << Health << std::endl;
	}

	void TakeHeal(int amount)
	{
		Health += amount;
	}

private:
	int Health;
};