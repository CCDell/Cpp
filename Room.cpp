
#include "stdafx.h"
#include "Room.h"
#include <vector>
#include <iostream>
#include <random>
#include "RoomEntities.h"
#include "Steamers.h"
#include "Door.h"
#include <iostream>
#include "Combat.h"


Room::Room(short location) {
	
	entered = false;
	//Assigns the location of every potential neighbouring room's doors
	rooms.nRoom->roomLocation = (int)roomColumns / 2;
	rooms.eRoom->roomLocation = (roomColumns*(((int)roomRows / 2)+1)) - 1;
	rooms.sRoom->roomLocation = roomColumns*(roomRows-1) + (int)roomRows / 2;
	rooms.wRoom->roomLocation = roomColumns * ((int)(roomRows / 2));
} 

//Getters
short Room::getDifficulty() { return difficulty; }
bool Room::getEntered() { return entered; }
short Room::getRoomColumns() { return roomColumns; }
short Room::getRoomRows() { return roomRows; }

void Room::printRoom() {
	// print the room. 
	
	for (int i = 0; i < roomRows; i++) {
		for (int j = 0; j < roomColumns; j++) {

			int currentRoomTile = i*roomColumns + j;

			if (roomEntities[currentRoomTile] != nullptr) { //if the spot is not open, then it has a symbol and colour to print specifically
				
				SetConsoleTextAttribute(hConsole, roomEntities[currentRoomTile]->getColour()); // assign the text to that colour
				std::cout << roomEntities[currentRoomTile]->getMapSymbol() << " "; //print that spot's symbol
			}
			else {
				std::cout << "0 "; 
			}// otherwise it is a white 0 
			SetConsoleTextAttribute(hConsole, _WHITE); // change text back to white
		}//end for for one row
		std::cout << "\n";
	}//end row making another row for loop
	std::cout << "\n";
}


Room * Room::updateRoom() {
	static std::vector<Combat*> combats; // combats in the current room taking place.
	/* 
	if the player is not in combat update him as normal. This is just general movement around the room.
	*/
	if (!player->getInCombat()) { 
		/*
		Get player input for movement
		*/
		
		//Get the player's new Location
		short newPlayerLocation = player->update(roomColumns, roomRows);

		if (canMove(newPlayerLocation)) {
			roomEntities[player->getLocationInRoom()] = nullptr;
			roomEntities[newPlayerLocation] = player;
			player->setLocationInRoom(newPlayerLocation);
			canExit = true;
		}  // if the player's new location is one that is availible to be moved on, set his location there and allow 
		//the player to exit.
		/*
		If the player's new location interacts with a door, then open the door
		*/

		if (player->getLocationInRoom() == this->rooms.nRoom->roomLocation + roomColumns && canExit) {
			return rooms.nRoom->newRoom;
		}// if you are next to the entry, go backwards on the map
		else if (player->getLocationInRoom() == this->rooms.eRoom->roomLocation - 1 && canExit) {
			return rooms.eRoom->newRoom;
		} // if you are exiting, go forward.
		else if (player->getLocationInRoom() == this->rooms.sRoom->roomLocation - roomColumns && canExit) {
			return rooms.sRoom->newRoom;
		} // if you are exiting, go forward.
		else if (player->getLocationInRoom() == this->rooms.wRoom->roomLocation + 1 && canExit) {
			return rooms.wRoom->newRoom;
		} // if you are exiting, go forward.
	}
	/*
	UPDATE STEAMERS
	*/

	for (int i = 0; i < roomSteamers.size(); i++) {
		// updating steamers like a normal person.
		// Makes them move and stuff so long as they're not in combat
		if (!roomSteamers[i]->getInCombat()) {
			short oldLocation = roomSteamers[i]->getLocationInRoom();
			short newLocation = roomSteamers[i]->update(player->getLocationInRoom(), this->roomColumns, roomRows);

			if (roomEntities[newLocation] == nullptr) {

				roomEntities[newLocation] = roomEntities[oldLocation];
				roomEntities[oldLocation] = nullptr;
				delete roomEntities[oldLocation];
				roomEntities[newLocation]->setLocationInRoom(newLocation);
			}// if the steamer can move in the place the update method has , set his location in the position

			else if (!(roomEntities[newLocation]->getFaction()->compare("object") == 0) && 
				!(roomEntities[newLocation]->getFaction()->compare(*roomEntities[oldLocation]->getFaction())==0)) {
				
				LivingBeings * potentialEnemy = dynamic_cast<LivingBeings*>(roomEntities[newLocation]);
				if (combats.size() != 0) {
					for (int j = 0; j < combats.size(); j++) {
						if (combats[j]->inThisCombat(potentialEnemy)) {
							combats[j]->addToCombat(roomSteamers[i]); 
							break;
						}//end if 
						else if (j == combats.size() - 1) {
							combats.emplace_back(new Combat(potentialEnemy, roomSteamers[i]));
						}//end elseif
					}//end for
				}//end if
				else if (combats.size() == 0) {
					combats.emplace_back(new Combat(potentialEnemy, roomSteamers[i]));
				}//end elseif
			} // end elseif
		}//end in combat if
	} // end update loop for steamers
	for (int i = 0; i < combats.size(); i++) { combats[i]->updateCombat(); } // update all combats

	return nullptr;
}


/* Method deciding if something can move into the location*/
bool Room::canMove(short location)
{
	if (roomEntities[location]!=nullptr) {
		return false;
	}
	else { return true; } 
}

/* Creates the room by assigning all locations as null and then adding the exits to the room, the player, and the
steamers in that order*/

void Room::onFirstEntry()
{

	// returns the new location of the player, without erasing the previous location to allow the pointer to be altered.
	// Make the room have things in it 
	roomEntities.assign(roomColumns*roomRows, nullptr); // assign empty tile pieces to the floor 

	for (int i = 1; i < 10; i++) {
		if (roomEntities[i] == nullptr) {
			player->setLocationInRoom(i);
			break;
		} // make the player's startpoint refer to the player
	}
	doorLocation();

	for (int i = 0; i < 3;) { // Creates the steamers in the room in random(ish) locations 
		short steamerLocation = rand() % (roomColumns*roomRows);

		if (roomEntities[steamerLocation] == nullptr) {
			roomSteamers.emplace_back(new Steamers(difficulty, steamerLocation));
			roomEntities.at(steamerLocation) = roomSteamers.back();
			i++;
			steamerCount++; 
		}
	} // maker steamers, or enemies

	entered = true;
}

/* the "main" loop for the room that the player is in. This sets the player at the location that corresponds to the 
room he came from ( if came from a room to the left of the room, will be placed at the left, or west, door)
returns the new room the player will be exiting to.*/

Room * Room::roomLoop(Player * player, short entryPoint)
{
	this->player = player; // assigns the player to the player of the room
	if (!entered) {	onFirstEntry(); }// if the player has never been in the room, set the room up with onFirstEntry call


	/*sets the player's location in the room based on where he entered from. */
	if (rooms.nRoom->newRoom != nullptr && entryPoint == rooms.nRoom->newRoom->locationOnMap){ player->setLocationInRoom(rooms.nRoom->roomLocation+roomColumns); }
	else if( rooms.eRoom->newRoom != nullptr && entryPoint == rooms.eRoom->newRoom->locationOnMap) { player->setLocationInRoom(rooms.eRoom->roomLocation-1); }
	else if (rooms.sRoom->newRoom != nullptr && entryPoint == rooms.sRoom->newRoom->locationOnMap) { player->setLocationInRoom(rooms.sRoom->roomLocation-roomColumns); }
	else if (rooms.wRoom->newRoom != nullptr && entryPoint == rooms.wRoom->newRoom->locationOnMap) { player->setLocationInRoom(rooms.wRoom->roomLocation+1); }
	roomEntities[player->getLocationInRoom()] = player; // sets the location that the player is on as the player itself

	Room * exitedRoom; // declare a pointer to room that the player will exit into 
	do { // general update loop. 
		printRoom(); // print the room
		exitedRoom = updateRoom(); // update the room and return a new room if the player has exited the room. 
	} while (player->getHealth()>0 && !exitedRoom);

	roomEntities[player->getLocationInRoom()] = nullptr;
	
	return exitedRoom;
}

/* place the new rooms in their respective locations, otherwise make them an inaccessible number*/
void Room::doorLocation() {
	if (rooms.nRoom->newRoom != nullptr) {
		roomEntities[rooms.nRoom->roomLocation] = new Door();
	}
	else { rooms.nRoom->roomLocation = -2; }

	if (rooms.eRoom->newRoom != nullptr) {
		roomEntities[rooms.eRoom->roomLocation] = new Door();
	}
	else { rooms.eRoom->roomLocation = -2; }

	if (rooms.sRoom->newRoom != nullptr) {
		roomEntities[rooms.sRoom->roomLocation] = new Door();
	}
	else { rooms.sRoom->roomLocation = -2; }

	if (rooms.wRoom->newRoom != nullptr) {
		roomEntities[rooms.wRoom->roomLocation] = new Door();
	}
	else { rooms.wRoom->roomLocation = -2; }
}

//Assign the exits. This method takes the locations of the surrounding rooms and assigns them to their respective direction
//relative to this room. A little bit messy.

void Room::assignExits(Room * exitLocations[4]) {
	
	if (exitLocations[0] != nullptr) {
		rooms.nRoom->newRoom = exitLocations[0];
	}	
	else { rooms.nRoom->newRoom = nullptr; }
	if (exitLocations[1] != nullptr) {
		rooms.eRoom->newRoom = exitLocations[1];
	}
	else { rooms.eRoom->newRoom = nullptr; }
	if (exitLocations[2] != nullptr) {
		rooms.sRoom->newRoom = exitLocations[2];
	}
	else { rooms.sRoom->newRoom = nullptr; }
	if (exitLocations[3] != nullptr) {
		rooms.wRoom->newRoom = exitLocations[3];
	}
	else { rooms.wRoom->newRoom = nullptr; }
}