#include "CaroModel.h"

CaroModel::CaroModel()
{

}
CaroModel::~CaroModel()
{

}

int CaroModel::getCurrentTurn()
{
    return curGame.getCurrTurn();
}
void CaroModel::incTurn() // turn tang thi doi side
{
    curGame.setCurrTurn(getCurrentTurn() + 1);
}
void CaroModel::setNodeData(boardCell point) // point duoc truyen tu controller (lay tu view)
{

}
void CaroModel::putXtoNode(int n_row, int n_column)
{
    addDataSide(n_row, n_column, side_O);
}
void CaroModel::putOtoNode(int n_row, int n_column)
{
    addDataSide(n_row, n_column, side_X);
}
void CaroModel::addDataSide(int n_row, int n_column, sideXorO side)
{
    curGame.addData(n_row, n_column, side);
}


int CaroModel::getBoardSize()
{
    return curGame.getBoardSize();
}

int CaroModel::getBoardSizeByID(string gameid)
{
    return preGames[gameid].getBoardSize();
}

void CaroModel::setBoardSize(int boradSize)
{
    curGame.setBoardSize(boradSize);
}

void  CaroModel::setGameID(string game_id)
{
    curGame.setGameID(game_id);
}

void CaroModel::setPlayerName(string name1, string name2)
{
    curGame.addPlayerInfo(name1, name2);
}

bool CaroModel::checkEmptyCell(boardCell point)
{
    if (curGame.getNodeData(point) == side_empty)
    {
        return true;
    }
    return false;
}

bool CaroModel::checkWin()
{
    int boardSize = curGame.getBoardSize();
    boardCell point;
    vector<boardCell> cellX, cellO;
    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < boardSize; j++)
        {
            point = { i,j };
            if (curGame.getNodeData(point) == side_empty)
            {
                continue;
            }
            else if (curGame.getNodeData(point) == side_X)
            {
                cellX.push_back(point);
            }
            else
            {
                cellO.push_back(point);
            }
        }
    }
    if (cellX.size() <= 3 && cellO.size() <= 3)
    {
        return false;
    }
    // X win
    if (checkVertical(cellX) || checkHorizontal(cellX) || checkDiagonal(cellX) || checkRevertDiagonal(cellX))
    {
        curGame.setWinner(1);
        return true;
    }
    // O win
    if (checkVertical(cellO) || checkHorizontal(cellO) || checkDiagonal(cellO) || checkRevertDiagonal(cellO))
    {
        curGame.setWinner(0);
        return true;
    }
    // fair
    if (curGame.getCurrTurn() == boardSize * boardSize)
    {
        return true;
    }

    return false;
}

bool CaroModel::checkVertical( vector< boardCell> cells)
{
    for (int i = 0; i < cells.size()-1; i++)
    {
        int y = cells[i].y;
        int count = 1;
        for (int j = i+1; j < cells.size(); j++)
        {
            if ((cells[i].x == cells[j].x) && (cells[j].y == (y + 1)))
            {
                y++;
                count++;
                if (count == 4)
                {
                    return true;
                }
            }

        }
    }
    return false;
}
bool CaroModel::checkHorizontal(vector< boardCell> cells)
{
    for (int i = 0; i < cells.size()-1; i++)
    {
        int x = cells[i].x;
        int count = 1;
        for (int j = i + 1; j < cells.size(); j++)
        {
            if ((cells[i].y == cells[j].y) && (cells[j].x == (x + 1)))
            {
                x++;
                count++;
                if (count == 4)
                {
                    return true;
                }
            }

        }
    }
    return false;

}
bool CaroModel::checkDiagonal(vector< boardCell> cells)
{
    for (int i = 0; i < cells.size()-1; i++)
    {
        int x = cells[i].x;
        int y = cells[i].y;
        int count = 1;
        for (int j = i + 1; j < cells.size(); j++)
        {
            if ((cells[j].y == (y + 1)) && (cells[j].x == (x + 1)))
            {
                x++;
                y++;
                count++;
                if (count == 4)
                {
                    return true;
                }
            }

        }
    }
    return false;
}
bool CaroModel::checkRevertDiagonal(vector< boardCell> cells)
{
    for (int i = 0; i < cells.size()-1; i++)
    {
        int x = cells[i].x;
        int y = cells[i].y;
        int count = 1;
        for (int j = i + 1; j < cells.size(); j++)
        {
            if ((cells[j].y == (y - 1)) && (cells[j].x == (x + 1)))
            {
                x++;
                y--;
                count++;
                if (count == 4)
                {
                    return true;
                }
            }

        }
    }
}

void CaroModel::saveGame()
{
    string key = curGame.getGameID();
    Game game = curGame;
    preGames.insert({ key ,game });
    Game newGame;
    curGame = newGame;
}

void CaroModel::getScore(int& player1, int& player2)
{
    int score1 = 0, score2 = 0;
    curGame.getPlayersSore(score1, score2);
    player1 = score1;
    player2 = score2;
}

void CaroModel::getScoreByID(int& player1, int& player2, string gameID)
{
    int score1 = 0, score2 = 0;
    preGames[gameID].getPlayersSore(score1, score2);
    player1 = score1;
    player2 = score2;
}


void CaroModel::displayHistory()
{
    map<string, Game>::iterator it;
    for (it = preGames.begin(); it != preGames.end(); it++) {
        cout << "Game ID: "<< it->first.c_str() << endl;
        cout << "Players: " << endl;
        it->second.displayPlayerInfo();
    }
}


string CaroModel::getGameID()
{
    return curGame.getGameID();
}

vector<string> CaroModel::getNamePlayers(string gameID)
{
    vector<string> playernames;
    string player1=" ", player2=" ";
    
    preGames[gameID].getNamePlayers(player1, player2);
    playernames.push_back(player1);
    playernames.push_back(player2);
    return playernames;
}

vector<boardCell> CaroModel::getDataNodeByTurn(string gameID)
{
    vector<boardCell> cells;
    int turn = preGames[gameID].getCurrTurn();
    for (int j = 1; j <= turn; j++)
    {
        cells.push_back(preGames[gameID].getTurnNodeData(j));
    }
    return cells;
}


void CaroModel::saveData()
{
    string name1 = " ", name2 = " ";
    int score1 = 0, score2 = 0;
    int curTurn = 0;
    fstream database;
    database.open("CaroDatabase.ini", ios::app);

    curGame.getNamePlayers(name1, name2);
    curGame.getPlayersSore(score1, score2);
    curTurn = curGame.getCurrTurn();

    database << "Game ID: " << curGame.getGameID()<< "\n";
    database << "total turn: " << curTurn << "\n";
    database << "Player 1: " << "\n";
    database << "Name: " << name1 << "\n";
    database << "Score: " << score1 << "\n";
    database << "Player 2: " << "\n";
    database << "Name: " << name2 << "\n";
    database << "Score: " << score2 << "\n";
    database.close();
}



