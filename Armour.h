#pragma once
#include "stdafx.h"
#include "Items.h"
#include <string>

/*
	base class of all armour types
*/
class Armour:Item {
private:
	int durability; // if something breaks than it will be deleted. 
	int armourValue; // Amount of armour for damage reduction
	std::string * armourType; // type of armour (gloves, chestpiece, boots, etc)

public:
	int getDurability(); 
	int getArmourValue();
	//constructor
	Armour(std::string* name,std::string * armourType, int weight,int durability, int armourValue);

};
