#pragma once
#include <string>
#include "Pv.h"
#include <winerror.h>

using namespace std;

class TurnInformation
{
private:
    string _turnLog;
    int _turnNumber;
    bool _isGameOver;
    Pv _pvCharacter1;
    Pv _pvCharacter2;
    HRESULT _isExecutionWell;

    string _winner;

public:
    TurnInformation();
    ~TurnInformation();

    string getlog() { return _turnLog; };
    int getTurnNumber() { return _turnNumber; };
    bool getIsGameOver() { return _isGameOver; }

    void setTurnNumber(int nb) { _turnNumber= nb; };
    void setTurnLog( string log) { _turnLog= log; };
    void setIsGameOver(bool IsGameOver) { _isGameOver = IsGameOver; }

    void setPvCharacter(Pv Character1, Pv Character2)
    {
        _pvCharacter1 = Character1;
        _pvCharacter2 = Character2;
    }
    HRESULT getIsExecutionWell() {
        return _isExecutionWell;
    }

    Pv getPvCharacter1() {
        return _pvCharacter1;
    }
    Pv getPvCharacter2() {
        return _pvCharacter2;
    }

    void setWinner(string winner)
    {
        _winner = winner;
    }
    string getWinner() { return _winner; }
};

