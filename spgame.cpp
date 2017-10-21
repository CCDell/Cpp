//============================================================================
// Name        : Maze.cpp
// Author      : Noah Sanci
// Version     :
// Copyright   : Don't copy my stuff please
// Description : 
//============================================================================

#include "stdafx.h"
#include "LevelMaker.h"
#include "Steamers.h"
#include "Player.h"
#include "windows.h"

#include <iostream>
#include <stdlib.h>
#include <vector>

int main() {

	cout << "Please enter your class; \nE:Engineer\nW:Warrior\nM:Mage\nR:Rogue\n";
	char playerClass;

	bool reloop = false;
	do {
		if (reloop) { cout << "\nPlease enter a valid class:\n"; }
		
		//std::cin >> playerClass;
		playerClass = 'm';
		reloop = true;
	} while ( toupper(playerClass) != 'E' && toupper(playerClass) != 'M' && toupper(playerClass) != 'W' && toupper(playerClass) != 'R');



	playerClass = toupper(playerClass);
	// And also sets the player's position to the beginning of the maze.
	// try to clarify code

	Player * player = new Player(new std::string("player"), playerClass);

	LevelMaker * currentLevel = new LevelMaker(0);// Makes a new LevelMaker with the player's  level for difficulty 

	short previousRoomLocation = -1;
	do{
		currentLevel->printMazeAnswer(); // prints current state of the maze
		Room* currentRoom = currentLevel->getPlayerRoom();

		currentLevel->update(currentRoom->roomLoop(player,previousRoomLocation));
		previousRoomLocation = currentRoom->locationOnMap;
	} while (true);

	return 0;
}



