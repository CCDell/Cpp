#pragma once
#include "FireSpells.h"

class Fireball:public FireSpells {
private:

public:
	Fireball();
	void spellEffect(LivingBeings*) override;
};