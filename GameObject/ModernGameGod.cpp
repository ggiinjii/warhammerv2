#include "ModernGameGod.h"


ModernGameGod::ModernGameGod()
{
}

ModernGameGod::~ModernGameGod()
{

}

TurnInformation ModernGameGod::StartModernBattle(Character* allianceFighter, Character* hordeFighter)
{
    _isGameOver = E_FAIL;
    _turnCount = 0;

    PLOG_INFO << "The battle Begin";

    TurnInformation logTurn = NextTurn(allianceFighter, hordeFighter);
    return  logTurn;

}

TurnInformation ModernGameGod::NextTurn(Character* allianceFighter, Character* hordeFighter)
{
    TurnInformation logTurn;
    _turnCount = _turnCount + 1;
    PLOG_INFO << "Turn No" << _turnCount;
    logTurn.setTurnNumber(_turnCount);

    AddTurnInfo("Special Capacity Phase");
    _isGameOver = LauchSpecialCapacity(allianceFighter, hordeFighter);

    if (_isGameOver != S_OK)
    {
        AddTurnInfo("\n\nClassic Combat Phase");
        _isGameOver = ClassicFight(allianceFighter, hordeFighter);

        if (_isGameOver == S_FALSE)
        {
            AddTurnInfo("\nCheck Condition of both players");
            CheckStatusEffectForPlayers(allianceFighter, hordeFighter);
            logTurn.setIsGameOver(false);
        }
        else {
            _isGameOver = S_OK;
            logTurn.setIsGameOver(true);
        }
    }

    AddTurnInfo("\nEnd Of Turn\n");
    logTurn.setPvCharacter(allianceFighter->GetPv(), hordeFighter->GetPv());
    logTurn.setTurnLog(_logTurn);
    if (_isGameOver==S_OK && _winner!=NULL)
        logTurn.setWinner(_winner->GetName());

    return logTurn;
}

void ModernGameGod::AddTurnInfo(string info)
{
    PLOG_INFO << info;
    _logTurn= _logTurn +info;
}
void ModernGameGod::ResetTurnInfo()
{
    _logTurn.clear();
}


HRESULT ModernGameGod::LauchSpecialCapacity(Character* allianceFighter, Character* hordeFighter)
{
    if (allianceFighter == nullptr || hordeFighter == nullptr)
    {
        AddTurnInfo("Error with Character. Check logfile");
        PLOG_ERROR << "One of the caracter is Null:" << " - Character allianceFighter: " << allianceFighter << " - Character hordeFighter:" << hordeFighter;
        return E_FAIL;
    }

    AddTurnInfo("\n"+allianceFighter->GetName() + " Launch Special Capacity\n");

    HRESULT result = allianceFighter->SpecialCapacityCheck(hordeFighter);

    std::list<string> characterlog = allianceFighter->GetLog();

    for (auto const& i : characterlog) {
        AddTurnInfo(i);
    }


    HRESULT isAPlayerDead = isAWinnerDecided(allianceFighter, hordeFighter);

    if (isAPlayerDead == S_FALSE)
    {
        AddTurnInfo("\n"+hordeFighter->GetName() + " Launch Special Capacity");

        hordeFighter->SpecialCapacityCheck(allianceFighter);

        characterlog = hordeFighter->GetLog();

        for (auto const& i : characterlog) {
            AddTurnInfo(i);
        }

        isAPlayerDead = isAWinnerDecided(allianceFighter, hordeFighter);
    }

    allianceFighter->ClearLog();
    hordeFighter->ClearLog();

    return isAPlayerDead;

}


HRESULT ModernGameGod::isAWinnerDecided(Character* allianceFighter, Character* hordeFighter)
{
    if (!allianceFighter->IsCharacterStillAlive())
    {
        setWinner(hordeFighter);
        return S_OK;
    }
    else if (!hordeFighter->IsCharacterStillAlive())
    {
        setWinner(allianceFighter);
        return S_OK;
    }
    else
        return S_FALSE;
}

HRESULT ModernGameGod::ClassicFight(Character* allianceFighter, Character* hordeFighter)
{
    AddTurnInfo("\nCharacter " + allianceFighter->GetName() + " Attack normaly\n");

    allianceFighter->Attack(hordeFighter);

    std::list<string> characterlog = allianceFighter->GetLog();

    for (auto const& i : characterlog) {
        AddTurnInfo(i);
    }


    if (isAWinnerDecided(allianceFighter, hordeFighter) == S_FALSE)
    {
        AddTurnInfo("\nCharacter " + hordeFighter->GetName() + " Attack normaly\n");

        hordeFighter->Attack(allianceFighter);

        characterlog = hordeFighter->GetLog();

        for (auto const& i : characterlog) {
            AddTurnInfo(i);
        }
    }

    allianceFighter->ClearLog();
    hordeFighter->ClearLog();

    return isAWinnerDecided(allianceFighter, hordeFighter);
}

void ModernGameGod::setWinner(Character* winner)
{
    PLOG_INFO << "\nWe have allianceFighter winner ";

    _winner = winner;
}

Character* ModernGameGod::GetWinner()
{
    return _winner;
}

void ModernGameGod::CheckStatusEffectForPlayers(Character* allianceFighter, Character* hordeFighter)
{
    CheckStatusEffect(allianceFighter);
    CheckStatusEffect(hordeFighter);

}


void ModernGameGod::CheckStatusEffect(Character* fighter)
{
    CONDITION status = fighter->getCharacterStatus();
    switch (status)
    {
    case STUN: fighter->setCharacterStatus(NORMAL);
        AddTurnInfo("\nCharacter " + fighter->GetName() + " Cured from STUN");
        break;

    case BURN: //TODO

    case FROZEN: //TODO

    case NORMAL:
        AddTurnInfo("\n"+ fighter->GetName() + " status is NORMAL");

    default:

        break;
    }

}
