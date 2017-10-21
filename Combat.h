#pragma once
#include "LivingBeings.h"
#include <string>


/*
	structure that holds all members of a faction in a combat.
*/
struct factionTeam {
public:
	factionTeam(LivingBeings*);
	std::string * faction; // faction of this particular team
	std::vector<LivingBeings *> factionMembers; // vector of all of the members on the team of the same faction
};

class Combat {
	
public:

	Combat(LivingBeings *, LivingBeings * );
	void addToCombat(LivingBeings *); // Adds someting to the combat
	void updateCombat(); // updates the combat
	bool inThisCombat(LivingBeings *); // Checks to see if a LivingBeing is in the combat 
private:
	void printCombat(); // prints combat
	std::vector<factionTeam*> combatants; //all combatatns in a combat
	std::vector<LivingBeings*>  findEnemies(std::string *); // finds all enemies in a combat based on faction.
};