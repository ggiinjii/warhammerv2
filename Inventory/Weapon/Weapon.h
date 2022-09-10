#pragma once

#include <string.h>
#include "plog/Log.h"

using namespace std;

class Weapon
{
protected:
	int _dammage;
    string _name;

public:
	Weapon(void);
	Weapon(int dammage);
	~Weapon(void);

	int DealDamage();

	void setDamage(int damage);

    string GetName() { return _name; };
    void SetName(string name) {
        _name = name;
    }
};

