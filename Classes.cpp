#include "stdafx.h"
#include "Classes.h"

Classes::Classes(char classType)
{
	if (toupper(classType) == 'E') { setClassEngineer(); }
	else if (toupper(classType) == 'W') { setClassWarrior(); }
	else if (toupper(classType) == 'M') { setClassMage(); }
	else if (toupper(classType) == 'R') { setClassEngineer(); }
}








