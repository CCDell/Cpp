#include "stdafx.h"
#include "Armour.h"

Armour::Armour(std::string * name,std::string * armourType, int weight, int durability, int armourValue):Item(name,weight)
{
	this->durability = durability;
	this->armourValue = armourValue;
	this->armourType = armourType;
}

int Armour::getDurability() { return durability; }

int Armour::getArmourValue() { return armourValue; }
