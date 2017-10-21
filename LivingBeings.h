#pragma once

#ifndef _LIVING_BEINGS
#define _LIVING_BEINGS
#include <string>
#include <vector>
#include "RoomEntities.h"


class LivingBeings : public RoomEntities{

protected:
	short damage; // damage of being
	bool inCombat = false; // whether or not the being is in combat

private:
	int maxHealth;
	int health; // health of being
	// target something for an attack
	virtual LivingBeings * target(std::vector<LivingBeings*>,std::vector<LivingBeings*>);

public:
	LivingBeings(int health, std::string * name, std::string *faction);
	int getHealth();
	std::string *getName();
	// update the livingBeing in combat
	virtual void combatUpdate(std::vector<LivingBeings*>enemies, std::vector<LivingBeings*>allies);
	void takeDamage(int); // takes damage.
	void setInCombat(bool b); 
	bool getInCombat();
	void heal(int amountHealed);

};

#endif

