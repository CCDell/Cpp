#include "stdafx.h"
#include "Sword.h"



ShortSword::ShortSword() :Weapon(2, 10, 2,2, new std::string("Short Sword"), new std::string("Sword"))
{
	scaling->agility->setValue(2);
}