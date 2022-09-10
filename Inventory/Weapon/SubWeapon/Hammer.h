#pragma once
#include "Inventory/Weapon/Weapon.h"
#include <time.h>
#include <stdio.h>
#include <cstdlib>

// The Hammer is a very Powerfull weapon which can deal 2x his basic dammage with 75% of precision. 

class Hammer : public Weapon
{
public:

	Hammer(void);
	Hammer(int dammage);
	~Hammer(void);

};

