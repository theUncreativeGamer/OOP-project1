#pragma once
#include <iostream>
#include <string>
#include <stdlib.h>
#include "GameBoard.h"

using namespace std;

class GameController 
{
private:
	GameBoard* board;
	
public:
	GameController() 
	{
		board = new GameBoard();
	};
	
	// Intent: Load the game board from a file specified by the input path.
	// Pre: GameController object is created and a valid path is provided.
	// Post: If the game board state is idle, load the board from the file and set the game board state to Playing. Otherwise, output an error message indicating that the board cannot be loaded while a game is in progress.
	void LoadPath(string path);
	
	// Intent:
	// Pre:
	// Post:
	void LoadRate(int m, int n, float rate);

	// Intent:
	// Pre:
	// Post:
	void LoadCount(int m, int n, int c);

	// Intent:
	// Pre:
	// Post:
	void StartGame();
	
	// Intent:
	// Pre:
	// Post:
	void Print(string inst);
	
	// Intent:
	// Pre:
	// Post:
	void LeftClick(int rol, int col);
	
	// Intent:
	// Pre:
	// Post:
	void RightClick(int rol, int col);

	// Intent:
	// Pre:
	// Post:
	void Replay();

	// Intent:
	// Pre:
	// Post:
	void Quit();
};


// commands: execute correspond commands if command exist, else make error message

// commands          idle ,		playing,		end
	// Load			yes			no				no
		// format: Load <mineMapFile>
		// format2: Load RandomRate <row> <column> <mineNumber> <minePossibility>
		// format3: Load RandomCount <row> <column> <mineNumber>
	// startgame 	yes			no				no
	// print 		yes			yes				yes
	// leftclick 	no			yes				no, "left click" the binding function will be replace to other events when not in game play
	// rightclick 	no			yes				no
	// replay 		no			no				yes
	// quit 		no			no				yes


//// commands         
//	// Load			
//		// format: Load <mineMapFile>
//		// format2: Load RandomRate <row> <column> <minePossibility>
//		// format3: Load RandomCount <row> <column> <mineNumber>
//	// startgame 	
//		// format: startgame
//	// print 		
//		// format: print [gameboard,gamestate,gamestate]
//	// leftclick 	
//		// format: leftclick <x> <y>
//	// rightclick 	
//		// format: rightclick <x> <y>
//	// replay
//		// format: replay
//	// quit
//		// format: quit