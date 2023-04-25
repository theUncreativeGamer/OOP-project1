#include "Tile.h"


Tile::Tile()
{
	isMine = false;
	mask = true;
	state = TileState::Clean;
	mineSurroundCount = 0;
}

bool Tile::IsMine() const
{
	return isMine;
}

bool Tile::IsMasking() const
{
	return mask;
}


bool Tile::IsClean() const
{
	return state == TileState::Clean;
}

bool Tile::IsFlagged() const
{
	return state == TileState::Flagged;
}

bool Tile::IsQuestionMarked() const
{
	return state == TileState::QuestionMark;
}

void Tile::AddMineCount()
{
	++mineSurroundCount;
}

TileState Tile::GetState() const
{
	return state;
}

std::string Tile::GetMask() const
{
	if (mask)
	{
		if (state == TileState::Clean)
		{
			return "#";
		}
		else if (state == TileState::Flagged)
		{
			return "f";
		}
		else if (state == TileState::QuestionMark)
		{
			return "?";
		}
		else
		{
			return "Error: Undefined output";
		}
	}
	else
	{
		return getAnswer();
	}

}
std::string Tile::getAnswer() const
{
	if (isMine)
	{
		return "X";
	}
	else
	{
		return std::to_string(mineSurroundCount);
	}
	
}

void Tile::SetMine()
{
	isMine = true;
}

void Tile::SetReveal()
{
	mask = false;
}

TileState Tile::FlagMark()
{
	if (mask == false)
	{
		//output error
		std::cout << "Error: Tile is already revealed." << std::endl;
		return state;
	}
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
	//return state to add or decrease flag/question/clean count
	return state;
}

int Tile::GetMineCount() const
{
	return mineSurroundCount;
}