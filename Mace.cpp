#include "stdafx.h"
#include "Mace.h"
#include <iostream>
BlackJack::BlackJack() :Weapon(2, 10, 2,1, new std::string("BlackJack"), new std::string("Mace"))
{
	scaling->agility->setValue(1);
	scaling->strength->setValue(1);
}

Torch::Torch() :Weapon(1, 10, 2,2, new std::string("Torch"), new std::string("Mace"))
{
	scaling->intelligence->setValue(2);
	scaling->strength->setValue(1);
}

Wrench::Wrench() :Weapon(2, 15, 4,2, new std::string("Wrench"), new std::string("Mace"))
{
	scaling->strength->setValue(1);
}
 