#include "GameObject/GameGod.h"
#include "Character/Alliance/Knigth.h"
#include "Character/Horde/Orc.h"
#include "Character/Character.h"
#include "Inventory/Weapon/SubWeapon/Hammer.h"
#include "Inventory/Armor/SubArmor/MirrorArmor.h"
#include "Inventory/Weapon/SubWeapon/BareHand.h"
#include "Inventory/Armor/SubArmor/Cloth.h"
#include "Ui/ModernUi.h"
#include <iostream>
#include "Tool/Image.h"
#include "include/nlohmann/json.hpp"

GameGod::GameGod(void)
{
    _winner = nullptr;
    _allianceFighter = nullptr;
    _hordeFighter = nullptr;
    _isGameOver = E_FAIL;
    _turnCount = 0;
}

GameGod::~GameGod()
{
    if (_winner != nullptr)
    {
        delete _winner;
        _winner = nullptr;
    }

    if (_allianceFighter != nullptr)
    {
        delete _allianceFighter;
        _allianceFighter = nullptr;
    }

    if (_hordeFighter != nullptr)
    {
        delete _hordeFighter;
        _hordeFighter = nullptr;
    }

    if (!_allianceFighters.empty())
    {
        for (int i = 0; _allianceFighters.size(); i++)
        {
            Character* charact;
            _allianceFighters.push_back(charact);
            delete charact;
            charact = nullptr;

        }
    }

    if (!_hordeFighters.empty())
    {
        for (int i = 0; _hordeFighters.size(); i++)
        {
            Character* charact;
            _hordeFighters.push_back(charact);
            delete charact;
            charact = nullptr;

        }
    }
}

HRESULT GameGod::LoadCharacterRessources(string fileName)
{
    json data = nullptr;

    try {
        ///Parser JSON
        std::ifstream f(fileName);
        data = json::parse(f);
    }
    catch (exception e)
    {
        PLOG_ERROR << "Parsing of Json Failed. Filename: " << fileName;
        throw e;
    }

    auto Characters = data["Character"];
    int nbCharacter = (int)Characters.size();


    /*********************************************CHARACTER CREATION***********************************************/

    for (int i = 0; i < nbCharacter; i++)
    {

        string name = Characters[i]["Name"];
        int pv = Characters[i]["pv"];

        Weapon* CharacterWeapon;
        Armor* CharacterArmor;

        /*********************************************SWORD CREATION***********************************************/
        if (!Characters[i]["MyWeapon"].empty())
        {
            string weapon = Characters[i]["MyWeapon"]["type"];


            if (weapon == "Sword")
            {
                CharacterWeapon = new Sword();
            }
            else if (weapon == "Hammer")
            {
                CharacterWeapon = new Hammer();
            }
            else
            {
                CharacterWeapon = new  BareHand();
            }
            CharacterWeapon->setDamage(Characters[i]["MyWeapon"]["damage"]);

            string weaponName = Characters[i]["MyWeapon"]["Name"];
            CharacterWeapon->SetName(weaponName);
        }
        else
        {
            CharacterWeapon = new Sword();
            CharacterWeapon->setDamage(0);
            CharacterWeapon->SetName("None");
        }
        /*********************************************ARMOR CREATION***********************************************/


        if (!Characters[i]["MyArmor"].empty())
        {
            string armor = Characters[i]["MyArmor"]["type"];

            if (armor == "Shield")
            {
                CharacterArmor = new Shield();
            }
            else if (armor == "MirrorArmor")
            {
                CharacterArmor = new MirrorArmor();
            }
            else
            {
                CharacterArmor = new Cloth();
            }
            CharacterArmor->setPvBonus(Characters[i]["MyArmor"]["pvBonus"]);
            string armorName = Characters[i]["MyArmor"]["Name"];
            CharacterArmor->SetName(armorName);
        }
        else
        {
            CharacterArmor = new Shield();
            CharacterArmor->setPvBonus(0);
            CharacterArmor->SetName("None");
        }


        int cdCapacity = Characters[i]["CdCapacity"];
        string nameCapacity = Characters[i]["NameCapacity"];

        Character* newCharacter = nullptr;

        string characterClass = Characters[i]["Class"];

        Image associateImg(Characters[i]["ImgSource"], Characters[i]["SizeImg"]["Height"], Characters[i]["SizeImg"]["Width"]);

        /*********************************************CLASS CREATION***********************************************/

        if (characterClass == "Orc")
        {
            newCharacter = new Orc(name, pv, CharacterWeapon, CharacterArmor, cdCapacity, nameCapacity, associateImg);

        }
        else if (characterClass == "Knight")
        {
            newCharacter = new Knigth(name, pv, CharacterWeapon, CharacterArmor, cdCapacity, nameCapacity, associateImg);

        }

        int ForceSide = Characters[i]["Alignement"];

        switch (ForceSide)
        {
        case 0:
            _hordeFighters.push_back((Knigth*)newCharacter); // Light Side
            break;

        case 1:
            _allianceFighters.push_back((Orc*)newCharacter); // Dark Side
            break;

        default:
            _allianceFighters.push_back((Knigth*)newCharacter); // Let's assume that we are all good is
            break;
        }

        delete newCharacter;
        delete CharacterWeapon;
        delete CharacterArmor;

        newCharacter = nullptr;
        CharacterWeapon = nullptr;
        CharacterArmor = nullptr;

    }

    return S_OK;
}

HRESULT GameGod::LauchSpecialCapacity(Character* allianceFighter, Character* hordeFighter)
{
    if (allianceFighter == nullptr || hordeFighter == nullptr)
    {
        AddTurnInfo("Error with Character. Check logfile\n");
        PLOG_ERROR << "One of the caracter is Null:" << " - Character allianceFighter: " << allianceFighter << " - Character hordeFighters:" << hordeFighter;
        return E_FAIL;
    }

    AddTurnInfo(allianceFighter->GetName() + " Launch Special Capacity");

    HRESULT result = allianceFighter->SpecialCapacityCheck(hordeFighter);

    if (result == E_FAIL)
    {
        return result;
    }

    std::list<string> characterlog = allianceFighter->GetLog();

    for (auto const& i : characterlog) {
        AddTurnInfo(i);
    }


    HRESULT isAPlayerDead = isAWinnerDecided(allianceFighter, hordeFighter);

    if (isAPlayerDead == S_FALSE)
    {
        AddTurnInfo(hordeFighter->GetName() + " Launch Special Capacity");

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


HRESULT GameGod::isAWinnerDecided(Character* allianceFighter, Character* hordeFighter)
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

HRESULT GameGod::ClassicFight(Character* allianceFighter, Character* hordeFighter)
{
    AddTurnInfo("Character " + allianceFighter->GetName() + " Attack normaly");

    allianceFighter->Attack(hordeFighter);

    std::list<string> characterlog = allianceFighter->GetLog();

    for (auto const& i : characterlog) {
        AddTurnInfo(i);
    }


    if (isAWinnerDecided(allianceFighter, hordeFighter) == S_FALSE)
    {
        AddTurnInfo("\nCharacter " + hordeFighter->GetName() + " Attack normaly");

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

void GameGod::CheckStatusEffectForPlayers(Character* allianceFighter, Character* hordeFighter)
{
    CheckStatusEffect(allianceFighter);
    CheckStatusEffect(hordeFighter);

}


void GameGod::CheckStatusEffect(Character* allianceFighter)
{
    CONDITION status = allianceFighter->getCharacterStatus();
    switch (status)
    {
    case STUN: allianceFighter->setCharacterStatus(NORMAL);
        AddTurnInfo("Character " + allianceFighter->GetName() + " Cured from STUN");
        break;

    case BURN: //TODO

    case FROZEN: //TODO

    case NORMAL:
        AddTurnInfo(allianceFighter->GetName() + " status is NORMAL");

    default:

        break;
    }


}

void GameGod::StartRetroBattle(Character* allianceFighter, Character* hordeFighter)
{
    _isGameOver = E_FAIL;
    _turnCount = 0;

    _retroUI.SetOpponent(allianceFighter->GetName(), hordeFighter->GetName());

    PLOG_INFO << "The battle Begin";
    while (_isGameOver != S_OK)
    {
        _isGameOver = NextTurn(allianceFighter, hordeFighter);
    }
}

void GameGod::StartModernBattle(Character* allianceFighter, Character* hordeFighter)
{
    _isGameOver = E_FAIL;
    _turnCount = 0;

    PLOG_INFO << "The battle Begin";

    _isGameOver = NextTurn(allianceFighter, hordeFighter);

}

HRESULT GameGod::NextTurn(Character* allianceFighter, Character* hordeFighter)
{

    resetTurnInfo();

    _turnCount = _turnCount + 1;
    PLOG_INFO << "Turn No" << _turnCount;
    _retroUI.SetTurnNumber(_turnCount);

    AddTurnInfo("\nSpecial Capacity Phase");
    _isGameOver = LauchSpecialCapacity(allianceFighter, hordeFighter);

    if (_isGameOver != S_OK)
    {
        AddTurnInfo("\nClassic Combat Phase");
        _isGameOver = ClassicFight(allianceFighter, hordeFighter);


        if (_isGameOver == S_FALSE)
        {
            AddTurnInfo("Check Condition of both players");
            CheckStatusEffectForPlayers(allianceFighter, hordeFighter);
        }
        else {
            _isGameOver = S_OK;
        }
    }

    AddTurnInfo("End Of Turn\n");
    _retroUI.SetPvOpponent(allianceFighter->GetPv(), hordeFighter->GetPv());
    _retroUI.displayUI();

    system("pause");

    return _isGameOver;
}


void GameGod::AddTurnInfo(string info)
{
    PLOG_INFO << info;
    _retroUI.AddTurnInfo(info);
}

void GameGod::resetTurnInfo()
{
    _retroUI.ResetTurnInfo();
}

void GameGod::RetroPlay()
{
    /******************CHOIX DE L'ADVERSAIRE************************/
    system("cls");
    cout << "Welcome to the Arena of Azeroth. Let's the fight between Aliance and horde Begin\n";

    cout << "Please Select alliance and horde Fighter!\n"
        << "Alliance Side: \n";
    DisplayNameFighter(_allianceFighters);

    int inputFighter = -1;

    cout << "\nYour Choice: ";
    inputFighter = SecureCinInput((int)_hordeFighters.size() - 1);

    cout << endl;
    Character* AllianceFighter = _allianceFighters[inputFighter];

    DisplayFighter(AllianceFighter);
    system("pause");

    system("cls");
    cout << "Welcome to the Arena of Azeroth. Let's the fight between Aliance and horde Begin\n";
    cout << "Horde Side: ";
    DisplayNameFighter(_hordeFighters);
    cout << "\nYour Choice: ";
    inputFighter = SecureCinInput((int)_hordeFighters.size() - 1);

    Character* HordeFighter = _hordeFighters[inputFighter];
    DisplayFighter(HordeFighter);

    cout << "Press Enter to Start the Battle";
    system("pause");

    StartRetroBattle(AllianceFighter, HordeFighter);

    resetTurnInfo();
    AddTurnInfo("The Game is Over.");
    AddTurnInfo("The Winner is " + GetWinner()->GetName());

    _retroUI.displayUI();
}

void GameGod::DisplayNameFighter(vector<Character*> Fighter)
{
    for (int i = 0; i < Fighter.size(); i++)
    {
        cout << Fighter[i]->GetName() << " - Enter " << i << endl;
    }
}

void GameGod::DisplayFighter(Character* Fighter)
{
    cout << "Fighter Selected: \n"
        << "Name: " << Fighter->GetName() << endl
        << "Pv: " << Fighter->GetPv().getPv() << "/" << Fighter->GetPv().getPv() << endl
        << "Capacity: " << Fighter->GetNameCapacity() << endl;
    if (Fighter->GetWeapon() != NULL)
    {
        cout << "Weapon: " << Fighter->GetWeapon()->GetName() << endl;
    }
    if (Fighter->GetArmor() != NULL)
    {
        cout << "Armor: " << Fighter->GetArmor()->GetName() << endl;
    }
    cout << endl;
}

int GameGod::SecureCinInput(int maxNumber)
{
    int inputFighter;
    cin >> inputFighter;
    while (std::cin.fail() || (inputFighter<0 || inputFighter>maxNumber))
    {
        std::cout << "\nNumber incorrect ! " << std::endl;
        std::cin.clear();
        std::cin.ignore(256, '\n');
        cout << "Your choice: ";
        std::cin >> inputFighter;
    }
    return inputFighter;
}



void GameGod::SetOpponent(Character* allianceFighters, Character* hordeFighters)
{
    _allianceFighter = allianceFighters;
    _hordeFighter = hordeFighters;
}

void GameGod::setWinner(Character* winner)
{
    PLOG_INFO << "We have allianceFighter winner ";

    _winner = winner;
}

Character* GameGod::GetWinner()
{
    return _winner;
}
