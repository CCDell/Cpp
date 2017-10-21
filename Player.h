#pragma once

#ifndef _PLAYER
#define _PLAYER

#include "LivingBeings.h"
#include <string>
#include "Stats.h"
#include <vector>
#include <iostream>
#include "Gloves.h"
#include "Weapons.h"
#include "AllSpells.h"

class Player:public LivingBeings {

private:
	struct Classes { /* class struct of stats*/
		std::string* className;
		Willpower * willpower;
		Strength * strength;
		Intelligence * intelligence;
		Agility *agility;
		Speech * speech;
		Stamina * stamina;
	}*playerClass = new Classes;

	struct equippedItems {
		Gloves* gloves; 
		Weapon * rHandWeapon;
		Weapon * lHandWeapon;
	}*items = new equippedItems;
	
	struct spellType {
		spellType(Magic * firstSpell);
		std::string * spellTypeName;
		std::vector<Magic *> spells;
	};

	std::vector<spellType*> spellList;

	static const short statCount = 6; // Stat Count 
	int baseDamage = 5;// damage
	short currentLevel = 0; // current level
	// overload of the virtual target method, for targeting something to act on it
	LivingBeings * target(std::vector<LivingBeings*>, std::vector<LivingBeings*>);
public:
	Player(std::string *characterName, char characterClass);/*:LivingBeings(health,name)*/

	int update(short roomColumns, short roomRows);
	void combatUpdate(std::vector<LivingBeings*>, std::vector<LivingBeings*>);
	//getters
	short getCurrentLevel();

	//setters
	void setClassEngineer();
	void setClassWarrior();
	void setClassMage();
	void setClassRogue();
};
#endif

