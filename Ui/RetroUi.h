#pragma once
#include <string>
#include <list>
#include <iostream>
#include "Tool/Pv.h"

using namespace std;
class RetroUi
{
private:
	int _turnNumber;

	std::list<string> _turnInformation;

    Pv _hordeFighterPv;
    Pv _allianceFighterPv;
	string _nameOrc;
	string _nameKnight;


public:
	RetroUi();
	~RetroUi();
	void displayUI();

	std::list<string> getTurnInfo();

	void DisplayTurnInformation();

	void AddTurnInfo(string turnInfo);

	void SetTurnNumber(int number);
	int GetTurnNumber();

	void ResetTurnInfo();

	void SetPvOpponent(Pv goodGuyPv, Pv badGuyPV);

	void SetOpponent(string knightName, string orcName);

};

