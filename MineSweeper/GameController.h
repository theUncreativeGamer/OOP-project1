#pragma once
#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

#include "GameBoard.h"

#endif // GAMECONTROLLER_H

using namespace std;

class GameController 
{
private:
	GameBoard* board;
	ostream* oStream;
	
public:
	GameController() 
	{
		this->oStream = &cout;
		board = new GameBoard();
	};
	
	GameController(ostream * oStream)
	{
		this->oStream = oStream;
		board = new GameBoard(((ofstream*)oStream));
	};
	
	// Intent: Load the game board from a file specified by the input path.
	// Pre: GameController object is created and a valid path is provided.
	// Post: If the game board state is idle, load the board from the file and set the game board state to Playing. Otherwise, output an error message indicating that the board cannot be loaded while a game is in progress.
	void LoadPath(string path);
	
	// Intent: Load the game board with random mine count based on given dimensions and mine count
	// Pre: Board state must be idle
	// Post: If board state is idle, the game board will be loaded with random mine count based on given dimensions and mine count, and a success message will be printed to the output stream. Otherwise, a failed message will be printed to the output stream.(Note: This function is calculating the mine count by the given rate, so proof that rate is in range of 0 to 1.)
	void LoadRate(int m, int n, float rate);

	// Intent: Load the game board with a randomly generated mine count with given dimensions
	// Pre: The game board must be in Idle state
	// Post: The game board is loaded with randomly generated mine count and Success is printed to the output stream, or Failed is printed if the game board is not in Idle state.
	void LoadCount(int m, int n, int c);

	// Intent: Start a new game.
	// Pre: A game board has been loaded and game input is enabled.
	// Post: The game has started and the board state has changed to 'Playing'. If the precondition is not met, output an error message.
	void StartGame();
	
	// Intent: Print out game-related information according to the input instruction.
	// Pre: GameController object has been initialized.
	// Post: The requested game information is printed to the output stream. If the input instruction is invalid, "Failed" is printed.
	void Print(string inst);
	
	// Intent: Perform a left click operation on the tile located at the given row and column position.
	// Pre: GameController object and GameBoard object have been initialized and connected. The game board is in the "Playing" state.
	// Post: If the tile at the given position is successfully revealed, the function returns true and updates the game state accordingly. If the tile contains a mine, the game is over and the function returns false. If all non-mine tiles are revealed, the game is won and the function returns true. Additionally, the function checks the game state after the click operation and updates the game state accordingly. The result of the operation (success or failure) is printed to the output stream.
	void LeftClick(int rol, int col);
	
	// Intent: Perform right-click operation on a tile.
	// Pre: GameController object is instantiated, and GameBoard object is loaded with a board file.
	// Post: The state of the tile in the specified row and column is changed to Flagged or QuestionMark, and the number of flagged tiles is incremented or decremented accordingly. A message indicating whether the operation was successful or not is printed to the output stream.
	void RightClick(int rol, int col);

	// Intent: To replay the game
	// Pre: None
	// Post: If the game board state is "End", creates a new game board and sets it as the current board. Prints "Success" if current state is able to replay, and "Failed" if not.
	void Replay();

	// Intent: Quit the game if the board is in end state.
	// Pre: The board state is either Idle or End.
	// Post: If the board state is End, the game is terminated successfully. If the board state is not End, a message is printed indicating that the player cannot quit now.
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

// rightclick, with parameters x and y
	// binding functions
		// set flag, set question mark, set nothing accirding to the current state

// replay: reset the game state, and reramdomize the plane if with parameters