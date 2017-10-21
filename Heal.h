#pragma once
#include "HolySpells.h"
#include "LivingBeings.h"

class Heal:public HolySpells{
private:
	int amountHealed;

public:
	Heal();
	void spellEffect(LivingBeings *)override;
};
