#pragma once

#include "stdafx.h"
#include "LivingBeings.h"

class Steamers: public LivingBeings {

public:
	Steamers(int roomLevel,short LocationInRoom);
	// 
	int update(short playerLocation,short roomColumns, short roomRows);
	void combatUpdate(std::vector<LivingBeings * >enemies, std::vector<LivingBeings*>allies) override;
private:
	
};

