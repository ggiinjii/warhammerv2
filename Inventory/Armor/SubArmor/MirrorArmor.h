#pragma once
#include "Inventory/Armor/Armor.h"


class MirrorArmor : public Armor
{
private: 
	int _nbUse = 2;

public: 
	MirrorArmor();
	~MirrorArmor();

	int ReflectDamage(int damagereceive);
};

