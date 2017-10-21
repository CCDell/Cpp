#pragma once
#include"stdafx.h"
#include <string>

class Stats{
public:
	Stats(int value,std::string * name);
	//getters
	int getValue();
	std::string * getName();
	//setters
	void setValue(int);

private:
	int value; // just the number of the stats
	std::string * name; // name of the stat
};

/*
Constructors to quickly make the only stats in the game.
*/

class Agility :public Stats {
public:
	Agility(int);
};
class Willpower :public Stats {
public:
	Willpower(int);
};
class Strength :public Stats {
public:
	Strength(int);
};
class Speech :public Stats {
public:
	Speech(int);
};
class Stamina :public Stats {
public:
	Stamina(int);
};
class Intelligence :public Stats {
public:
	Intelligence(int);
};
