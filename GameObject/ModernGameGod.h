#pragma once
#include "Character/Character.h"
#include "Tool/TurnInformation.h"

class ModernGameGod
{
    //Game Mandatory Variable
    HRESULT _isGameOver;
    int _turnCount;
    Character* _winner;
    string _logTurn;

public :
    ModernGameGod();
    ~ModernGameGod();
    TurnInformation StartModernBattle(Character* goodGuy, Character* badGuy);
    
    TurnInformation NextTurn(Character* goodGuy, Character* badGuy);
    void AddTurnInfo(string info);
    void ResetTurnInfo();
    HRESULT LauchSpecialCapacity(Character* a, Character* b);
    HRESULT isAWinnerDecided(Character* character1, Character* character2);
    HRESULT ClassicFight(Character* a, Character* b);
    void setWinner(Character* winner);
    Character* GetWinner();

    void CheckStatusEffectForPlayers(Character* a, Character* b);
    void CheckStatusEffect(Character* a);

};

