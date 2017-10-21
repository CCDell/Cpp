#include "stdafx.h"
#include "Combat.h"
#include <iostream>
#define uint unsigned int

Combat::Combat(LivingBeings * firstEnemy, LivingBeings * secondEnemy)
{
	/* 
	This adds two new factions to the combat, as required to have a combat.
	*/

	addToCombat( firstEnemy); 
	addToCombat( secondEnemy);

	printCombat();
}

void Combat::addToCombat(LivingBeings * addingBeing)
{	
	addingBeing->setInCombat(true);
	/* 
	Add something to the combat by looking through all factions and adding it
	to a similar faction or making a new "side" to the fight.
	*/
	if ( combatants.size() == 0 ) {
		combatants.emplace_back(new factionTeam(addingBeing));
	}
	else {
		short originalCombatantsSize = combatants.size();
		for (int i = 0; i < originalCombatantsSize; i++) {

			if (combatants[i]->faction == addingBeing->getFaction()) {
				combatants[i]->factionMembers.emplace_back(addingBeing);
			}
			else if (i == combatants.size()-1) {
				combatants.emplace_back(new factionTeam(addingBeing));
			}
		}

	}
}

void Combat::updateCombat()
{ 
	for (int i = 0; i < combatants.size(); i++){ // go through each faction 
		for (int j = 0; j < combatants[i]->factionMembers.size(); j++) { // go through each faction member
			combatants[i]->factionMembers[j]->combatUpdate( findEnemies(combatants[i]->factionMembers[j]->getFaction()),combatants[i]->factionMembers); // update each one 
		}
	}
}

bool Combat::inThisCombat(LivingBeings * potentialEnemy){
	//check if a living being is in this combat. if they are return true

	for (int i = 0; i < combatants.size(); i++) {
		for (int j = 0; j < combatants[i]->factionMembers.size(); j++) {
			if (potentialEnemy == combatants[i]->factionMembers[j]) { 
				return true;
			}
		}
	}
	
	return false;
}

void Combat::printCombat()
{
	std::cout << "\nCombat!\n" << "Combatants:\n";
	for (uint i = 0; i < combatants.size(); i++) {
		std::cout << *combatants[i]->faction << ":\n	";
		for (uint j = 0; j < combatants[i]->factionMembers.size(); j++) {
			std::cout << *combatants[i]->factionMembers[j]->getName() << "\n";
		}
	}
}

std::vector<LivingBeings *>  Combat::findEnemies(std::string * currentBeingFaction)
{
	std::vector<LivingBeings *>  enemies;
	for (uint i = 0; i < combatants.size(); i++) {
		//search through all factions that rae not the same as the faction of the attacking being
		if (combatants[i]->faction == currentBeingFaction) { continue; }

		else { 
			for (uint j = 0; j < combatants[i]->factionMembers.size(); j++) {
				enemies.emplace_back(combatants[i]->factionMembers[j]);
			}
		}
	}
	
	
	return enemies;
}

/*
	FactionTeam methods
*/

factionTeam::factionTeam( LivingBeings * factionMember)
{
	this->faction = factionMember->getFaction();
	this->factionMembers.emplace_back(factionMember);
}

