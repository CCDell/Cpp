#include "stdafx.h"
#include "Player.h"


Player::Player(std::string *characterName, char classType) :LivingBeings(50, characterName, new std::string("Allies")) {

	items = new equippedItems();

	if (toupper(classType) == 'E') { setClassEngineer(); }
	else if (toupper(classType) == 'W') { setClassWarrior(); }
	else if (toupper(classType) == 'M') { setClassMage(); }
	else if (toupper(classType) == 'R') { setClassRogue(); }
	locationInRoom = 1;
	mapSymbol = '$';
	colour = 0x02;

}

int Player::update(short roomColumns, short roomRows) {
	char playerMove;
	do {
		std::cout << "Please make a move:\n";
		std::cin >> playerMove;
		playerMove = toupper(playerMove);
	} while (playerMove != 'W'&&playerMove != 'S'&&playerMove != 'A'&&playerMove != 'D' && playerMove != 'X'); // loop for player input for move

	if (playerMove == 'W' && (this->locationInRoom - roomColumns) >= 0 ) {
		return this->locationInRoom - roomColumns;
	} // if W go up, based on subtraction of column count, as one row ( that we must go up) is equal to X amount of columns
	else if (playerMove == 'D'&& this->locationInRoom + 1 < roomColumns* roomRows && (this->locationInRoom + 1) % roomColumns != 0 ) {
		return this->locationInRoom + 1;
	} // if D go right 
	else if (playerMove == 'S' && this->locationInRoom + roomColumns < roomColumns*roomRows ) {
		return this->locationInRoom + roomColumns;
	} // if S go down based on similar principles to that of W
	else if (playerMove == 'A'&& this->locationInRoom - 1 >= 0 && this->locationInRoom % roomColumns != 0) {
		return this->locationInRoom - 1;
	} // if A go left
	else { return locationInRoom; }
	
	//Simply decides where the player moves, and whether or not he can go there based on the size
	// of the room.
}

void Player::combatUpdate(std::vector<LivingBeings*> enemies, std::vector<LivingBeings*> allies)
{
	std::cout << "\nMake a move!\n";
	std::cout << "\nAttack: A\nMagic: M\nInventory: I\nNothing: X\n";
	char playerChoice;
	do {
		std::cin >> playerChoice;
	} while (playerChoice !='a'&&playerChoice != 'm'&&playerChoice != 'i'&&playerChoice != 'x');
	playerChoice = toupper(playerChoice);

	if (playerChoice == 'A') { // if the player wants to attack
		/*
		** gets the damage of nonnull weapons in both hands of the player**
		*/
		this->damage = items->lHandWeapon!=nullptr? items->lHandWeapon->getBaseDamage():0
			+ items->rHandWeapon!=nullptr? items->rHandWeapon->getBaseDamage():0;
		
		target(enemies, allies)->takeDamage(damage); // returns the player's choice of target and deal damage to it 
	}
	else if (playerChoice == 'M') { // if the player wants to use magic
		
		std::cout << "Please choose a spell to use.";
		int spellCount = 1; // increment for the spells. used to find which spell the player would
		// like to use 

		//Loop listing the spells with specified numbers so the player can pick the spell they
		//would like.
		for (int i = 0; i < spellList.size();i++){
			for (int j = 0; j < spellList[i]->spells.size(); j++) {
				if (j == 0) {
					std::cout << "\n"<<* spellList[i]->spellTypeName<<":\n";

				} // end if 
				std::cout << "\t" << spellCount << "; " << * spellList[i]->spells[j]->getSpellName()<<"\n";
				spellCount++;
			}	// end inner for 
		}// end outer for 

		spellCount = 0; // reset for next loop set
		int playerChoice;

		do {
			
			std::cin >> playerChoice;
			playerChoice -= 1;

		} while (playerChoice < spellCount || playerChoice < 0);
		// loop through all spells to match the player's choice wiht the spell they want
		for (int i = 0; i < spellList.size(); i++) { 
			for (int j = 0; j < spellList[i]->spells.size(); j++) {
				
				if (spellCount == playerChoice) {
					// if the spell is the spell the player desires, use its effect on a target.
					spellList[j]->spells[i]->spellEffect(target(enemies, allies));
					break;
				}
				spellCount++;
			}
		}

	}
	else if (playerChoice =='I'){ 
		
	}
}

LivingBeings * Player::target(std::vector<LivingBeings*> enemies, std::vector<LivingBeings*> allies)
{

	std::cout << "\nPlease pick a target to attack:\n";
	std::cout << "\nEnemies:\n";

	short targetNumber = 1; // To list the targets in an ordered manner for printing 

	for (int i = 0; i < enemies.size(); i++) {
		std::cout << targetNumber << ". " << *enemies[i]->getName() << " Health: " << enemies[i]->getHealth() << "\n";
		targetNumber++;
	} // prints all of the targets that are enemies and their respective number
	std::cout << "\nAllies\n";
	for (int i = 0; i < allies.size(); i++) {
		std::cout << targetNumber << ". " << *allies[i]->getName() << " Health: " << allies[i]->getHealth() << "\n";
		targetNumber++;
	} // prints all ally targets and their respective number 

	std::cin >> targetNumber; // get which target the player would like to target.

	targetNumber -= 1;

	if (targetNumber < enemies.size()) { return enemies[targetNumber]; }
	else if (targetNumber >= enemies.size()) { return allies[targetNumber - enemies.size()]; }
	else { std::cout << "There was an error in player targeting"; }
	return nullptr;
}

//getters
short Player::getCurrentLevel() {return currentLevel;}



//Setters
void Player::setClassEngineer()
{
	playerClass->className = new std::string("Engineer"); // name
	playerClass->willpower = new Willpower(5); // willpower
	playerClass->strength = new Strength(7); // strength
	playerClass->intelligence = new Intelligence(5);//intelligence
	playerClass->agility = new Agility(5);//agility
	playerClass->speech = new Speech(5); // speech
	playerClass->stamina = new Stamina(7);//stamina

	items->lHandWeapon = new Shank();
}
void Player::setClassWarrior()
{
	playerClass->className = new std::string("Warrior"); // name
	playerClass->willpower = new Willpower(5); // willpower
	playerClass->strength = new Strength(7); // strength
	playerClass->intelligence = new Intelligence(5);//intelligence
	playerClass->agility = new Agility(5);//agility
	playerClass->speech = new Speech(5); // speech
	playerClass->stamina = new Stamina(7);//stamina 

	items->rHandWeapon = new ShortSword();
	items->lHandWeapon = new Buckler();
}
void Player::setClassMage()
{
	playerClass->className = new std::string("Mage"); //  name
	playerClass->willpower = new Willpower(5); // willpower
	playerClass->strength = new Strength(7); // strength
	playerClass->intelligence = new Intelligence(5);//intelligence
	playerClass->agility = new Agility(5);//agility
	playerClass->speech = new Speech(5); // speech
	playerClass->stamina = new Stamina(7);//stamina 

	items->lHandWeapon = new Torch();
	
	spellList.emplace_back(new spellType(new Fireball()) );
}

void Player::setClassRogue()
{
	playerClass->className = new std::string("Rogue"); // name
	playerClass->willpower = new Willpower(5); // willpower
	playerClass->strength = new Strength(7); // strength
	playerClass->intelligence = new Intelligence(5);//intelligence
	playerClass->agility = new Agility(5);//agility
	playerClass->speech = new Speech(5); // speech
	playerClass->stamina = new Stamina(7);//stamina 

	items->rHandWeapon = new BlackJack();
}

Player::spellType::spellType( Magic * firstSpell) {
	spellTypeName = firstSpell->getSpellType();
	spells.emplace_back(firstSpell);
}
