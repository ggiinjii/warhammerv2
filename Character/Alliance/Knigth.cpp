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
	std::stringstream ss;

	if (ennemy == nullptr)
	{
		result.SetMessage("Character NULL");
		result.SetResult(E_FAIL);
		return result;
	}

	srand((int)time(0));
	if (rand() % 100 > 40)
	{
		int damagedDealed = _weapon->DealDamage() * 2;

		_currentCd = _cdSpecialCapacity;
	
		ss << _nameCharacter << " use Special Capacity " << _nameCapacity << endl
			<< "Damage done : " << damagedDealed;
		ss << ennemy->GetHit(damagedDealed);

		result.SetResult(S_OK);
	}
	else
	{
		ss <<_nameCharacter << " Failed to use Special Capacity " << _nameCapacity;
		result.SetResult(S_FALSE);
		
	}

	result.SetMessage(ss.str());
	return result;

}
