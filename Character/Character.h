#pragma once
#include <string>
#include "include/plog/Log.h"
#include "Inventory/Weapon/SubWeapon/Sword.h"
#include "Inventory/Armor/SubArmor/Shield.h"
#include "Tool/EnhancedHresult.h"
#include "Tool/Image.h"
#include <winerror.h>
#include <list>

#include "Tool/Pv.h"

using namespace std;

enum CONDITION {
	NORMAL=0,
	STUN,
	FROZEN,
	BURN
};

class Character
{
protected:
	string _nameCharacter;
	Pv _pv;
	const int _cdSpecialCapacity=0;
	int _currentCd;
	CONDITION _characterStatus;
	string _nameCapacity;

	Weapon* _weapon;
	Armor* _armor;

	list<string> _log;

    Image _img;

public :
	Character();
	Character(string name,int pv, int cdSpecialCapacity, Weapon* myWeapon, Armor* myArmor, string nameCapacity, Image img);
	~Character();

	void AddLog(string msg);
	void ClearLog();
	list<string> GetLog();

	void SetPv(Pv pv);
    Pv GetPv();

	void setCharacterStatus(CONDITION status);
	CONDITION getCharacterStatus();

	HRESULT Attack(Character* Ennemy);
	string GetHit(int damage);
	bool IsCharacterStillAlive();

	HRESULT SpecialCapacityCheck(Character* ennemy);
	virtual EnhancedHresult SpecialCapacity(Character* ennemy) = 0;

	string GetName();
	void SetWeapon(Weapon* weapon);
	void SetArmor(Armor* armor);
	void SetCurrentCd(int cd);
    string GetNameCapacity() { return _nameCapacity; }
    Weapon* GetWeapon() { return _weapon; }
    Armor* GetArmor() { return _armor; }
    Image getImage() { return _img; }
    void setImg(Image img) { _img = img; };

};

