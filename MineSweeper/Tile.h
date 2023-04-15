#pragma once
#include <iostream>
#include <string>

enum class TileState
{
	Clean,
	Flagged,
	QuestionMark
};

class Tile
{
private:
	bool isMine;
	bool mask;
	TileState state;
	int mineSurroundCount;


public:

	Tile();

	TileState GetState();

	std::string getMask();
	std::string getAnswer();

	bool IsMine();
	bool IsMasking();

	void SetMine();
	void SetReveal();
	void FlagMark();
	void AddMineCount();

};