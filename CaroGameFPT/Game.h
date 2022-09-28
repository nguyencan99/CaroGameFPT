#ifndef _GAME_H_
#define _GAME_H_

#include<iostream>
#include<string>
#include<vector>
#include"player.h"
#include"Library.h"

using namespace std;



class node
{
private:
    sideXorO side;
    boardCell point;
    int turn;
public:
    node();
    ~node();
    void setSide(sideXorO side);
    sideXorO getSide();
    void setCoordinate(boardCell point);
    boardCell getCoordinate();
    void setTurn(int n_turn);
    int getTurn();

};

class Game
{
private:
    string gameID;
    int currTurn;
    int boardSize;
    vector<vector<node>> dataSide;// luu cac nuoc di cua 1 van choi
    vector<player> players; // luu thong tin cua 2 ng choi cua van choi
public:
    Game();
    ~Game();
    void setGameID(string gameid);
    string getGameID();
    void setCurrTurn(int cturn);
    int getCurrTurn();
    void setBoardSize(int bSize);
    int getBoardSize();
    sideXorO getNodeData(boardCell cell);
    void setWinner(int winner);
    void getPlayersSore(int& score1, int& score2);
    void getNamePlayers(string& name1, string& name2);
    boardCell getTurnNodeData(int i);

    void initialDataNode();
    void initialPlayer();
    void addData(int n_row, int n_column, sideXorO side);
    void addPlayerInfo(string name1, string name2);
    void displayPlayerInfo();

};
#endif // !_GAME_H_



