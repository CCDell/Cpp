#include "stdafx.h"
#include "Items.h"
#include <iostream>

Item::Item(std::string * name, int weight)
{
	this->name = name; // name of the item 
	this->weight = weight; // affects movespeed ( maybe later )

}

std::string * Item::getName() { return name; }