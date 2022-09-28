#ifndef _CAROVIEW_H_
#define _CAROVIEW_H_

#include <iostream>
#include <windows.h>
#include<sstream>
#include<string>
#include"Library.h"

using namespace std;

#define ROWCOUNT 10
#define COLUMNCOUNT 10

class CaroView
{
private:
    void drawBoardLine(int lastRowNum);
    void drawBoardCellRow(int lastRowNum);
    
public:
    CaroView();
    virtual ~CaroView();
    //COORD CursorToBuffer();
    void putXO(COORD &point, std::string text);
    void gotoxy(int x, int y);
    //COORD getCursorPosition();
    void drawBoard(int sizeofBoard);
    bool disableBorderBorad(int boardSize, COORD border, COORD startpoint = { 0,0 });
    boardCell convertCoorToBoardCell(COORD point, const COORD startpoint = { 0,0 });
    COORD convertBoardCellToCoor(boardCell cell, const COORD startpoint = { 0,0 });
    void setcolor(WORD color);
    void clearBoardArea(COORD topLeft);
    void viewUpdateScore(COORD& point, int player1Score, int player2Score);
    COORD mouse();
    void displayMenu();
    void displayName();

};
#endif // !_CAROVIEW_H_
