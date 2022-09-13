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
    std::stringstream LogFight;

	if (ennemy == nullptr)
	{
        PLOG_ERROR<<"Error: Ennemy NULL";
		result.SetMessage("Ennemy NULL");
		result.SetResult(E_FAIL);
		return result;
	}

	srand((int)time(0));
	if (rand() % 100 > 80)
	{
		ennemy->setCharacterStatus(STUN);
		LogFight << _nameCharacter << " use Special Capacity: " << _nameCapacity << " - Ennemy Stun for 1 turn";

		result.SetResult(S_OK);
	}
	else
	{
		LogFight << _nameCharacter << " failed to use Special Capacity : " << _nameCapacity;
		result.SetResult(S_FALSE);
	}

	result.SetMessage(LogFight.str());
	return result;
}
