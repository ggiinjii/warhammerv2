#include "MirrorArmor.h"


MirrorArmor::MirrorArmor()
{
	_nbUse = 0;
}

MirrorArmor::~MirrorArmor()
{
}


int MirrorArmor::ReflectDamage(int damagereceive)
{
	if (_nbUse =! 0)
	{
		_nbUse = _nbUse - 1;

		return damagereceive * 2;
	}
}
