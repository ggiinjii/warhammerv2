#pragma once
class Pv
{
private:
    int _pvCurrent;
    int _pvmax;

public:

    Pv();
    Pv(int pv, int pvMax);
    ~Pv();

    void SetPv(int pv){
        _pvCurrent = pv;
    };
    void SetFullPv(int pv)
    {
        _pvCurrent = pv;
        _pvmax = pv;
    }
    int getPv() { return _pvCurrent; }
    int getPvMax() { return _pvmax; }
    Pv operator-  (const int pv)
    {
        _pvCurrent = this->_pvCurrent - pv;
        return Pv(_pvCurrent, _pvmax);
    }
};

