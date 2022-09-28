#ifndef _PLAYER_H_
#define _PLAYER_H_
#include<iostream>
#include<string>

using namespace std;

class player
{
public:
    player();
    ~player();
    void setName(string name);
    string getname();
    void setWinGame();
    int getWinGame();
    void setPlayerInfor();
    void displayPlayerInfo();

private:
    string playerName;
    int score;
};
#endif // !_PLAYER_H_


