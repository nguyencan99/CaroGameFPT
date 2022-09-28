#include "player.h"

// definition class player
player::player()
{
    playerName = " ";
    score = 0;
}

player::~player()
{
}
void player::setName(string name)
{
    playerName = name;
}
string player::getname()
{
    return playerName;
}

void player::setWinGame()
{
    score ++;
}
int player::getWinGame()
{
    return score;
}

void player::setPlayerInfor()
{
    cin.ignore();
    cout << "Enter name: ";
    getline(cin, playerName);
}

void player::displayPlayerInfo()
{
    cout << "Name: " << playerName  << endl;
    cout << "Score"  << score       << endl;
}
