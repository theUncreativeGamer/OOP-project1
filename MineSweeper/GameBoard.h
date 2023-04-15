#pragma once
#include <iostream>
#include <exception>
#include <map>
#include <random>
#include <fstream>
#include <regex>
#include <sstream>
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

	int MineCount;
	int FlagCount;
	int QuestionMarkCount;
	int OpenedTileCount;// only adds when tile is opened and not mine
	int RemainClosedTileCount;// only adds when tile is closed and not mine
	//command handler

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
	//void PrintGameState()
	//{
	//	//print game state
	//	std::cout << "Game State: " << GameBoardStateString[gameBoardState] << std::endl;
	//	
	//}

	void PrintBoard();
	void PrintBoardWithMask();

	//click operation
	void RevealTile(int row, int col);
	void FlagTile(int row, int col);

	//actions
	bool checkGame();


};