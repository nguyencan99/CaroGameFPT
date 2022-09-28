#include "CaroView.h"
#include<Windows.h>

CaroView::CaroView()
{

}
CaroView::~CaroView()
{

}

// private functions
void CaroView::drawBoardLine( int lastRowNum) 
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 10);
    string noDataLine = "";
    for (int j = 0; j < lastRowNum-1; j++)
    {
            noDataLine += "+---";
    }
    noDataLine += "+---+";
    cout << noDataLine << "\n";
}

void CaroView::drawBoardCellRow( int lastRowNum)
{
    string boardRow = "";
    string s;

    for (int j = 0; j < lastRowNum; j++) 
    {
        boardRow += "|";
        s = " ";
        boardRow += " " + s + " ";            
    }
    cout << boardRow << "\n";

}


void CaroView::drawBoard(int sizeofBoard)
{
    for (int i = 0; i < (sizeofBoard); i++)
    {
        drawBoardLine(sizeofBoard);
        drawBoardCellRow(sizeofBoard + 1);
    }
    drawBoardLine(sizeofBoard);
}

void CaroView::putXO(COORD &point, std::string text)
{
    if (point.X % 4 == 1)
    {
        point.X = point.X + 1;
    }
    else if (point.X % 4 == 3)
    {
        point.X = point.X - 1;
    }
    else
    {
        point.X = point.X;
    }

    gotoxy(point.X, point.Y);

    if(text=="X")
    {
        setcolor(1);//blue
    }
    if (text == "O")
    {
        setcolor(4);//red
    }
    std::cout << text;
}

void CaroView::gotoxy(int x, int y) 
{
    COORD coord;
    coord.X = x; coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    return;
}


bool CaroView::disableBorderBorad(int boardSize, COORD border,const COORD startpoint)
{
    // ko nam trong board
    if ((border.X< startpoint.X) || (border.X> (startpoint.X+boardSize * 4))|| (border.Y < startpoint.Y) || (border.Y > (startpoint.Y + boardSize * 2)))
    {
        return false;
    }
    // nam tren border
    if ((border.X - startpoint.X) == 0 || (border.Y- startpoint.Y) == 0 || (border.Y - startpoint.Y )== (boardSize * 2) || (border.X - startpoint.X) == (boardSize * 4))
    {
        return false;
    }
    if ((border.X - startpoint.X) % 4 == 0|| (border.Y - startpoint.Y) % 2 == 0)
    {
        return false;
    }
    return true;
}

//cell thoa man đk disableBorderBorad
boardCell CaroView::convertCoorToBoardCell(COORD point, const COORD startpoint)
{
    boardCell cell;
    cell.x = (point.X - startpoint.X) / 4;
    cell.y = (point.Y - startpoint.Y) / 2;
    return cell;
}

COORD CaroView::convertBoardCellToCoor(boardCell cell, const COORD startpoint)
{
    COORD point;
    point.X = startpoint.X + (cell.x * 4 + 2);
    point.Y = startpoint.Y + (cell.y * 2 + 1);

    return point;
}


void CaroView::setcolor(WORD color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    return;
}

void CaroView::clearBoardArea(COORD topLeft)
{
    //COORD topLeft = { 0, 4 };
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen;
    DWORD written;

    GetConsoleScreenBufferInfo(console, &screen);
    FillConsoleOutputCharacterA(console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
    FillConsoleOutputAttribute( console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE, screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
    SetConsoleCursorPosition(console, topLeft);
}

void CaroView::viewUpdateScore(COORD& point, int player1Score, int player2Score)
{
    gotoxy(point.X, point.Y);
    cout << player1Score;

    gotoxy(point.X, point.Y+1);
    cout << player2Score;

}

COORD CaroView::mouse()
{
    INPUT_RECORD ir[128];
    DWORD        nRead;
    COORD        xy;
    HANDLE       hStdInput = NULL;
    HANDLE       hStdOutput = NULL;
    HANDLE       hEvent = NULL;
    hStdInput = GetStdHandle(STD_INPUT_HANDLE);
    hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    FlushConsoleInputBuffer(hStdInput);
    SetConsoleMode(hStdInput, ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
    hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
    HANDLE handles[2] = { hEvent, hStdInput };
    while (WaitForMultipleObjects(2, handles, FALSE, INFINITE)) 
    {
        ReadConsoleInput(hStdInput, ir, 128, &nRead);
        for (unsigned int i = 0; i < nRead; i++)
        {
            if (ir[i].EventType == MOUSE_EVENT)
            {
                if ((GetKeyState(VK_LBUTTON) & 0x8000) != 0)
                {
                    COORD coor_mouse;
                    coor_mouse.X = ir[i].Event.MouseEvent.dwMousePosition.X; //X là tọa độ ngang hoặc giá trị cột
                    coor_mouse.Y = ir[i].Event.MouseEvent.dwMousePosition.Y; //Y là tọa độ dọc hoặc giá trị hàng
                    return coor_mouse;
                }
            }
        }
    }
}

void CaroView::displayMenu()
{
    cout << " <NEW GAME> " << " <EXIT> " << " <HISTORY> " << " <REPLAY> " << endl;
}

void CaroView::displayName()
{
    gotoxy(0, 1);
    cout << "GAME ID:               ";
    gotoxy(0, 2);
    cout << "BOARD SIZE:               ";
    gotoxy(0, 3);
    cout << "PLAYER 1 <X>:                   " << "SCORE: ";
    gotoxy(0, 4);
    cout << "PLAYER 2 <O>:                   " << "SCORE: ";
}