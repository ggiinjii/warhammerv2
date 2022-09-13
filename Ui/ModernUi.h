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

    string _nameOrc;
    string _nameKnight;
    vector<Character*> _allianceSide;
    vector<Character*> _hordeSide;
    string _battleLog;

    bool _isGameStarted;
    bool _isGameOver;


public:
    ModernUi();
    ModernUi(vector<Character*> _allianceSide, vector<Character*> _hordeSide);
    ~ModernUi();

    void displayModernUi();


    char* LoadHordeNameFighter();
    char* LoadAllianceNameFighter();

    void AddTurnInfo(string log) { _battleLog = _battleLog+"\n"+ log; }
    void ResetTurnInfo() { _battleLog.clear(); }

    string GetLog() { return _battleLog; }

    void setFighter(vector<Character*> GoodGuy, vector<Character*> BadGuy) {
        _allianceSide = GoodGuy  ;
        _hordeSide = BadGuy ;
    }

    void setTurnNumber();

};

