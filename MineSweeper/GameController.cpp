// using GameController to input command to Commmand Handler
// then  let Command Handler to handle the command
// then let GameBoard to handle the command

#include "GameController.h"

void GameController::LoadPath(string path) 
{
	if (board->getBoardState() == GameBoardState::Idle) 
	{
		board->LoadBoardFile(path);
		cout << "< Success >\n";
	}
	else
	{
		cout << "< Failed >\n";
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
	if (board->getIsEnableGameInput()) 
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
		cout << "< Success >\n";
	}
}

void GameController::Print(string inst) 
{
	if (inst == "GameBoard") 
	{
		board->PrintBoardWithMask();
	}
	else if (inst == "GameState") 
	{
		//
		GameBoardState state = board->getBoardState();
		if (state == GameBoardState::Idle) 
		{
			cout << "Idle\n";
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
	else if (inst == "GameAnswer") 
	{
		board->PrintBoard();
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
		cout << "Failed\n";
	}
}

void GameController::LeftClick(int rol, int col) 
{
	if (board->getBoardState() == GameBoardState::Playing) 
	{
		board->RevealTile(rol, col);
		cout << "Success\n";
	}
	else 
	{
		cout << "Failed\n";
	}
}

void GameController::RightClick(int rol, int col) 
{
	if (board->getBoardState() == GameBoardState::Playing) 
	{
		board->FlagTile(rol, col);
		cout << "Success\n";
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
		exit(0);
	}
	else 
	{
		cout << "You can't quit now.";
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