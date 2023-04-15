#pragma once
#include <iostream>
#include <exception>
#include <map>
#include <random>
#include <fstream>
#include <regex>
#include <sstream>
#include "Tile.h"
#include <set>

class GameBoardException : public std::exception
{
public:
	GameBoardException(const char* message) : std::exception(message) {}

private:
	std::string message;
};

enum class GameBoardState
{
	//Idle
	Idle,

	//Gaming
	Playing,

	//End
	Win,
	Lose,
	End

};

class GameBoard
{
private:
	int width;
	int height;

	Tile* board;

	bool isEnableGameInput;
	GameBoardState gameBoardState;

	int mineCount;
	int flagCount;
	int QuestionMarkCount;
	int openedTileCount;// only adds when tile is opened and not mine
	int remainClosedTileCount;// only adds when tile is closed and not mine

private:
	
	void ChangeGameInput();
	void EnableGameInput();
	void DisableGameInput();
	
	bool ValidPosition(int x, int y);
	void CalculateMines();

public:

	//loaders
	void LoadBoardFile(std::string relative_path);
	void LoadRandomGenerateMine(int height, int width, int mineCount);
	void LoadRandomCountMine(int height, int width, float mineGenerateRate);

	// printer
	void PrintGameState();
	void PrintBoard();
	void PrintBoardWithMask();

	//click operation
	void RevealTile(int row, int col);
	void FlagTile(int row, int col);

	//actions
	bool CheckGame();
	std::string GetGameStateString();
	
};