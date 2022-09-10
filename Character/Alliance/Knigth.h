#pragma once
#include <stdio.h>
#include "Character/Character.h"
#include <winerror.h>

class Knigth : public Character
{
private:


public:

	Knigth(void);
	Knigth(string name, int pv, Weapon* myWeapon, Armor* myArmor, int cdSpecialCapacity, string nameCapacity, Image img);
	~Knigth(void);

	// Fight Capacity
	EnhancedHresult SpecialCapacity(Character* ennemy);
};

