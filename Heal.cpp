#include "stdafx.h"
#include "Heal.h"

Heal::Heal():HolySpells(new std::string("Heal")) {}

void Heal::spellEffect(LivingBeings * healTarget)
{
	healTarget->heal(amountHealed);
}
