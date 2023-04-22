// using GameController to input command to Commmand Handler
// then  let Command Handler to handle the command
// then let GameBoard to handle the command

#include "GameController.h"

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
	*oStream << std::endl;
	oStream->flush();
}

void GameController::LoadRate(int m, int n, float rate) 
{
	
	if (board->getBoardState() == GameBoardState::Idle) 
	{
		board->LoadRandomGenerateMine(m, n, rate);
		*oStream << "< Success >\n";
	}
	else 
	{
		*oStream << "< Failed >\n";
	}
}

void GameController::LoadCount(int m, int n, int c) 
{
	if (board->getBoardState() == GameBoardState::Idle) 
	{
		board->LoadRandomCountMine(m, n, c);
		*oStream << "< Success >\n";
	}
	else
	{
		*oStream << "< Failed >\n";
	}
}

void GameController::StartGame() 
{
	if (board->getIsEnableGameInput() == false)
	{
		*oStream << "©|¥¼¸ü¤J½L­±\n";
	}
	else if (board->getBoardState() != GameBoardState::Idle) 
	{
		*oStream << "< Failed >\n";
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
			*oStream << "GameOver";
		}
	}
	else if (inst == "BombCount") 
	{
		*oStream << board->getMineCount() << '\n';
	}
	else if (inst == "FlagCount") 
	{
		*oStream << board->getFlagCount() << '\n';
	}
	else if (inst == "OpenBlankCount") 
	{
		*oStream << board->getOpenedTileCount() << '\n';
	}
	else if (inst == "RemainBlankCount") 
	{
		*oStream << board->getRemainClosedTileCount() << '\n';
	}
	else 
	{
		////debug snnippet fragment
		////print all counts in board
		//*oStream << "BombCount: " << board->getMineCount() << '\n';
		//*oStream << "FlagCount: " << board->getFlagCount() << '\n';
		//*oStream << "OpenBlankCount: " << board->getOpenedTileCount() << '\n';
		//*oStream << "RemainBlankCount: " << board->getRemainClosedTileCount() << '\n';
		////debug snnippet fragment

		*oStream << "Failed\n";
	}
}

void GameController::LeftClick(int rol, int col) 
{
	// <LeftClick 5 1> :
	string outputString = "<LeftClick " + to_string(rol) + " " + to_string(col) + "> : ";
	*oStream << outputString;
	
	if (board->getBoardState() == GameBoardState::Playing) 
	{
		bool allRight = board->RevealTile(rol, col);
		//*oStream << "Success\n";
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
	// <RightClick 5 1> :
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
		*oStream << "Success\n";
	}
	else
	{
		*oStream << "Failed\n";
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
		*oStream << "You can't quit now.\n";
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