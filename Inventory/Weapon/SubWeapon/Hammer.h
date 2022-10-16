#pragma once
#include "Inventory/Weapon/Weapon.h"
#include <time.h>
#include <stdio.h>
#include <cstdlib>

// this class is created to be able to add special capacity 

class Hammer : public Weapon
{
public:

	Hammer(void);
	Hammer(int dammage);
	~Hammer(void);
    int SpecialCapacity();

};

