#include "Character/Horde/Orc.h"
#include <iostream>
#include "Tool/EnhancedHresult.h"

Orc::Orc(void)
{
}

Orc::Orc(string name, int pv, Weapon* myWeapon, Armor* myArmor, int cdSpecialCapacity, string nameCapacity, Image img)
    : Character(name,pv, cdSpecialCapacity, myWeapon, myArmor, nameCapacity, img)
{
	
}

Orc::~Orc(void)
{
}

EnhancedHresult Orc::SpecialCapacity(Character* ennemy)
{
	EnhancedHresult result;
    std::stringstream ss;

	if (ennemy == nullptr)
	{
		result.SetMessage("Character NULL");
		result.SetResult(E_FAIL);
		return result;
	}

	srand((int)time(0));
	if (rand() % 100 > 80)
	{
		ennemy->setCharacterStatus(STUN);	
		ss << _nameCharacter << " use Special Capacity: " << _nameCapacity << " - Ennemy Stun for 1 turn";

		result.SetResult(S_OK);
	}
	else
	{
		ss << _nameCharacter << " failed to use Special Capacity : " << _nameCapacity;
		result.SetResult(S_FALSE);
	}

	result.SetMessage(ss.str());
	return result;
}
