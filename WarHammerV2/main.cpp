#include <iostream>
#include "stdio.h"
#include "Inventory/Weapon/SubWeapon/Sword.h"
#include "Inventory/Weapon/SubWeapon/Hammer.h"
#include "Character/Alliance/Knigth.h"
#include "Character/Horde/Orc.h"
#include "GameObject/GameGod.h"
#include "plog/Log.h"
#include "plog/Initializers/RollingFileInitializer.h"
#include <chrono>
#include<ctime>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <windows.h>


std::string datetime()
{
    char buffer[80];
    struct tm newtime;
    time_t now = time(0);
    localtime_s(&newtime, &now);

    strftime(buffer, 80, "%d-%m-%Y %H-%M-%S", &newtime);
    return std::string(buffer);
}

int main(int, char**)
{

    // Set console code page to UTF-8 so console known how to interpret string data
    SetConsoleOutputCP(CP_UTF8);

    // Enable buffering to prevent VS from chopping up UTF-8 byte sequences
    setvbuf(stdout, nullptr, _IOFBF, 1000);

    GameGod Kimimaro; // creation of the singleton Which Overwatch the game (

    /********Initialisation LogFile*************/
    string filename = "../Log/logCombat" + datetime() + ".txt";
    plog::init(plog::debug, filename.c_str()); // Step2: initialize the logger

    
    TCHAR buffer[MAX_PATH] = { 0 };
    GetModuleFileName(NULL, buffer, MAX_PATH);

    // Load Character Ressources

    HRESULT isLoadingCorrect = Kimimaro.LoadCharacterRessources("..\\Ressources\\Orc.json");
    //Stuff Creation
    Shield* SolarShield = new Shield(50);
    Sword* LunarSword = new Sword(5);
    Hammer* DoomHammer = new Hammer(8);

    Image imgVide;

    //Character Creation
    Knigth* Billy = new Knigth("Billy2", 20, LunarSword, SolarShield, 3, "Charge", imgVide);
    Orc* Thrall = new Orc("Thrall2", 60, DoomHammer, nullptr, 5, "Stun", imgVide);

    Kimimaro.SetOpponent(Billy, Thrall); // Setup for RetroUi

    int displayChoice = 0;

    while (displayChoice != 1 && displayChoice != 2)
    {
        system("cls");
        cout << "Voulez vous lancer l'affichage Retro ou l'affichage Moderne ?" << endl
            << "Affichage Retro : 1" << endl
            << "Affichage Moderne: 2" << endl
            << "Votre choix: ";
        cin >> displayChoice;
        if (displayChoice == 1)
        {
            Kimimaro.RetroPlay(Billy, Thrall);
            break;
        }
        else if (displayChoice == 2)
        {
            ModernUi modernUi;              
            modernUi.setFighter(Kimimaro.GetGoodGuy(), Kimimaro.GetBadGuy());
            modernUi.displayModernUi();

           break;
        }
        else
        {
            cout << "Choix Incorrect" << endl;
            system("pause");
        }
    }

    return 0;
}
