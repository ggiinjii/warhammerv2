#pragma once
#include "Inventory/Weapon/Weapon.h"

class Sword : public Weapon
{

public : 

	Sword(void);
	Sword(int damage);
	~Sword(void);
    int SpecialCapacity();

};

