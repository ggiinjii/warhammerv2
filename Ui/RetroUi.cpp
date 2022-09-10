﻿#include "RetroUi.h"
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
        << "Name: " << _nameOrc << "                       Name: " << _nameKnight << endl
        << "PV: " << _pvOrc.getPv() << "/" << _pvOrc.getPvMax() << "                              PV: " << _pvKnight.getPv() << "/" << _pvKnight.getPvMax() << endl << endl
        << "Battle Log: " << endl;
    DisplayTurnInformation();

}

void RetroUi::SetPvOpponent(Pv goodGuyPv, Pv badGuyPV  )
{
    _pvOrc = badGuyPV;
    _pvKnight = goodGuyPv;

}

void RetroUi::SetOpponent(string knightName, string orcName)
{
    _nameOrc = orcName;
    _nameKnight = knightName;
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
