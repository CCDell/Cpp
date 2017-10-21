#pragma once
#include "stdafx.h"
#include "Items.h"
#include "Stats.h"

struct statScaling {
	/*
	For each point in the stat, it scales for one additional dmg. ex
	scales 4 with agi, if the base damage is 5 and someone has 10 agi the damage is
	45
	*/
	Willpower * willpower = new Willpower(0);
	Strength * strength = new Strength(0);
	Intelligence * intelligence = new Intelligence(0);
	Agility * agility = new Agility(0);
	Speech * speech = new Speech(0);
};

class Weapon : public Item {
protected:
	statScaling  *scaling = new statScaling();// inherited stat scaling for each weapon
private:
	
	int damage; // how much damage the weapon will do to enemies
	int durability; // how long the weapon will take to break
	int range; // the reach of the weapon.
	// May be remove this.
	std::string * weaponType; // The type of weapon the weapon is


public:
	Weapon(int damage, int durability,int weight,int range, std::string* name, std::string *weaponType); 
	int getBaseDamage();
	int getDurability();
	statScaling * getStatScaling();
};



