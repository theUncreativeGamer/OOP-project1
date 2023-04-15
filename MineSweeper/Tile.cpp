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
void Tile::AddMineCount()
{
	mineSurroundCount++;
}

TileState Tile::GetState()
{
	return state;
}

std::string Tile::getMask()
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
std::string Tile::getAnswer()
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

void Tile::SetMine()
{
	isMine = true;
}

bool Tile::IsMasking()
{
	return mask;
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