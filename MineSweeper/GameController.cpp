// using GameController to input command to Commmand Handler
// then  let Command Handler to handle the command
// then let GameBoard to handle the command

#ifndef GAMECONTROLLER_CPP
#define GAMECONTROLLER_CPP

#include "GameController.h"

#endif // GAMECONTROLLER_CPP


void GameController::LoadPath(string path) 
{
	string outputString = "<Load BoardFile " + path + "> : ";
	*oStream << outputString ;
	
	if (board->getBoardState() == GameBoardState::Idle) 
	{
		bool allRight = board->LoadBoardFile(path);
		
		if (allRight)
		{
			*oStream << "Success\n";
		}
		else
		{
			*oStream << "Failed\n";
		}
	}
	else
	{
		*oStream << "Failed\n";
	}
	
}

void GameController::LoadRate(int m, int n, float rate) 
{
	string outputString = "<Load RandomRate " + to_string(rate) + "> : ";
	*oStream << outputString;
	
	if (board->getBoardState() == GameBoardState::Idle) 
	{
		board->LoadRandomCountMine(m, n, rate);
		*oStream << "Success\n";
	}
	else 
	{
		*oStream << "Failed\n";
	}
}

void GameController::LoadCount(int m, int n, int c) 
{
	string outputString = "<Load RandomCount " + to_string(c) + "> : ";
	*oStream << outputString;
	
	if (board->getBoardState() == GameBoardState::Idle) 
	{
		board->LoadRandomGenerateMine(m, n, c);
		*oStream << "Success\n";
	}
	else
	{
		*oStream << "Failed\n";
	}
}

void GameController::StartGame() 
{
	if (board->getIsEnableGameInput() == false)
	{
		//*oStream << "©|¥¼¸ü¤J½L­±\n";
		*oStream << "<StartGame> : Failed\n";
	}
	else if (board->getBoardState() != GameBoardState::Idle) 
	{
		*oStream << "<StartGame> : Failed\n";
	}
	else 
	{
		board->StartGame();
		*oStream << "<StartGame> : Success\n";
	}
}

void GameController::Print(string inst) 
{
	if (inst == "GameBoard") 
	{
		*oStream << "<Print GameBoard> : \n";
		board->PrintBoardWithMask();
	}
	else if (inst == "GameAnswer") 
	{
		*oStream << "<Print GameAnswer> : \n";
		board->PrintBoard();
	}
	else if (inst == "GameState") 
	{
		*oStream << "<Print GameState> : ";
		
		//
		GameBoardState state = board->getBoardState();
		if (state == GameBoardState::Idle) 
		{
			*oStream << "Standby\n";
		}
		else if (state == GameBoardState::Playing) 
		{
			*oStream << "Playing\n";
		}
		else if (state == GameBoardState::End) 
		{
			*oStream << "GameOver\n";
		}
	}
	else if (inst == "BombCount") 
	{
		*oStream << "<Print BombCount> : ";
		*oStream << board->getMineCount() << '\n';
	}
	else if (inst == "FlagCount") 
	{
		*oStream << "<Print FlagCount> : ";
		*oStream << board->getFlagCount() << '\n';
	}
	else if (inst == "OpenBlankCount") 
	{
		*oStream << "<Print OpenBlankCount> : ";
		*oStream << board->getOpenedTileCount() << '\n';
	}
	else if (inst == "RemainBlankCount") 
	{
		*oStream << "<Print RemainBlankCount> : ";
		*oStream << board->getRemainClosedTileCount() << '\n';
	}
	else 
	{
		*oStream << "Failed\n";
	}
}

void GameController::LeftClick(int rol, int col) 
{
	string outputString = "<LeftClick " + to_string(rol) + " " + to_string(col) + "> : ";
	*oStream << outputString;
	
	if (board->getBoardState() == GameBoardState::Playing) 
	{
		bool allRight = board->RevealTile(rol, col);
		
		if (allRight)
		{
			*oStream << "Success\n";
		}
		else
		{
			*oStream << "Failed\n";
		}
		
		board->CheckGame();
	}
	else 
	{
		*oStream << "Failed\n";
	}
}

void GameController::RightClick(int rol, int col) 
{
	string outputString = "<RightClick " + to_string(rol) + " " + to_string(col) + "> : ";
	*oStream << outputString;
	
	if (board->getBoardState() == GameBoardState::Playing) 
	{
		bool allRight = board->FlagTile(rol, col);

		if (allRight)
		{
			*oStream << "Success\n";
		}
		else
		{
			*oStream << "Failed\n";
		}
	}
	else 
	{
		*oStream << "Failed\n";
	}
}

void GameController::Replay() 
{
	if (board->getBoardState() == GameBoardState::End) 
	{
		board = new GameBoard(((ofstream*)oStream));
		*oStream << "<Replay> : Success\n";
	}
	else
	{
		*oStream << "<Replay> : Failed\n";
	}
}

void GameController::Quit() 
{
	if (board->getBoardState() == GameBoardState::End) 
	{
		*oStream << "<Quit> : Success\n";
		exit(0);
	}
	else 
	{
		*oStream << "<Quit> : Failed\n";
	}
}
