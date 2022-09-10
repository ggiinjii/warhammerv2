#include "Pv.h"

Pv::Pv()
{
    _pvCurrent = 0;
    _pvmax = 0;
}
Pv::Pv(int pv, int pvMax)
{
    _pvCurrent = pv;
    _pvmax = pvMax;
}
Pv::~Pv()
{

}
