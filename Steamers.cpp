#include "stdafx.h"
#include "Steamers.h"
#include <iostream>

Steamers::Steamers(int roomDifficulty, short locationInRoom) :LivingBeings(roomDifficulty * 15 + 20, new std::string("Steamer") , new std::string("Steamers"))
{
	damage = roomDifficulty * 10 + 15;
	colour = 0x04;
	mapSymbol = '+';
	this->locationInRoom = locationInRoom;


}

int Steamers::update(short playerLocation,short roomColumns, short roomRows){

	short newLocationInRoom = 0;
	/*Both variablaes here are declared in a sense that is relative to that of the player's*/
	/*
	PLAYER EQUALIZER
	*/
	//X:
	/*
	The X equalizers allow the x location of hte player and steamer to be compared on an x-only axis resembling a 2-d array.
	*/

	short playerXEqualizer = 0;
	for (int i = 0; i < roomRows; i++) {
		if (i*roomColumns>playerLocation) {
			break;
		}
		playerXEqualizer = i;
	} 
	playerXEqualizer = playerLocation - playerXEqualizer*roomColumns;

	//Y
	//The Y equalizers do something similar to that of the x equalizer, in that it simply relates the location of the steamer and player on an x-y plain, however
	// 
	short playerYEqualizer = 0;
	for (int i = 0; i < roomRows;i++) {
		if (i*roomColumns>playerLocation) {
			break;
		}
		playerYEqualizer = i;
	}
	/* improve this equation
	The y equalizer effectively pushes the player's y value to the furthest left of the room it can go, then finds how many rows down the player is from the 
	top right corner by dividing the player's y value by the amount of columns that the room has, because each new row beings wiht a multiple of the columns a whole
	number is always provided and is then able to be compared to the steamer y value. 
	*/
	int difference = playerLocation - playerYEqualizer*roomColumns;
	playerYEqualizer = (playerLocation - difference)/roomColumns;

	/*
	Steamer Equalizer
	*/
	//X
	/*
	Works the same as the player x equalizer found above.
	*/
	short steamerXEqualizer = 0;
	for (int i = 0; i < roomRows; i++) {
		if (i*roomColumns > this->locationInRoom) {
			break;
		}
		steamerXEqualizer = i;
	}
	steamerXEqualizer = this->locationInRoom - steamerXEqualizer *roomColumns;

	//Y
	/*
	Works the same as the player y equalizer found above.
	*/
	short steamerYEqualizer = 0;
	for (int i = 0; i < roomRows; i++) {
		if (i*roomColumns > this->locationInRoom) {
			break;
		}
		steamerYEqualizer = i;
	}
	difference = this->locationInRoom - steamerYEqualizer*roomColumns;
	steamerYEqualizer = (this->locationInRoom - difference) / roomColumns;

	int playerVerticalDirectionSpaces = playerYEqualizer - steamerYEqualizer;
	int playerHorizontalDirectionSpaces = playerXEqualizer - steamerXEqualizer;

	if ((playerHorizontalDirectionSpaces > 0 && playerVerticalDirectionSpaces > 0 && playerVerticalDirectionSpaces > playerHorizontalDirectionSpaces )||
		(playerHorizontalDirectionSpaces > 0 && playerVerticalDirectionSpaces < 0 && playerHorizontalDirectionSpaces + playerVerticalDirectionSpaces<=0)||
		(playerVerticalDirectionSpaces == 0 && playerHorizontalDirectionSpaces>0)) {
		newLocationInRoom = this->locationInRoom + 1;
	}// Make the steamer move right, assuming the conditions are correct
	else if ((playerHorizontalDirectionSpaces < 0 && playerVerticalDirectionSpaces <  0 &&  playerHorizontalDirectionSpaces > playerVerticalDirectionSpaces )||
			(playerHorizontalDirectionSpaces < 0 && playerVerticalDirectionSpaces > 0 && playerHorizontalDirectionSpaces + playerVerticalDirectionSpaces>=0)||
			(playerVerticalDirectionSpaces== 0 && playerHorizontalDirectionSpaces<0)) {
				newLocationInRoom=this->locationInRoom - 1;
	}// make the steamer move left, assuming the conditions are correct
	else if ((playerVerticalDirectionSpaces > 0 && playerHorizontalDirectionSpaces > 0 && playerVerticalDirectionSpaces < playerHorizontalDirectionSpaces )||
		(playerVerticalDirectionSpaces>0 && playerHorizontalDirectionSpaces < 0 && playerVerticalDirectionSpaces + playerHorizontalDirectionSpaces < 0)||
		(playerHorizontalDirectionSpaces == 0 && playerVerticalDirectionSpaces>0)){
		newLocationInRoom = this->locationInRoom + roomColumns;
	}// make the steamer move down, assuming the conditions are correct
	else if ((playerVerticalDirectionSpaces < 0 && playerHorizontalDirectionSpaces < 0 && playerVerticalDirectionSpaces > playerHorizontalDirectionSpaces) ||
		(playerVerticalDirectionSpaces < 0 && playerHorizontalDirectionSpaces > 0 && playerVerticalDirectionSpaces + playerHorizontalDirectionSpaces > 0) ||
		(playerHorizontalDirectionSpaces == 0 && playerVerticalDirectionSpaces < 0)) {
		newLocationInRoom = this->locationInRoom - roomColumns;
	}// make the steamer move up, assuming the conditions are correct
	else { return locationInRoom; }
	return newLocationInRoom;
}

void Steamers::combatUpdate(std::vector<LivingBeings*> enemies, std::vector<LivingBeings*> allies)
{

	std::cout << "\nin the combat update method for steamers\n";

}
 
