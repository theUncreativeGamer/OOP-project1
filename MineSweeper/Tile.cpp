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
	
	Tile() 
	{
		isMine = false;
		mask = true;
		state = TileState::Clean;
		mineSurroundCount = 0;
	}
	
	bool IsMine() 
	{
		return isMine;
	}
	void AddMineCount() 
	{
		mineSurroundCount++;
	}

	TileState GetState()
	{
		return state;
	}

	std::string getMask()
	{
		if (mask)
		{
			return "#";
		}
		else
		{
			return getAnswer();
		}
		
	}
	std::string getAnswer()
	{
		if (isMine)
		{
			return "X";
		}
		else if (state == TileState::Clean)
		{
			return std::to_string(mineSurroundCount);
		}
		else if (state == TileState::Flagged)
		{
			return "F";
		}
		else if (state == TileState::QuestionMark)
		{
			return "?";
		}
		
	}
	
	void SetMine()
	{
		isMine = true;
	}

	bool IsMasking()
	{
		return mask;
	}

	void setReveal() 
	{
		mask = false;
	}

	void FlagMark()
	{
		switch (state)
		{
		case TileState::Clean:
			state = TileState::Flagged;
			break;
		case TileState::Flagged:
			state = TileState::QuestionMark;
			break;
		case TileState::QuestionMark:
			state = TileState::Clean;
			break;
		}
	}

};