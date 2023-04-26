#pragma once
#ifndef TILE_H
#define TILE_H

#include <iostream>
#include <string>

#endif // TILE_H

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

	// Intent: Constructor of Tile class, initialize the member variables of Tile object.
	// Pre: None.
	// Post: A Tile object is constructed with isMine set to false, mask set to true, state set to TileState::Clean, and mineSurroundCount set to 0.
	Tile();

	
	// Intent: To get the state of a tile.
	// Pre: Tile object must be instantiated.
	// Post: Returns the state of the tile (clean, flagged, question mark or error)
	TileState GetState();


	// Intent: To get the mask of a tile.
	// Pre: Tile object must be instantiated.
	// Post: Returns the mask of the tile, which can be a clean tile, flagged tile, question mark or error.
	std::string GetMask();
	
	// Intent: Get the answer of the tile (mine or number of surrounding mines)
	// Pre: None
	// Post: Return the answer in string format (either "X" for mine or a number for surrounding mines)
	std::string getAnswer();

	
	// Intent: Check if the tile is a mine.
	// Pre: None.
	// Post: Return true if the tile is a mine, false otherwise.
	bool IsMine();

	// Intent: Check if the tile is masked.
	// Pre: None.
	// Post: Return true if the tile is masked, false otherwise.
	bool IsMasking();
	
	// Intent: Check if the tile is clean.
	// Pre: None.
	// Post: Return true if the tile is in clean state, false otherwise.
	bool IsClean();
	
	// Intent: Check if the tile is flagged.
	// Pre: None.
	// Post: Return true if the tile is in flagged state, false otherwise.
	bool IsFlagged();

	// Intent: Check if the tile is marked with a question mark.
	// Pre: None.
	// Post: Return true if the tile is marked with a question mark, false otherwise.
	bool IsQuestionMarked();

	// Intent: Set the tile as a mine
	// Pre: None
	// Post: The tile is marked as a mine
	void SetMine();
	
	// Intent: Set the tile as revealed
	// Pre: None
	// Post: The tile is marked as revealed by setting mask to false
	void SetReveal();

	// Intent: To mark a Tile with a flag or question mark, depending on its current state.
	// Pre: The Tile exists and is not revealed.
	// Post: The Tile's state is updated to the next state in the cycle (clean, flagged, question mark), and the new state is returned.
	TileState FlagMark();

	// Intent: To increase the mine count of a tile.
	// Pre: Tile object must be instantiated.
	// Post: Increases the mine count of the tile by 1.
	void AddMineCount();

	// Intent: To get the number of mines surrounding a Tile.
	// Pre: The Tile exists.
	// Post: The number of mines surrounding the Tile is returned.
	int GetMineCount();

};