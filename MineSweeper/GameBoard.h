#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <exception>
#include <map>
#include <set>
#include <regex>
#include <random>

#include "Tile.h"

class GameBoardException : public std::exception
{
public:
	GameBoardException(const char* message) : std::exception(message) {}

private:
	std::string message;
};

enum class GameBoardState
{
	Idle,
	Playing,
	End
};

//³Ó­t 
enum class GameBoardResult
{
	Win,
	Lose,
	Playing//?
};



class GameBoard
{
private:
	int width;
	int height;

	Tile* board;

	bool isEnableGameInput;
	GameBoardState gameBoardState;
	GameBoardResult gameBoardResult;	//??

	int mineCount;//after initialized, it was a fixed value
	
	int flagCount;// mark will add or decrease this
	int questionMarkCount;// mark will add or decrease this
	
	int openedTileCount;// only adds when tile is opened and not mine
	int remainClosedBlankTileCount;// only adds when tile is closed and not mine
	
	static std::map<GameBoardState, std::string> GameBoardStateString;
	
private:

	// Intent:
	// Pre:
	// Post:
	void ChangeGameInput();

	// Intent:
	// Pre:
	// Post:
	void EnableGameInput();

	// Intent:
	// Pre:
	// Post:
	void DisableGameInput();

	// Intent: Check if the given coordinates are within the game board range and not already opened.
	// Pre: x and y are valid integers.
	// Post: Return true if the given coordinates are within the game board range and not already opened; otherwise, return false.
	bool ValidPosition(int x, int y);

	// Intent: To increment the mine count for surrounding tiles of a given tile.
	// Pre: GameBoard object must be instantiated and the given tile must be a mine.
	// Post: Increments the mine count for surrounding tiles of the given tile.
	void IncrementSurroundMineCounts(int row_center, int col_center);

	// Intent: To calculate the mine counts for each tile on the game board.
	// Pre: GameBoard object must be instantiated and game board must be created.
	// Post: Calculates the mine counts for each tile on the game board.
	void CalculateMines();

	// Intent: To update the count of opened tiles.
	// Pre: GameBoard object must be instantiated.
	// Post: Updates the count of opened tiles.
	void UpdateOpenedTileCount();
	
	// Intent: To update the count of remaining unopened blank tiles.
	// Pre: GameBoard object must be instantiated.
	// Post: Updates the count of remaining unopened blank tiles.
	void UpdateRemainClosedBlankTileCount();

public:

	//constructor
	GameBoard();
	GameBoard(int m, int n);


//loaders
	// Intent: Loads a mine map from a file with a specific format and initializes the game board.
	// Pre: A valid file path is passed as a parameter.
	// Post: If the file exists and has a valid format, the game board is initialized with the information from the file.
	void LoadBoardFile(std::string relative_path);
	
	// Intent: This function loads a game board with randomly generated mines
	// Pre: The height, width, and mineCount parameters are valid integers
	// Post: A game board is created with randomly generated mines and all other tiles are initialized with no mine and with the mine count for surrounding tiles calculated. The game state is set to Playing, the flag count is set to 0, the opened tile count is set to 0, and the remaining closed blank tile count is set to the total number of tiles minus the mine count.
	void LoadRandomGenerateMine(int height, int width, int mineCount);
	
	// Intent: This function loads a game board with randomly generated mines
	// Pre: The height, width, and mineCount parameters are valid integers
	// Post: A game board is created with randomly generated mines and all other tiles are initialized with no mine and with the mine count for surrounding tiles calculated. The game state is set to Playing, the flag count is set to 0, the opened tile count is set to 0, and the remaining closed blank tile count is set to the total number of tiles minus the mine count.
	void LoadRandomCountMine(int height, int width, float mineGenerateRate);

// printer
	// Intent: Prints the current game state to the console.
	// Pre: None
	// Post: The current game state has been printed to the console.
	void PrintGameState();
	
	// Intent:
	// To print the answer board of the game board, which shows where the mines are located and where the numbers are.
	// Pre:
	// - The game board must have been initialized and loaded with mines.
	// - The board array must have been filled with Tile objects.
	// Post:
	// - The answer board of the game board will be printed to the console.
	// - The function will not modify the game board or its state.
	void PrintBoard();
	
	// Intent: This function prints the game board with the mask.
	// Pre: The game board has been initialized and the mask for each tile has been set.
	// Post: The game board with the mask has been printed to the console.
	void PrintBoardWithMask();

//click operation
	// Intent:
	// Pre:
	// Post:
	void RevealTile(int row, int col);
	
	// Intent: This function marks a tile with a flag or a question mark based on user input.
	// Pre: The GameBoard object has been initialized and a game has been started. row and col represent valid positions on the game board.
	// Post: The tile at the given position has been marked with a flag or question mark, or unmarked if it was already marked. The flagCount and questionMarkCount member variables are updated accordingly. If an invalid position or operation is provided, an error message is displayed.
	void FlagTile(int row, int col);

//actions
	// Intent: To check the game status and determine if the game is over.
	// Pre: GameBoard object must be instantiated.
	// Post: Returns true if the game is over, false otherwise.
	bool CheckGame();
	
	// Intent: To start the game and set the game state to playing.
	// Pre: GameBoard object must be instantiated.
	// Post: Sets the game state to playing.
	void StartGame();

	// Intent: Return the current state of the game board
	// Pre: None
	// Post: The current state of the game board is returned as a GameBoardState enum value
	GameBoardState getBoardState();
	
	// Intent: Get the number of mines on the game board.
	// Pre: None.
	// Post: Return an integer representing the number of mines on the game board.
	int getMineCount() { return mineCount; };
	
	// Intent: Get the number of flagged tiles on the game board.
	// Pre: None.
	// Post: Return an integer representing the number of flagged tiles on the game board.
	int getFlagCount() { return flagCount; };
	
	// Intent: Get the number of opened tiles on the game board.
	// Pre: None.
	// Post: Return an integer representing the number of opened tiles on the game board.
	int getOpenedTileCount() { return openedTileCount; };
	
	// Intent: Get the number of remain closed blank tiles on the game board.
	// Pre: None.
	// Post: Return an integer representing the number of remain closed blank tiles on the game board.
	// rename it as getRemainClosedBlankTileCount()
	int getRemainClosedTileCount() { return remainClosedBlankTileCount; };
	
	// Intent: Get whether the game input is enabled.
	// Pre: None.
	// Post: Return a boolean indicating whether the game input is enabled.
	bool getIsEnableGameInput() { return isEnableGameInput; };
	
	// Intent: To get the game state as a string.
	// Pre: GameBoard object must be instantiated.
	// Post: Returns the game state as a string.
	std::string GetGameStateString();

};

