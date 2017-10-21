#include "stdafx.h"
#include "Polearm.h"

Spear::Spear() :Weapon(3, 15, 5, 4, new std::string("Spear"), new std::string("Polearm"))
{
	scaling->agility->setValue(2);
	scaling->strength->setValue(2);
}