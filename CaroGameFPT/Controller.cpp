#include"Controller.h"

Controller::Controller()
{}

Controller::Controller(CaroModel& Model, CaroView& View)
{
	caroModel = Model;
	caroView = View;
}
Controller::~Controller()
{

}

void Controller::viewDisplayTable(int sizeOfBoard) // goi xuong view
{
    caroView.drawBoard(sizeOfBoard);
}
//void Controller::viewDisplayMenu()  // nhap thong tin nguoi choi, chon side
//{
//    cout << "============================================" << endl;
//    cout << "__________________CARO GAME_________________" << endl;
//    cout << "1. Start game" << endl;
//    cout << "2. View history" << endl;
//
//}

void Controller::setSizeBoard()
{
    int boardSize=0;
    cout << "Enter the size of board: ";
    cin >> boardSize;
	caroModel.setBoardSize(boardSize);
}

int Controller::getSizeBoard()
{
    return caroModel.getBoardSize();
}


void Controller::StartGame()
{
	COORD topleft = { 0,5 };
	caroView.clearBoardArea(topleft);

	caroView.gotoxy(40, 3);
	cout << "  ";
	caroView.gotoxy(40, 4);
	cout << "  ";
	caroView.displayName();
	int boardSize;
	string gameID;
	caroView.gotoxy(9, 1);
	cin >> gameID;
	caroModel.setGameID(gameID);

	caroView.gotoxy(12, 2);
	cin >> boardSize;
	caroModel.setBoardSize(boardSize);

	string nickName1, nickName2;
	caroView.gotoxy(16, 3);
	cin >> nickName1;
	caroView.gotoxy(16, 4);
	cin >> nickName2;
	caroModel.setPlayerName(nickName1, nickName2);

	//PlayGame();
	//Display board
	caroView.gotoxy(0, 5);
	viewDisplayTable(boardSize);
	caroView.setcolor(15);

}
void  Controller::runProgram()
{
	bool intoGameFlag = false;
	caroView.displayMenu();
	while (true)
	{
		COORD coor_mouse = caroView.mouse();
		if (coor_mouse.Y == 0 && (coor_mouse.X > 0 && coor_mouse.X < 11))
		{
			StartGame();
			intoGameFlag = true;
		}
		// <EXIT>
		else if (coor_mouse.Y == 0 && (coor_mouse.X > 12 && coor_mouse.X < 19))
		{
			saveGame();
			caroModel.saveData();
			//COORD  topleft = { 0,1 };
			//caroView.clearBoardArea(topleft);// clear screen
			//caroView.gotoxy(0, 5);
			return;
			// clear man hinh
			// tro ve man hinh chinh
		}
		//<HISTORY>
		else if (coor_mouse.Y == 0 && (coor_mouse.X > 21 && coor_mouse.X < 30))
		{
			COORD  topleft = { 0,1 };
			caroView.clearBoardArea(topleft);// clear screen
			caroView.gotoxy(0, 5);
			caroModel.displayHistory();
		}
		//<REPLAY>
		else if (coor_mouse.Y == 0 && (coor_mouse.X > 32 && coor_mouse.X < 40))
		{
			COORD  topleft = { 0,5 };
			caroView.clearBoardArea(topleft);// clear screen
			caroView.gotoxy(0, 5);
			replayGame();
			// chon game muon replay
			// draw the replay board
		}
		if (intoGameFlag)
		{
			PlayGame(coor_mouse);
		}
	}
}
void  Controller::PlayGame(COORD coor_mouse)
{
	bool winFlag = false;

	if (caroView.disableBorderBorad(getSizeBoard(), coor_mouse, { 0,5 })) // if cursor get the coord of the border then ignore 
	{
		boardCell cell = caroView.convertCoorToBoardCell(coor_mouse, { 0,5 }); // convert to board cell to check empty
		if (caroModel.checkEmptyCell(cell))
		{
			int turn = caroModel.getCurrentTurn();
			if (turn % 2 == 0)
			{
				caroView.putXO(coor_mouse, "X");
				caroModel.addDataSide(cell.x, cell.y, side_X);
			}
			else
			{
				caroView.putXO(coor_mouse, "O");
				caroModel.addDataSide(cell.x, cell.y, side_O);
			}
		}
		if (caroModel.checkWin())
		{
			winFlag = true;
			caroView.setcolor(15);
			int player1Score, player2Score;
			player1Score = player2Score = 0;
			caroModel.getScore(player1Score, player2Score);
			COORD point = { 40 , 3 };
			caroView.viewUpdateScore(point, player1Score, player2Score);
			saveGame();
			//goto
			// clear screen -> tro ve man hinh chinh
			return;
		}
		if (!winFlag)
		{
			caroModel.incTurn();
		}
	}

}

void Controller::saveGame()
{
	caroModel.saveData();
	caroModel.saveGame();
}
//void runProgram();
//bool checkGame();
//void replayGame();

bool Controller::MtoVCoordConvert()
{
	return true;
}
//bool Controller::VtoMCoordConvert()
//{
//    //caroView.convertCoorToBoardCell()
//	return true;
//
//}

void Controller::replayGame()
{
	COORD starting_point = { 0,5 };
	caroView.displayName();
	int boardSize;
	string GameID;
	string nickName1, nickName2;


	caroView.gotoxy(9, 1);
	cin >> GameID;

	caroView.gotoxy(12, 2);
	boardSize = caroModel.getBoardSizeByID(GameID);
	cout << boardSize;
	
	vector<string> playernames;
	playernames = caroModel.getNamePlayers(GameID);
	caroView.gotoxy(16, 3);
	cout << playernames[0];
	caroView.gotoxy(16, 4);
	cout << playernames[1];

	caroView.gotoxy(0, 5);
	viewDisplayTable(boardSize);

	caroView.setcolor(15);

	vector<boardCell> cells;
	cells = caroModel.getDataNodeByTurn(GameID);
	for (int i = 0; i < cells.size(); i++)
	{
		COORD point;
		point = caroView.convertBoardCellToCoor(cells[i], starting_point);
		if (i % 2 == 0)
		{
			caroView.putXO(point, "O");
		}
		else
		{
			caroView.putXO(point, "X");
		}
		Sleep(500);
	}
	caroView.setcolor(15);

	int player1Score, player2Score;
	player1Score = player2Score = 0;
	caroModel.getScoreByID(player1Score, player2Score, GameID);
	COORD point = { 40 , 3 };
	caroView.viewUpdateScore(point, player1Score, player2Score);
}

