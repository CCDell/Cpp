#pragma once
#ifndef _ROOM_ENTITIES
#define _ROOM_ENTITIES
#include <string>

class RoomEntities {
protected:
	int colour; // colour of entity in console
	int locationInRoom; // location of entity in the room
	char mapSymbol; // symbol of the entity in the room in console text
	std::string * name; // name of entity
	std::string * faction; // faction of the entity
public:
	//getters
	int getLocationInRoom();
	char getMapSymbol();
	int getColour();
	virtual std::string * getName();
	std::string * getFaction();
	//setters 
	void setLocationInRoom(int location);

};
#endif