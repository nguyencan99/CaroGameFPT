#include "Game.h"

node::node()
{
    side = side_empty;
    point = { -1,-1 };
    turn = 0;
}
node::~node()
{
}
void node::setSide(sideXorO n_side)
{
    side = n_side;
}
sideXorO node::getSide()
{
    return side;
}
void node::setCoordinate(boardCell n_point)
{
    point = n_point;
}
boardCell node::getCoordinate()
{
    return point;
}
void node::setTurn(int n_turn)
{
    turn = n_turn;
}
int node::getTurn()
{
    return turn;
}


Game::Game()
{
}

Game::~Game()
{
}

void Game::setGameID(string gameid)
{
    gameID = gameid;
}
string Game::getGameID()
{
    return gameID;
}
void Game::setCurrTurn(int cturn)
{
    currTurn = cturn;
}
int Game::getCurrTurn()
{
    return currTurn;
}
void Game::setBoardSize(int bSize)
{
    boardSize = bSize;
    initialDataNode();
}
int Game::getBoardSize()
{
    return boardSize;
}
void Game::addData(int n_row, int n_column, sideXorO side)
{
    dataSide.at(n_row).at(n_column).setTurn(currTurn);
    dataSide.at(n_row).at(n_column).setSide(side);
    boardCell boardCell;
    boardCell.x = n_row;
    boardCell.y = n_column;
    dataSide.at(n_row).at(n_column).setCoordinate(boardCell);
}
void Game::addPlayerInfo(string name1, string name2)
{
    player player1, player2;
    player1.setName(name1);
    players.push_back(player1);

    player2.setName(name2);
    players.push_back(player2);
}

sideXorO Game::getNodeData(boardCell cell)
{
    return dataSide[cell.x][cell.y].getSide();
}

boardCell Game::getTurnNodeData(int n_turn)
{
    boardCell cell;
    for (int i = 0; i < dataSide.size(); i++)
    {
        for (int j = 0; j < dataSide.size(); j++)
        {
            if (dataSide[i][j].getTurn() == n_turn)
            {
                cell = dataSide[i][j].getCoordinate();
                return cell;
            }
        }
    }
}

void Game::initialDataNode()
{
    for (int i = 0; i < boardSize; i++)
    {
        vector<node> v_temp;
        for (int j = 0; j < boardSize; j++)
        {
            node n_node;
            boardCell n_point = { i, j };
            n_node.setCoordinate(n_point);
            n_node.setSide(side_empty);
            v_temp.push_back(n_node);
        }
        dataSide.push_back(v_temp);
    }
}

void  Game::initialPlayer()
{
    for (int i = 0; i < 2; i++)
    {
        player player;
        players.push_back(player);
    }
}

void Game::setWinner(int winner)
{
    if (winner == 0 || winner == 1)
    {
        players[winner].setWinGame();
    }
}

void Game::getPlayersSore(int& score1, int& score2)
{
    score1 = players[0].getWinGame();
    score2= players[1].getWinGame();
}

void Game::displayPlayerInfo()
{
    for (int i = 0; i < 2; i++)
    {
        players[i].displayPlayerInfo();
    }
}

void Game::getNamePlayers(string& name1, string& name2)
{
    name1 = players[0].getname();
    name2 = players[1].getname();
}

