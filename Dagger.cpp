#include "stdafx.h"
#include "Dagger.h"





Shank::Shank() :Weapon(1, 10, 1,1, new std::string("Shank"), new std::string("Dagger")) {
	scaling->agility = new Agility(2);

}

KitchenKnife::KitchenKnife():Weapon(2, 10, 1, 1, new std::string("Kitchen Knife"), new std::string("Dagger"))
{
	scaling->agility = new Agility(2);
}
