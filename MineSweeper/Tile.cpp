#include "Tile.h"


Tile::Tile()
{
	isMine = false;
	mask = true;
	state = TileState::Clean;
	mineSurroundCount = 0;
}

bool Tile::IsMine()
{
	return isMine;
}

bool Tile::IsMasking()
{
	return mask;
}


bool Tile::IsClean()
{
	return state == TileState::Clean;
}

bool Tile::IsFlagged()
{
	return state == TileState::Flagged;
}

bool Tile::IsQuestionMark()
{
	return state == TileState::QuestionMark;
}

void Tile::AddMineCount()
{
	++mineSurroundCount;
}

TileState Tile::GetState()
{
	return state;
}

std::string Tile::GetMask()
{
	if (mask)
	{
		if (state == TileState::Clean)
		{
			return "#";
		}
		else if (state == TileState::Flagged)
		{
			return "F";
		}
		else if (state == TileState::QuestionMark)
		{
			return "?";
		}
		else
		{
			return "Errrrrrrrrr";
		}
	}
	else
	{
		return getAnswer();
	}

}
std::string Tile::getAnswer()
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

void Tile::FlagMark()
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

int Tile::GetMineCount()
{
	return mineSurroundCount;
}