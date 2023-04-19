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

	// Intent:
	// Pre:
	// Post:
	bool ValidPosition(int x, int y);

	// Intent:
	// Pre:
	// Post:
	void IncrementSurroundMineCounts(int row_center, int col_center);

	// Intent:
	// Pre:
	// Post:
	void CalculateMines();

	void UpdateOpenedTileCount();
	void UpdateRemainClosedBlankTileCount();

public:

	//constructor
	GameBoard();
	GameBoard(int m, int n);


//loaders
	// Intent:
	// Pre:
	// Post:
	void LoadBoardFile(std::string relative_path);
	
	// Intent:
	// Pre:
	// Post:
	void LoadRandomGenerateMine(int height, int width, int mineCount);
	
	// Intent:
	// Pre:
	// Post:
	void LoadRandomCountMine(int height, int width, float mineGenerateRate);

// printer
	// Intent:
	// Pre:
	// Post:
	void PrintGameState();
	
	// Intent:
	// Pre:
	// Post:
	void PrintBoard();
	
	// Intent:
	// Pre:
	// Post:
	void PrintBoardWithMask();

//click operation
	// Intent:
	// Pre:
	// Post:
	void RevealTile(int row, int col);
	
	// Intent:
	// Pre:
	// Post:
	void FlagTile(int row, int col);

//actions
	// Intent:
	// Pre:
	// Post:
	bool CheckGame();
	
	// Intent:
	// Pre:
	// Post:
	void StartGame();

	// Intent:
	// Pre:
	// Post:
	GameBoardState getBoardState();
	
	// Intent:
	// Pre:
	// Post:
	int getMineCount() { return mineCount; };
	
	// Intent:
	// Pre:
	// Post:
	int getFlagCount() { return flagCount; };
	
	// Intent:
	// Pre:
	// Post:
	int getOpenedTileCount() { return openedTileCount; };
	
	// Intent:
	// Pre:
	// Post:
	// rename it as getRemainClosedBlankTileCount()
	int getRemainClosedTileCount() { return remainClosedBlankTileCount; };
	
	// Intent:
	// Pre:
	// Post:
	bool getIsEnableGameInput() { return isEnableGameInput; };
	
	// Intent:
	// Pre:
	// Post:
	std::string GetGameStateString();

};

