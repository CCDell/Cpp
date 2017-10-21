#pragma once
#include "Armour.h"

/* Basic type of armour. */
class Gloves:Armour {
private:

public:
	//Glove constructor
	Gloves(std::string * name, std::string * armourtype,int weight, int durability, int armourValue); 
};