#include<iostream>
#include<string>
#include"CaroView.h"
#include"Controller.h"

using namespace std;
//struct point
//{
//    int x;
//    int y;
//};

int main()
{
    Controller carogame;
    //cout << " <START GAME> " << " <EXIT> " << " <HISTORY> " << " <REPLAY> " << endl;
    carogame.runProgram();
    //carogame.PlayGame();
    
    //carogame.setSizeBoard();
 /*   CaroView view;
    COORD A = view.mouse();
    cout << A.X << " " << A.Y;*/

 //   view.drawBoard(10);
 //   //while (1) {
 //   //    COORD cursor = view.CursorToBuffer();
 //   //    int x = cursor.X;
 //   //    int y = cursor.Y;
 //   //    view.putXO(x, y, "X");
 //   //}

 ////   view.putXO("X");
 //  // cout << "X";
    return 0;
}