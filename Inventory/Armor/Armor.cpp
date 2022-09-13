#include "Inventory/Armor/Armor.h"
#include <string>

using namespace std;

Armor::Armor(void)
{
    _status = PERFECT;
    _pvBonus = 0;
    _pvMaxBonus = _pvBonus;
}

Armor::Armor(int PvBonus) : _pvBonus(PvBonus)
{
    _status = PERFECT;
    _pvMaxBonus = _pvBonus;

}

Armor::~Armor(void)
{
}

int Armor::getPvBonus()
{
    return _pvBonus;
}

void Armor::setPvBonus(int PvBonus)
{
    PLOG_DEBUG << "Current pv of the armor set to: " << PvBonus;
    _pvBonus = PvBonus;
    _pvMaxBonus = PvBonus;
}

int Armor::getDamaged(int damaged)
{
    _pvBonus = _pvBonus - damaged;

    PLOG_DEBUG << "Armor get damaged"
    <<damaged << " point of damage taken, Pv left "<< PvBonus;

    double PercentDamage = ((double)_pvBonus / _pvMaxBonus) * 100;

    if (PercentDamage > 90.0)
    {
        _status = PERFECT;
    }
    else if (PercentDamage > 50.0)
    {
        _status = SCRATCHED;
    }
    else if (PercentDamage > 20.0)
    {
        _status = BROKEN;
    }
    else {
        _status = DEAD;
    }

    return _pvBonus;
}

ARMORSTATUS Armor::getArmorStatus()
{
    return _status;
}
