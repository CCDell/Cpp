#include "stdafx.h"
#include "Weapon.h"
#include <string>
#include<iostream>

Weapon::Weapon(int damage, int durability,int weight,int range, std::string * sname , std::string * weaponType):Item(sname,weight){

	this->damage = damage;
	this->durability = durability;
	this->weaponType = weaponType;
	this->range = range;
}

int Weapon::getBaseDamage() { return damage; }

int Weapon::getDurability() { return durability; }

statScaling * Weapon::getStatScaling() { return scaling; }