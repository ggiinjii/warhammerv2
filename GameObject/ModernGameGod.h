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
    TurnInformation StartModernBattle(Character* allianceFighter, Character* hordeFighter);
    
    TurnInformation NextTurn(Character* allianceFighter, Character* hordeFighter);
    void AddTurnInfo(string info);
    void ResetTurnInfo();
    HRESULT LauchSpecialCapacity(Character* allianceFighter, Character* hordeFighter);
    HRESULT isAWinnerDecided(Character* allianceFighter, Character* hordeFighter);
    HRESULT ClassicFight(Character* allianceFighter, Character* hordeFighter);
    void setWinner(Character* winner);
    Character* GetWinner();

    void CheckStatusEffectForPlayers(Character* allianceFighter, Character* hordeFighter);
    void CheckStatusEffect(Character* fighter);

};

