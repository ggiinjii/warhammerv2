#include "ModernGameGod.h"


ModernGameGod::ModernGameGod()
{
}

ModernGameGod::~ModernGameGod()
{

}

TurnInformation ModernGameGod::StartModernBattle(Character* goodGuy, Character* badGuy)
{
    _isGameOver = E_FAIL;
    _turnCount = 0;

    PLOG_INFO << "The battle Begin";

    TurnInformation logTurn = NextTurn(goodGuy, badGuy);
    return  logTurn;

}

TurnInformation ModernGameGod::NextTurn(Character* goodGuy, Character* badGuy)
{
    TurnInformation logTurn;
    _turnCount = _turnCount + 1;
    PLOG_INFO << "Turn No" << _turnCount;
    logTurn.setTurnNumber(_turnCount);

    AddTurnInfo("Special Capacity Phase");
    _isGameOver = LauchSpecialCapacity(goodGuy, badGuy);

    if (_isGameOver != S_OK)
    {
        AddTurnInfo("\n\nClassic Combat Phase");
        _isGameOver = ClassicFight(goodGuy, badGuy);

        if (_isGameOver == S_FALSE)
        {
            AddTurnInfo("\nCheck Condition of both players");
            CheckStatusEffectForPlayers(goodGuy, badGuy);
            logTurn.setIsGameOver(false);
        }
        else {
            _isGameOver = S_OK;
            logTurn.setIsGameOver(true);
        }
    }

    AddTurnInfo("\nEnd Of Turn\n");
    logTurn.setPvCharacter(goodGuy->GetPv(), badGuy->GetPv());
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


HRESULT ModernGameGod::LauchSpecialCapacity(Character* a, Character* b)
{
    if (a == nullptr || b == nullptr)
    {
        AddTurnInfo("Error with Character. Check logfile");
        PLOG_ERROR << "One of the caracter is Null:" << " - Character A: " << a << " - Character B:" << b;
        return E_FAIL;
    }

    AddTurnInfo("\n"+a->GetName() + " Launch Special Capacity\n");

    HRESULT result = a->SpecialCapacityCheck(b);

    std::list<string> characterlog = a->GetLog();

    for (auto const& i : characterlog) {
        AddTurnInfo(i);
    }


    HRESULT isAPlayerDead = isAWinnerDecided(a, b);

    if (isAPlayerDead == S_FALSE)
    {
        AddTurnInfo("\n"+b->GetName() + " Launch Special Capacity");

        b->SpecialCapacityCheck(a);

        characterlog = b->GetLog();

        for (auto const& i : characterlog) {
            AddTurnInfo(i);
        }

        isAPlayerDead = isAWinnerDecided(a, b);
    }

    a->ClearLog();
    b->ClearLog();

    return isAPlayerDead;

}


HRESULT ModernGameGod::isAWinnerDecided(Character* character1, Character* character2)
{
    if (!character1->IsCharacterStillAlive())
    {
        setWinner(character2);
        return S_OK;
    }
    else if (!character2->IsCharacterStillAlive())
    {
        setWinner(character1);
        return S_OK;
    }
    else
        return S_FALSE;
}

HRESULT ModernGameGod::ClassicFight(Character* a, Character* b)
{
    AddTurnInfo("\nCharacter " + a->GetName() + " Attack normaly\n");

    a->Attack(b);

    std::list<string> characterlog = a->GetLog();

    for (auto const& i : characterlog) {
        AddTurnInfo(i);
    }


    if (isAWinnerDecided(a, b) == S_FALSE)
    {
        AddTurnInfo("\nCharacter " + b->GetName() + " Attack normaly\n");

        b->Attack(a);

        characterlog = b->GetLog();

        for (auto const& i : characterlog) {
            AddTurnInfo(i);
        }
    }

    a->ClearLog();
    b->ClearLog();

    return isAWinnerDecided(a, b);
}

void ModernGameGod::setWinner(Character* winner)
{
    PLOG_INFO << "\nWe have a winner ";

    _winner = winner;
}

Character* ModernGameGod::GetWinner()
{
    return _winner;
}

void ModernGameGod::CheckStatusEffectForPlayers(Character* a, Character* b)
{
    CheckStatusEffect(a);
    CheckStatusEffect(b);

}


void ModernGameGod::CheckStatusEffect(Character* a)
{
    CONDITION status = a->getCharacterStatus();
    switch (status)
    {
    case STUN: a->setCharacterStatus(NORMAL);
        AddTurnInfo("\nCharacter " + a->GetName() + " Cured from STUN");
        break;

    case BURN: //TODO

    case FROZEN: //TODO

    case NORMAL:
        AddTurnInfo("\n"+a->GetName() + " status is NORMAL");

    default:

        break;
    }


}
