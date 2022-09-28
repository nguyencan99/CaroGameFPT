#ifndef _CAROMODEL_H_
#define _CAROMODEL_H_
#include<iostream>
#include<string>
#include<vector>
#include<map>
#include"Game.h"
#include"player.h"
#include"Game.h"
#include <fstream>  


using namespace std;


class CaroModel
{
private:
    Game curGame;
    map<string, Game> preGames;
public:
    CaroModel();
    ~CaroModel();

    int getCurrentTurn();
    void incTurn(); // turn tang thi doi side
    void setNodeData(boardCell point);// point duoc truyen tu controller (lay tu view)
    void putXtoNode(int n_row, int n_column);
    void putOtoNode(int n_row, int n_column);
    void addDataSide(int n_row, int n_column, sideXorO side);
    int getBoardSize();
    int getBoardSizeByID(string gameid);
    void getScore(int &player1, int &player2);
    void getScoreByID(int& player1, int& player2, string gameID);
    void setBoardSize(int boradSize);
    void setGameID(string game_id);
    void setPlayerName(string name1, string name2);
    string getGameID();
    vector<string> getNamePlayers(string gameID);
    vector<boardCell> getDataNodeByTurn(string gameID);


    bool checkEmptyCell(boardCell point);
    bool checkWin();
    bool checkVertical(vector< boardCell> cells);
    bool checkHorizontal(vector< boardCell> cells);
    bool checkDiagonal(vector< boardCell> cells);
    bool checkRevertDiagonal(vector< boardCell> cells);
    void saveGame();
    void displayHistory();

    void saveData();
    
    //char* getBoardStatusCopy(char* boardLayoutCopy);
    //bool isPlayerMoveValid(int cellNumber);

    //bool isFull();
    //char getBoardStatus(int index);
    //void recordMove(int cellIndex, char playerID);
    //char checkWinner();
    //void startGame();

    //void setStarter(char userStarter);
    //bool getNextMove();
    //void changeNextMove();

    //string getFreeBoardCellsNumbers();
};


#endif // !_CAROMODEL_H_


