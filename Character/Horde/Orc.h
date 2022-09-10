#pragma once
#include "Character/Character.h"
#include "Inventory/Weapon/SubWeapon/Sword.h"
#include "Inventory/Armor/SubArmor/Shield.h"
#include <stdio.h>
#include <time.h>

class Orc: public Character
{
private:

public:

	Orc(void);
	Orc(string name, int pv, Weapon* myWeapon, Armor* myArmor, int cdSpecialCapacity,string nameCapacity, Image img);
	~Orc(void);

	// Fight Capacity
	EnhancedHresult SpecialCapacity(Character* ennemy);

};

