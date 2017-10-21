#include "stdafx.h"
#include "Fireball.h"

Fireball::Fireball():FireSpells(new std::string("Fireball"))
{
}

void Fireball::spellEffect(LivingBeings *target)
{
	target->takeDamage(15);
}

