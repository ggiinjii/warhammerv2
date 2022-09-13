#pragma once
#include <list>
#include <vector>
#include <string>
#include "Character/Character.h"
#include "GameObject/ModernGameGod.h"

using namespace std;

class ModernUi
{
private:

    int _turnNumber;
    std::list<string> _turnInformation;
    int _pvOrc, _pvMaxOrc;
    int _pvKnight, _pvMaxKnight;
    string _nameOrc;
    string _nameKnight;
    vector<Character*> _allianceSide;
    vector<Character*> _hordeSide;
    string _battleLog;

    bool _isGameStarted;
    bool _isGameOver;


public:
    ModernUi();
    ModernUi(vector<Character*> _allianceFighters, vector<Character*> _hordeFighters);
    ~ModernUi();

    void displayModernUi();


    char* LoadHordeNameFighter();
    char* LoadAllianceNameFighter();

    void AddTurnInfo(string log) { _battleLog = _battleLog+"\n"+ log; }
    void ResetTurnInfo() { _battleLog.clear(); }

    string GetLog() { return _battleLog; }

    void setFighter(vector<Character*> allianceFighters, vector<Character*> hordeFighters) {
        _allianceSide = allianceFighters  ;
        _hordeSide = hordeFighters ;
    }

    void setTurnNumber();

};

