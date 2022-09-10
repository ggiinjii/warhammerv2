#include "Inventory/Weapon/Weapon.h"

Weapon::Weapon(void)
{
	_dammage = 0;
}

Weapon::Weapon(int damage)
{
	_dammage = damage;
}

Weapon::~Weapon(void)
{
}

int Weapon::DealDamage()
{
	PLOG_INFO << "Dammaged Dealed: " << _dammage;
	return _dammage;
}

void Weapon::setDamage(int damage)
{
	_dammage = damage;
	PLOG_DEBUG << "Damage set to:" << _dammage;
}
