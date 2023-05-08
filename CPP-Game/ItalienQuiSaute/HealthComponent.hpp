#pragma once

#include "Component.hpp";

class HealthComponent : public Component
{
public:
	bool isDead;
	HealthComponent()
	{
		Tag = "HEALTH";
		Health = 100.0f;
		isDead = false;
	}

	float GetHealth()
	{
		return Health;
	}

	float SetHealth(float newHealth)
	{
		Health = newHealth;
	}

	void TakeDamage(float amount)
	{
		Health -= amount;
		if (Health <= 0) {
			isDead = false;
		}
	}

	void TakeHeal(float amount)
	{
		Health += amount;
	}

private:
	
	float Health;
	
};