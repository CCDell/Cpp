#include "stdafx.h"
#include "RoomEntities.h"

//setters
void RoomEntities::setLocationInRoom(int location) { this->locationInRoom = location; }

//getters
int RoomEntities::getLocationInRoom() { return locationInRoom; }
char RoomEntities::getMapSymbol(){return mapSymbol;}
int RoomEntities::getColour(){return colour;}
std::string* RoomEntities::getName(){return name;}
std::string* RoomEntities::getFaction() { return faction; }