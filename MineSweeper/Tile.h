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
	TileState state;
	int  mineSurroundCount;
	bool isMine;
	bool mask;

public:

	// Intent:
	// Pre:
	// Post:
	Tile();

	
	// Intent:
	// Pre:
	// Post:
	TileState GetState();


	// Intent:
	// Pre:
	// Post:
	std::string GetMask();
	
	// Intent:
	// Pre:
	// Post:
	std::string getAnswer();

	
	// Intent:
	// Pre:
	// Post:
	bool IsMine();

	// Intent:
	// Pre:
	// Post:
	bool IsMasking();
	
	// Intent:
	// Pre:
	// Post:
	bool IsClean();
	
	// Intent:
	// Pre:
	// Post:
	bool IsFlagged();

	// Intent:
	// Pre:
	// Post:
	bool IsQuestionMarked();

	// Intent:
	// Pre:
	// Post:
	void SetMine();
	
	// Intent:
	// Pre:
	// Post:
	void SetReveal();

	// Intent:
	// Pre:
	// Post:
	TileState FlagMark();

	// Intent:
	// Pre:
	// Post:
	void AddMineCount();

	// Intent:
	// Pre:
	// Post:
	int GetMineCount();

};