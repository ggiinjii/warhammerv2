#include "Inventory/Weapon/SubWeapon/Sword.h"

Sword::Sword(void)
{
}

Sword::Sword(int damage)
	: Weapon(damage)
{
}

Sword::~Sword(void)
{
}

int Sword::SpecialCapacity()
{
    // todo

    return 0;
}
