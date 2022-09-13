#pragma once
#include "plog/Log.h"
#include <string>

using namespace std;

enum ARMORSTATUS
{
    PERFECT = 0,
    SCRATCHED,
    BROKEN,
    DEAD
};

class Armor
{
protected:
    int _pvMaxBonus = 0;
    int _pvBonus;
    ARMORSTATUS _status;

    string _name;
public:
    Armor(void);
    Armor(int PvBonus);
    virtual ~Armor(void);

    int getPvBonus();
    int GetPvMax() {
        return _pvMaxBonus;
    }

    void setPvBonus(int PvBonus);

    int getDamaged(int damaged);

    ARMORSTATUS getArmorStatus();

    string GetName() { return _name; }
    void SetName(string name) {
        _name = name;
    }
};

