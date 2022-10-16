#pragma once
#include "Inventory/Armor/Armor.h"

class Cloth: public Armor
{
public: 
    Cloth();
    Cloth(int pvbonus);
    virtual ~Cloth();

};

