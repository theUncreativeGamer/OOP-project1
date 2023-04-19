// using GameController to input command to Commmand Handler
// then  let Command Handler to handle the command
// then let GameBoard to handle the command

#include "GameController.h"

void GameController::LoadPath(string path) 
{
	string outputString = "<Load BoardFile " + path + "> : ";
	cout << outputString ;
	
	if (board->getBoardState() == GameBoardState::Idle) 
	{
		bool allRight = board->LoadBoardFile(path);
		//cout << "Success\n";
		if (allRight)
		{
			cout << "Success\n";
		}
		else
		{
			cout << "Failed\n";
		}
	}
	else
	{
		cout << "Failed\n";
	}
}

void GameController::LoadRate(int m, int n, float rate) 
{
	
	if (board->getBoardState() == GameBoardState::Idle) 
	{
		board->LoadRandomGenerateMine(m, n, rate);
		cout << "< Success >\n";
	}
	else 
	{
		cout << "< Failed >\n";
	}
}

void GameController::LoadCount(int m, int n, int c) 
{
	if (board->getBoardState() == GameBoardState::Idle) 
	{
		board->LoadRandomCountMine(m, n, c);
		cout << "< Success >\n";
	}
	else
	{
		cout << "< Failed >\n";
	}
}

void GameController::StartGame() 
{
	if (board->getIsEnableGameInput() == false)
	{
		cout << "©|¥¼¸ü¤J½L­±\n";
	}
	else if (board->getBoardState() != GameBoardState::Idle) 
	{
		cout << "< Failed >\n";
	}
	else 
	{
		board->StartGame();
		cout << "<StartGame> : Success\n";
	}
}

void GameController::Print(string inst) 
{
	if (inst == "GameBoard") 
	{
		cout << "<Print GameBoard> : \n";
		board->PrintBoardWithMask();
	}
	else if (inst == "GameAnswer") 
	{
		cout << "<Print GameAnswer> : \n";
		board->PrintBoard();
	}
	else if (inst == "GameState") 
	{
		cout << "<Print GameState> : ";
		
		//
		GameBoardState state = board->getBoardState();
		if (state == GameBoardState::Idle) 
		{
			cout << "Standby\n";
		}
		else if (state == GameBoardState::Playing) 
		{
			cout << "Playing\n";
		}
		else if (state == GameBoardState::End) 
		{
			cout << "GameOver";
		}
	}
	else if (inst == "BombCount") 
	{
		cout << board->getMineCount() << '\n';
	}
	else if (inst == "FlagCount") 
	{
		cout << board->getFlagCount() << '\n';
	}
	else if (inst == "OpenBlankCount") 
	{
		cout << board->getOpenedTileCount() << '\n';
	}
	else if (inst == "RemainBlankCount") 
	{
		cout << board->getRemainClosedTileCount() << '\n';
	}
	else 
	{
		////debug snnippet fragment
		////print all counts in board
		//cout << "BombCount: " << board->getMineCount() << '\n';
		//cout << "FlagCount: " << board->getFlagCount() << '\n';
		//cout << "OpenBlankCount: " << board->getOpenedTileCount() << '\n';
		//cout << "RemainBlankCount: " << board->getRemainClosedTileCount() << '\n';
		////debug snnippet fragment

		cout << "Failed\n";
	}
}

void GameController::LeftClick(int rol, int col) 
{
	// <LeftClick 5 1> :
	string outputString = "<LeftClick " + to_string(rol) + " " + to_string(col) + "> : ";
	cout << outputString;
	
	if (board->getBoardState() == GameBoardState::Playing) 
	{
		bool allRight = board->RevealTile(rol, col);
		//cout << "Success\n";
		if (allRight)
		{
			cout << "Success\n";
		}
		else
		{
			cout << "Failed\n";
		}
	}
	else 
	{
		cout << "Failed\n";
	}
}

void GameController::RightClick(int rol, int col) 
{
	// <RightClick 5 1> :
	string outputString = "<RightClick " + to_string(rol) + " " + to_string(col) + "> : ";
	cout << outputString;
	
	if (board->getBoardState() == GameBoardState::Playing) 
	{
		bool allRight = board->FlagTile(rol, col);
		//cout << "Success\n";
		if (allRight)
		{
			cout << "Success\n";
		}
		else
		{
			cout << "Fail\n";
		}
	}
	else 
	{
		cout << "Failed\n";
	}
}

void GameController::Replay() 
{
	if (board->getBoardState() == GameBoardState::End) 
	{
		board = new GameBoard();
		cout << "Success\n";
	}
	else
	{
		cout << "Failed\n";
	}
}

void GameController::Quit() 
{
	if (board->getBoardState() == GameBoardState::End) 
	{
		cout << "<Quit> : Success\n";
		exit(0);
	}
	else 
	{
		cout << "You can't quit now.\n";
	}
}

// command handler: handle the command with situation can be executed or not, if not , throw a error message

// operation events
// rightclick, with parameters x and y
	// binding functions
		// set flag, set question mark, set nothing accirding to the current state

// leftclick
	// binding functions
		// if it is a mine, game over
		// if it is not a mine, show the number of mines around it
		// if it is a blank, show the blank, and show the number of mines around it

// replay: reset the game state, and reramdomize the plane if with parameters