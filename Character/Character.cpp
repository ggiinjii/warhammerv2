#include "Character/Character.h"
#include <iostream>
#include <string>

Character::Character()
{
    _pv.SetFullPv(0);
    _characterStatus = NORMAL;
    _currentCd = 0;
}

Character::Character(string name, int pv, int cdSpecialCapacity, Weapon* myWeapon, Armor* myArmor, string nameCapacity, Image img)
    : _nameCharacter(name), _cdSpecialCapacity(cdSpecialCapacity), _weapon(myWeapon), _armor(myArmor), _nameCapacity(nameCapacity), _img(img)
{
    _pv.SetFullPv(pv);
    _characterStatus = NORMAL;
    _currentCd = 0;
}

Character::~Character()
{
}



void Character::ClearLog()
{
    _log.clear();
}
list<string> Character::GetLog()
{
    return _log;
}

void Character::SetPv(Pv pv)
{
    _pv = pv;
}

Pv Character::GetPv() { return _pv; }

void Character::setCharacterStatus(CONDITION status)
{
    _characterStatus = status;
}

CONDITION Character::getCharacterStatus()
{
    return _characterStatus;
}

HRESULT Character::Attack(Character* Ennemy)
{
    std::stringstream ss;

    if (Ennemy == nullptr)
        return E_FAIL;

    if (_characterStatus == STUN)
    {
        AddLog(_nameCharacter + " is Stun and Can't attack");
        return S_FALSE;
    }

    AddLog(_nameCharacter + " Attack");


    int damage = 0;
    if (_weapon != nullptr)
    {
        damage = _weapon->DealDamage();
       
        ss << _nameCharacter << " Has a Weapon and will do " << damage << " point of damage to Ennemy " << Ennemy->GetName();
        
    }
    else
    {
        damage = 1;// basic damage done by hand Combat
        ss<<_nameCharacter << " Has no Weapon and will do 1 point of damage";
    }

    if (_currentCd > 0)
    {
        _currentCd = _currentCd - 1; // one turn passed, Cd go down
        PLOG_DEBUG<<"Turn Over, Cd go down, turn left : " << to_string(_currentCd);
    }

    string damageLog=Ennemy->GetHit(damage);

    ss <<endl<< damageLog;

    AddLog(ss.str());

    return S_OK;
}

string Character::GetHit(int damage)
{
    std::stringstream ss;
    ss <<endl<< _nameCharacter << " get hit\n";

    if (_armor != nullptr && _armor->getArmorStatus() != DEAD)
    {
        ss << "His armor blocked " << damage << " point of damage\n";
        ss << _nameCharacter << " status:";
        ss << "\nArmor : " << to_string(_armor->getDamaged(damage)) <<"/"<<_armor->GetPvMax();
        ss << "\nPv : " << to_string(_pv.getPv())<<"/"<< to_string(_pv.getPvMax());
    }
    else
    {
        _pv = _pv - damage;
        ss << _nameCharacter<<" Received : " << to_string(damage) << " Point of Damage\nPv Left : " << to_string(_pv.getPv()) << "/" << to_string(_pv.getPvMax());
    }
    PLOG_INFO << ss.str();
    return ss.str();
}

bool Character::IsCharacterStillAlive()
{
    bool isStillAlive = (_pv.getPv() > 0);
    std::stringstream ss;
    ss << "\nis " << _nameCharacter << " still alive ? " << (isStillAlive ? "Oui" : "Non");
   
    PLOG_DEBUG << ss.str();
    return isStillAlive;
}

HRESULT Character::SpecialCapacityCheck(Character* ennemy)
{
    std::stringstream ss;

    if (ennemy == nullptr)
    {
        PLOG_ERROR << "ennemy is null";
        ss << "\nNo ennemy Error";
        AddLog(ss.str());
        return E_FAIL;
    }

    if (_characterStatus == STUN)
    {
        ss <<endl<< _nameCharacter << " is stun. End of his turn";
        AddLog(ss.str());
        return S_FALSE;
    }

    if (_currentCd == 0)
    {
        _currentCd = _cdSpecialCapacity;


        EnhancedHresult result= SpecialCapacity(ennemy);
        AddLog(result.getMessage());

        if (result.getResult() != E_FAIL)
            return S_OK;
        else 
            return E_FAIL;
    }
    else
    {
        ss <<endl<< _nameCharacter << " Cannot Use Special Capacity : " << _nameCapacity << " this turn. He must wait: " << _currentCd << " turn";
        AddLog(ss.str());

        return S_FALSE;
    }
}

string Character::GetName()
{
    return _nameCharacter;
}

void Character::SetWeapon(Weapon* weapon)
{
    _weapon = weapon;
}

void Character::SetArmor(Armor* armor)
{
    _armor = armor;
}

void Character::SetCurrentCd(int cd)
{
    _currentCd = cd;
}

void Character::AddLog(string msg) {
    PLOG_INFO << msg;
    _log.push_back(msg);
}

