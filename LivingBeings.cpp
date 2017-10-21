
#include "stdafx.h"
#include "LivingBeings.h"
#include <iostream>


LivingBeings::LivingBeings(int health, std::string* name,std::string *faction)
{
	this->maxHealth = this->health = health;
	this->name = name;
	this->faction = faction;
}



void LivingBeings::combatUpdate(std::vector<LivingBeings*>, std::vector<LivingBeings*>)
{
	std::cout << "\nYou are currently in the virtual method of combat update for living beings\n";
}
void LivingBeings::takeDamage(int enemyDamage)
{
	this->health -= enemyDamage; 
}

LivingBeings * LivingBeings::target(std::vector<LivingBeings*>, std::vector<LivingBeings*>)
{
	std::cout << "\nYou are in the virtual function for target.\n";
	return nullptr;
}

void LivingBeings::setInCombat(bool b) { inCombat = b; }

int LivingBeings::getHealth() { return this->health; }

std::string * LivingBeings::getName() { return name; }

bool LivingBeings::getInCombat(){ return inCombat; }

void LivingBeings::heal(int amountHealed)
{
	if (this->health+amountHealed < this->maxHealth) {
		this->health = this->health + amountHealed;
	}
	else { health = maxHealth; }
}
