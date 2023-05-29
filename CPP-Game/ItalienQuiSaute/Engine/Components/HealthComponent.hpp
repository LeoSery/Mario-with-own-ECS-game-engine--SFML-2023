#pragma once

#include "Component.hpp";

class HealthComponent : public Component
{
public:
	HealthComponent()
	{
		Tag = "HEALTH";
		Health = 100;
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

	}

	void TakeHeal(int amount)
	{
		Health += amount;
	}

	bool GetisDead()
	{
		if (Health <= 0) {
			return true;
		}
		return false;
	}

private:
	int Health;
};