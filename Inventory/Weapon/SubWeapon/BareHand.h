#pragma once
#include "Inventory/Weapon/Weapon.h"

class BareHand: public Weapon
{
public:
    BareHand();
   ~BareHand();
    BareHand(int dammage);
    int SpecialCapacity();
};

