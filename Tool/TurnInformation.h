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
    Pv _pvAllianceFighter;
    Pv _pvHordeFighter;
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

    void setPvCharacter(Pv AllianceFighter, Pv HordeFighter)
    {
        _pvAllianceFighter = AllianceFighter;
        _pvHordeFighter = HordeFighter;
    }
    HRESULT getIsExecutionWell() {
        return _isExecutionWell;
    }

    Pv getPvAllianceFighter() {
        return _pvAllianceFighter;
    }
    Pv getPvHordeFighter() {
        return _pvHordeFighter;
    }

    void setWinner(string winner)
    {
        _winner = winner;
    }
    string getWinner() { return _winner; }
};

