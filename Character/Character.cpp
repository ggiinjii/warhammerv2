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
    std::stringstream logFight;

    if (Ennemy == nullptr)
        PLOG_ERROR<<"Error: Ennemy NULL";
        return E_FAIL;

    if (_characterStatus == STUN)
    {
        logFight<<_nameCharacter << " is Stun and can't attack";
        AddLog(logFight.str());
        return S_FALSE;
    }

    logFight<<_nameCharacter << " Attack";
    AddLog(logFight.str());


    int damage = 0;
    if (_weapon != nullptr)
    {
        damage = _weapon->DealDamage();

        logFight << _nameCharacter << " has a Weapon and will do " << damage << " point of damage to " << Ennemy->GetName();

    }
    else
    {
        damage = 1;// basic damage done by hand Combat
        logFight<<_nameCharacter << " has no Weapon and so will do 1 point of damage to " << Ennemy->GetName();
    }

    if (_currentCd > 0)
    {
        _currentCd = _currentCd - 1; // one turn passed, Cd go down
        PLOG_DEBUG<<"Turn Over, Cd go down, turn left : " << to_string(_currentCd);
    }

    string damageLog=Ennemy->GetHit(damage);

    logFight <<endl<< damageLog;

    AddLog(logFight.str());

    return S_OK;
}

string Character::GetHit(int damage)
{
    std::stringstream logFight;
    logFight <<endl<< _nameCharacter << " get hit\n";

    if (_armor != nullptr && _armor->getArmorStatus() != DEAD)
    {
        logFight << "His armor blocked " << damage << " point of damage\n";
        logFight << _nameCharacter << " status:";
        logFight << "\nArmor : " << to_string(_armor->getDamaged(damage)) <<"/"<<_armor->GetPvMax();
        logFight << "\nPv : " << to_string(_pv.getPv())<<"/"<< to_string(_pv.getPvMax());
    }
    else
    {
        _pv = _pv - damage;
        logFight << _nameCharacter<<" received : " << to_string(damage) << " point of damage\nPv left : " << to_string(_pv.getPv()) << "/" << to_string(_pv.getPvMax());
    }
    PLOG_INFO << logFight.str();
    return logFight.str();
}

bool Character::IsCharacterStillAlive()
{
    bool isStillAlive = (_pv.getPv() > 0);
    std::stringstream logFight;
    logFight << "\nis " << _nameCharacter << " still alive ? " << (isStillAlive ? "Yes" : "No");

    PLOG_DEBUG << logFight.str();
    return isStillAlive;
}

HRESULT Character::SpecialCapacityCheck(Character* ennemy)
{
    std::stringstream logFight;

    if (ennemy == nullptr)
    {
        PLOG_ERROR << "\nError: ennemy is null";
        logFight << "\nError: No ennemy (null)";
        AddLog(logFight.str());
        return E_FAIL;
    }

    if (_characterStatus == STUN)
    {
        logFight <<endl<< _nameCharacter << " is stun. End of his turn";
        AddLog(logFight.str());
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
        logFight <<endl<< _nameCharacter << " cannot Use Special Capacity : " << _nameCapacity << " this turn. He must wait: " << _currentCd << " turn";
        AddLog(logFight.str());

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

