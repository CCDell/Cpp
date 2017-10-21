#pragma once
#ifndef _ROOMS_H
#define _ROOMS_H

#define _GREEN 0x02
#define _BLUE 0x05
#define _RED  0x04
#define _BLACK 0x00
#define _WHITE 0x0f
#define _YEN ¥

#include "RoomEntities.h"
#include <random>
#include <vector>
#include "windows.h"
#include "Player.h"
#include "Steamers.h"

class Room {
public:

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	Room(short = 0);// Room constructor, makes the dimensions of the room.

	short locationOnMap; // location on map
	void onFirstEntry(); // on first entry into the room, locations of enemies are assigned and the maze is filled
	void printRoom(); // prints the room and all of its contents, including the player in his location.
	Room* roomLoop(Player *, short); // basic loop for the room
	//get functions
	bool getEntered();
	short getDifficulty(); // returns the room's difficulty
	short getRoomColumns();
	short getRoomRows();
	void assignExits(Room* exitLocations[4]);
private:
	// structure holding a pointer to a neighbouring room, and the location of the door in the room
	struct neighbouringRooms { 
		Room * newRoom;
		short roomLocation;
	};
	struct Rooms {
		public:
			neighbouringRooms * nRoom = new neighbouringRooms();
			neighbouringRooms * eRoom = new neighbouringRooms();
			neighbouringRooms * sRoom = new neighbouringRooms();
			neighbouringRooms * wRoom = new neighbouringRooms();
	};
	Rooms rooms; 
	bool entered; // whether or not the room is enterd
	short difficulty = rand() % 3 + 2; // room difficulty
	std::vector<Steamers*> roomSteamers; // All steamers
	std::vector<RoomEntities*> roomEntities; // All things on this floor
	const short roomColumns = rand() % 10 + 5;  // number of columns and rows, because this room is a square. =)
	const short roomRows = rand() % 10 + 5;
	short steamerCount; // number of steamers (enemies)
	Room * updateRoom(); // updates the room, may take the new lcation of the player
	bool canMove(short); // finds if the location can be moved to, the number being the new location
	bool canExit = false; // so that the player must move away from a door before leaving a room
	Player * player; //Pointer to the player};
	void doorLocation(); // forms exits of a room
};
#endif