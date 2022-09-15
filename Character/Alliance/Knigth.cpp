#include "Character/Alliance/Knigth.h"
#include <iostream>
#include "Tool/EnhancedHresult.h"

Knigth::Knigth(void)
{
	_weapon = nullptr;
	_armor = nullptr;
}

Knigth::Knigth(string name,int pv, Weapon* myWeapon, Armor* myArmor, int cdSpecialCapacity,string nameCapacity, Image img)
    : Character(name,pv, cdSpecialCapacity, myWeapon, myArmor, nameCapacity, img)
{
	_nameCapacity =  nameCapacity;
}

Knigth::~Knigth(void)
{

}

EnhancedHresult Knigth::SpecialCapacity(Character* ennemy)
{
	EnhancedHresult result;
	std::stringstream logFight;

	if (ennemy == nullptr)
	{
        PLOG_ERROR<<"Error: Ennemy NULL";
		result.SetMessage("Error Character NULL");
		result.SetResult(E_FAIL);
		return result;
	}

	srand((int)time(0));
	if (rand() % 100 > 40)
	{
        int damagedDealed = 0;
        if (_weapon!=nullptr)
        {
            damagedDealed=_weapon->DealDamage() * 2;
        }
        else {
            damagedDealed = 2; // No weapon, base damage = 1 multiplied by 2 due to special Capacity 
        }

		_currentCd = _cdSpecialCapacity;

		logFight << _nameCharacter << " use Special Capacity " << _nameCapacity << endl
			<< "Damage done : " << damagedDealed;
		logFight << ennemy->GetHit(damagedDealed);

		result.SetResult(S_OK);
	}
	else
	{
		logFight <<_nameCharacter << " failed to use special capacity " << _nameCapacity;
		result.SetResult(S_FALSE);

	}

	result.SetMessage(logFight.str());
	return result;

}
