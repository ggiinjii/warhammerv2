#include "RetroUi.h"
#include <iostream>

using namespace std;

RetroUi::RetroUi()
{
    _turnNumber = 0;

}

RetroUi::~RetroUi()
{
}

void RetroUi::displayUI()
{
    system("cls");

    cout << "|--------------------Turn N " << GetTurnNumber() << "------------------------------" << endl
        << "|                              ||                         |" << endl
        << "|       .-\"\"\"\".                ||                         |" << endl
        << "|       /       \\              ||                  /      |" << endl
        << "|   __ /   .-.  .\\             ||           ,~~   /       |" << endl
        << "|  /  `\\  /   \\/  \\            ||       _  <=)  _/_       |" << endl
        << "|  |  _ \\/   .==.==.           ||       /I\\.=\"==.{>       |" << endl
        << "|  | (   \\  /____\\__\\          ||        \\I/-\\T/-'        |" << endl
        << "|   \\ \\      (_()(_()          ||          /_\\            |" << endl
        << "|    \\ \\            '---._     ||         // \\_           |" << endl
        << "|     \\                   \\_   ||        _I    /          |" << endl
        << "|  /\\ |`       (__)________/   ||                         |" << endl
        << "|  /  \\|     /\\___/            ||                         |" << endl
        << "| |    \\      \\ || VV          ||                         |" << endl
        << "| |     \\     \\|\"\"\"\",          ||                         |" << endl
        << "| |      \\     ______)         ||                         |" << endl
        << "| |       \\  /`                ||                         |" << endl
        << "|          \\(                  ||                         |" << endl
        << " --------------------------------------------------------- " << endl
        << "Name: " << _nameHordeFighter << "                       Name: " << _nameAllianceFighter << endl
        << "PV: " << _hordeFighterPv.getPv() << "/" << _hordeFighterPv.getPvMax() << "                              PV: " << _allianceFighterPv.getPv() << "/" << _allianceFighterPv.getPvMax() << endl << endl
        << "Battle Log: " << endl;
    DisplayTurnInformation();

}

void RetroUi::SetPvOpponent(Pv AllianceFighterPv, Pv HordeFighterPV  )
{
    _hordeFighterPv = HordeFighterPV;
    _allianceFighterPv = AllianceFighterPv;

}

void RetroUi::SetOpponent(string AllianceFighterName, string HordeFighterName)
{
    _nameHordeFighter = HordeFighterName;
    _nameAllianceFighter = AllianceFighterName;
};

std::list<string> RetroUi::getTurnInfo()
{
    return _turnInformation;
}

void RetroUi::DisplayTurnInformation()
{
    string turnInfo = "";

    for (auto const& i : _turnInformation) {
        std::cout << i << std::endl;
    }

}

void RetroUi::AddTurnInfo(string turnInfo)
{
    _turnInformation.push_back(turnInfo);
}

void RetroUi::SetTurnNumber(int number)
{
    _turnNumber = number;
}
int RetroUi::GetTurnNumber()
{
    return _turnNumber;
}

void RetroUi::ResetTurnInfo()
{
    _turnInformation.clear();
}
