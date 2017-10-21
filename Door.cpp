#include "stdafx.h"
#include "Door.h"

Door::Door()
{
	colour = 0x05;  // doors are purplish
	mapSymbol = '<' ; // they look like left arrows
	name = new std::string("Door");
	faction = new std::string("object");
}