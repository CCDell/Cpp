#pragma once
#include "stdafx.h"
#include <string>

class Item {
private:
	std::string *name; // name of the weapon
	int weight; // Weight will have an effect on various speeds
public:
	Item(std::string *name, int weight); 
	std::string* getName();
};