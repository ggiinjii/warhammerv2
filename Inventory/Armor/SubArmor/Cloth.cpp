#include "Inventory/Armor/SubArmor/Cloth.h"

Cloth::Cloth()
{
	_pvBonus = 0;
}

Cloth::Cloth(int pvbonus) : Armor(pvbonus)
{
}

Cloth::~Cloth()
{
}
