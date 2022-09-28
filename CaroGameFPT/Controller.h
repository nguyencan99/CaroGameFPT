#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include "CaroModel.h"
#include "CaroView.h"

#include <iostream>
#include <string>

using namespace std;

class Controller
{
public:

    CaroModel caroModel;
    CaroView caroView;


    Controller();
    Controller(CaroModel& ticTacModel, CaroView& ticTacView);
    ~Controller();

    void viewDisplayTable(int sizeOfBoard); // goi xuong view
    //void viewDisplayMenu();  // nhap thong tin nguoi choi, chon side
    void setSizeBoard();
    int getSizeBoard();

    void StartGame();
    void PlayGame(COORD coor_mouse);
    void saveGame();
    void runProgram();
    //bool checkGame();
    void replayGame();

    bool MtoVCoordConvert();
    //bool VtoMCoordConvert();
    bool checkVertical();
    bool checkHorizontal();
    bool checkDiagonal();
    bool checkRevertDiagonal();

};

#endif /* CONTROLLER_H */

