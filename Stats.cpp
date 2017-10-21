#include "stdafx.h"
#include "Stats.h"

Stats::Stats(int value, std::string* name)
{
	this->name = name;
	this->value = value;
}

//getters
int Stats::getValue(){return value;}
std::string * Stats::getName(){	return name;}

//setters
void Stats::setValue(int value) { this->value = value; }

/*
	Default stats.
*/

Agility::Agility(int quantity) :Stats(quantity, new std::string("Agility")){}

Willpower::Willpower(int quantity) :Stats(quantity, new std::string("Willpower")){}

Strength::Strength(int quantity) :Stats(quantity, new std::string("Strength")){}

Speech::Speech(int quantity) :Stats(quantity, new std::string("Speech")){}

Stamina::Stamina(int quantity) :Stats(quantity, new std::string("Stamina")){}

Intelligence::Intelligence(int quantity):Stats(quantity, new std::string("Intelligence")){}
