#include "stdafx.h"
#include "Magic.h"
#include <iostream>


Magic::Magic(std::string * spellName, std::string * spellType) {
	this->spellName = spellName;
	this->spellType = spellType;

}

std::string * Magic::getSpellName()
{
	return spellName;
}

std::string * Magic::getSpellType()
{
	return spellType;
}

void Magic::spellEffect(LivingBeings * target)
{
	std::cout << "In the virtual method spell effect";
}
