#pragma once
#include <string>
#include"LivingBeings.h"

class Magic {
private:
	std::string * spellName;
	std::string * spellType;
protected:

public:
	std::string * getSpellName();
	std::string * getSpellType();
	virtual void spellEffect(LivingBeings* target);
	Magic(std::string * spellName, std::string * spellType);
};
