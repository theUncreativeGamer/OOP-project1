
#ifndef GAMEBOARD_CPP
#define GAMEBOARD_CPP

#include "GameBoard.h"

#endif // GAMEBOARD_CPP

std::map<GameBoardState, std::string> GameBoard::GameBoardStateString
{
	{GameBoardState::Idle, "Standby"},
	{GameBoardState::Playing, "Playing"},
	{GameBoardState::End, "GameOver"}
};

GameBoard::GameBoard()
{
	width = 0;
	height = 0;

	board = NULL;//tile array

	isEnableGameInput = false;
	gameBoardState = GameBoardState::Idle;
	gameBoardResult = GameBoardResult::Playing;		//??

	mineCount = 0;
	flagCount = 0;
	questionMarkCount = 0;
	openedTileCount = 0;
	remainClosedBlankTileCount = 0;

}

GameBoard::GameBoard(std::ostream* oStream)
{
	width = 0;
	height = 0;

	board = NULL;//tile array

	isEnableGameInput = false;
	gameBoardState = GameBoardState::Idle;
	gameBoardResult = GameBoardResult::Playing;		//??

	mineCount = 0;
	flagCount = 0;
	questionMarkCount = 0;
	openedTileCount = 0;
	remainClosedBlankTileCount = 0;
	
	this->oStream = oStream;

}

void GameBoard::EnableGameInput()
{
	// enable the gameinput while current stage is valid controlled by GameController
	isEnableGameInput = true;
}

void GameBoard::DisableGameInput()
{
	// disable the gameinput while current stage is invalid controlled by GameController
	isEnableGameInput = false;
}

bool GameBoard::ValidPosition(int x, int y)
{
	// check if the given coordinates are within the game board range
	//
	if (x < 0 || x >= height || y < 0 || y >= width)
	{
		return false;
	}
	return true;
}

void GameBoard::IncrementSurroundMineCounts(int row_center, int col_center)
{
	// this loop is to give the mine count to the surrounding tiles from a given centered tile
	for (int m = -1; m <= 1; m++)
	{
		for (int n = -1; n <= 1; n++)
		{
			// check if each surrounding tile is not out of range, and add 1 to minecount on the tile
			if (ValidPosition(row_center + m, col_center + n))
			{
				board[(row_center + m) * width + (col_center + n)].AddMineCount();
			}
		}
	}
}


void GameBoard::CalculateMines() 
{
	// after the gameboard created and already initialized to be called
	// for some tiles are mine, add 1 minecount to 3x3 tiles
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (board[i * width + j].IsMine())
			{
				// surrouding tiles around mine, all minecount += 1
				IncrementSurroundMineCounts(i, j);
			}
		}
	}
}

bool GameBoard::LoadBoardFile(std::string relative_path)
{
	// load file format:
	// row, column in first line
	// mine map in remain lines, which O means not mine, and X means mine

	// open file
	std::ifstream file(relative_path);
	if (!file.is_open())
	{
		*oStream << "File not found" << std::endl;
		return false;
	}

	std::string line;
	
	// get row and column by getting first line
	std::getline(file, line);

	// check first row is composed by 2 integers
	std::regex widthHeightChecker(R"(^(\d+)\s+(\d+)$)");

	// then check first line is two integer or not, if true, then assign integers to width and height, if false, return false and terminate the function
	if (!std::regex_match(line, widthHeightChecker))
	{
		*oStream << "Invalid file format" << std::endl;
		return false;
	}

	// load these two integers as width and height
	std::stringstream ss(line);
	ss >> height >> width;

	// create board (allocate)
	board = new Tile[height * width];

	// remain rows must composed by O and X
	std::regex rowContentChecker(R"(^[OX]+$)");
	
	int currentHeight = 0;
	
	// read file line by line
	while (file >> line)
	{
		// reading board map info
		// check each row length is same as width
		// check each row only contains O or X
		if (line.length() != width)
		{
			*oStream << "Invalid file format with row length in map" << std::endl;
			return false;
		}
		if (!std::regex_match(line, rowContentChecker))
		{
			*oStream << "Invalid file format with content" << std::endl;
			return false;
		}

		// check the sign is O or X, if O, then set the tile as not mine (by default), if X, then set the tile as mine
		for (int i = 0; i < width; i++)
		{
			if (line[i] == 'X')
			{
				board[currentHeight * width + i].SetMine();
				mineCount++;
			}
		}
		currentHeight++;
	}
	
	// close file stream
	file.close();
	
	// if height is not same as currentHeight, then output error messgae
	if (currentHeight != height)
	{
		*oStream << "Invalid file format with height" << std::endl;
		return false;
	}

	// initialize members
	EnableGameInput();
	flagCount = 0;
	openedTileCount = 0;
	remainClosedBlankTileCount = width * height - mineCount;

	// initialize mine count to every tile
	CalculateMines();
	
	return true;
}


void GameBoard::LoadRandomGenerateMine(int height, int width, int mineCount)
{
	// generate mine by param count
	// if mineCount is bigger than total tiles, terminate this function
	if (mineCount >= width * height)
	{
		return;
	}
	
	// set width and height
	this->width = width;
	this->height = height;

	// set mine count
	this->mineCount = mineCount;

	// set construct board
	board = new Tile[this->height * this->width];
	
	// initialize all tiles
	for (int i = 0; i < height * width; i++)
	{
		new (&board[i]) Tile();
	}

	// generate random mine
	GenerateMines(this->mineCount);

	// initialize members
	EnableGameInput(); // enable game input
	flagCount = 0;// no flags will be set at begin
	openedTileCount = 0;// no tiles will be opened at begin
	remainClosedBlankTileCount = width * height - mineCount;// all tiles are closed at begin

	CalculateMines();
}

void GameBoard::LoadRandomCountMine(int height, int width, float mineGenerateRate)
{
	// generate mine by param rate
	// if rate is not between 0 and 1, then terminate this function
	if (mineGenerateRate < 0 || mineGenerateRate >= 1)
	{
		return;
	}

	// set width and height
	this->width = width;
	this->height = height;

	// set mine count
	this->mineCount = floor(height * width * mineGenerateRate);

	// set construct board
	board = new Tile[this->height * this->width];
	
	// initialize all tiles
	for (int i = 0; i < height * width; i++)
	{
		new (&board[i]) Tile();
	}

	// generate random mine
	GenerateMines(this->mineCount);

	// initialize members
	EnableGameInput(); // enable game input
	flagCount = 0;// no flags will be set at begin
	openedTileCount = 0;// no tiles will be opened at begin
	remainClosedBlankTileCount = width * height - mineCount;// all tiles are closed at begin

	CalculateMines();
}

void GameBoard::PrintGameState()
{
	// print game state
	*oStream << "Game State: " << GameBoardStateString[gameBoardState] << std::endl;
	return;
}

std::string GameBoard::GetGameStateString()
{
	//return game state string
	return GameBoardStateString[gameBoardState];
}

GameBoardState GameBoard::getBoardState()
{
	// return game board state in enum class type
	return gameBoardState;
}


void GameBoard::PrintBoard()
{
	// print board in answer
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			*oStream << board[i * width + j].getAnswer() << " ";
		}
		*oStream << std::endl;
	}
}

void GameBoard::PrintBoardWithMask()
{
	// print board with mask
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			*oStream << board[i * width + j].GetMask() << " ";
		}
		*oStream << std::endl;
	}
}

bool GameBoard::RevealTile(int row, int col)
{
	// open tiles: only unmarked tiles can be opened

	// if not valid position
	if (!ValidPosition(row, col))
	{
		return false;
	}

	// if already opened, return error message
	else if (!board[row * width + col].IsMasking())
	{
		return false;
	}
	// if flagged or question marked, return error message
	// only unmarked tiles can be opened
	else if (board[row * width + col].IsFlagged() /* ||
		board[row * width + col].IsQuestionMarked()*/)
	{
		return false;
	}
	// if open target is mine, turn game to lose
	else if (board[row * width + col].IsMine())
	{
		gameBoardResult = GameBoardResult::Lose;
		return true;
	}

	
	// if target tile mine count is 0, then keep reveal surround until meet a minecount number is bigger than 0
	// if current this tile has 0 mine count, then add surround to next(expect flagged) to reveal
	// if current this tile has mine count (1~8), stop spread, but reveal
	// using BFS
	
	bool isIteratorOpened;
	bool isIteratorFlagged;

	std::vector<std::pair<int, int>> current;
	std::vector<std::pair<int, int>> next;

	// push the first tile to spread blank tile map
	current.push_back(std::make_pair(row, col));
	
	while (!current.empty())
	{
		// clear next
		next.clear();
		
		// for each tile in current
		for (auto& tile : current)
		{
			// then reveal it
			board[tile.first * width + tile.second].SetReveal();
			
			// if current tile is not mine, and mine count is 0, then add surround to next
			if (board[tile.first * width + tile.second].GetMineCount() == 0)
			{
				// add surround to next
				for (int i = -1; i <= 1; i++)
				{
					for (int j = -1; j <= 1; j++)
					{
						// if is current tile, skip it
						if (i == 0 && j == 0)
						{
							continue;
						}

						// if is in valid position
						if (ValidPosition(tile.first + i, tile.second + j))
						{
							// if is not opened or flagged
							isIteratorOpened = !board[(tile.first + i) * width + tile.second + j].IsMasking();
							isIteratorFlagged = board[(tile.first + i) * width + tile.second + j].IsFlagged();

							if (!isIteratorOpened && !isIteratorFlagged)
							{
								next.push_back(std::make_pair(tile.first + i, tile.second + j));
							}
						}
					}
				}
			}
		}

		// swap current and next
		current.swap(next);
	}
	
	// update opened tile count and remain closed blank tile count
	UpdateOpenedTileCount();
	UpdateRemainClosedBlankTileCount();
	
	return true;
}

bool GameBoard::FlagTile(int row, int col)
{
	// mark tile: tile can be only marked when it is not opened

	// if not valid position
	if (!ValidPosition(row, col))
	{
		return false;
	}
	// and if not Masked
	if (!board[row * width + col].IsMasking())
	{
		return false;
	}

	// if not flagged, then flag it, and update flag count and question mark count
	TileState afterDoFlagMarkTileState = board[row * width + col].FlagMark();
	if (afterDoFlagMarkTileState == TileState::Flagged)
	{
		flagCount++;
	}
	else if (afterDoFlagMarkTileState == TileState::QuestionMark)
	{
		questionMarkCount++;
		flagCount--;
	}
	else if (afterDoFlagMarkTileState == TileState::Clean)
	{
		questionMarkCount--;
	}
	
	return true;
}

bool GameBoard::CheckGame()
{
	// losegame
		// the position pass in of your pick if it's a mine, then lose the game, terminate current play (take response by GameController)
		
	// wingame
		// if remainClosedBlankTileCount == 0, then win the game, terminate current play (take response by GameController)
		// if and only if all flags are on all mines
		// all blank tiles are opened 
		
	// iff all mines are flagged
	if (gameBoardResult == GameBoardResult::Lose)
	{
		// output lose message
		*oStream << "You lose the game" << std::endl;
		
		// turn game to lose
		gameBoardState = GameBoardState::End;
		return true;
	}	
	else if (remainClosedBlankTileCount == 0 )
	{
		// output win message
		*oStream << "You win the game" << std::endl;
		
		// turn game to win
		gameBoardResult = GameBoardResult::Win;
		gameBoardState = GameBoardState::End;
		return true;
	}
	
	return false;
}

void GameBoard::StartGame()
{
	// start game, and set game state to playable
	gameBoardState = GameBoardState::Playing;
}

void GameBoard::UpdateOpenedTileCount() 
{
	// recount opened tile count from whole board
	openedTileCount = 0;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (!board[i * width + j].IsMasking())
			{
				openedTileCount++;
			}
		}
	}

}

void GameBoard::UpdateRemainClosedBlankTileCount() 
{
	// recount remain closed blank tile count from whole board
	remainClosedBlankTileCount = 0;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (board[i * width + j].IsMasking() && board[i * width + j].IsMine()==false)
			{
				remainClosedBlankTileCount++;
			}
		}
	}
}

void GameBoard::GenerateMines(int mineCount)
{
	// under the cases of mineCount is a valid number
	// generate random mines in range of board

	// set the number generate range
	int minBoardIndex = 0;
	int maxBoardIndex = height * width - 1;

	// random generator
	std::random_device rd;
	std::mt19937 gen(rd());

	// insert and store unique random number
	std::set<int> random_numbers;

	// generate random number into set
	while (random_numbers.size() < mineCount)
	{
		std::uniform_int_distribution<> dis(minBoardIndex, maxBoardIndex);
		random_numbers.insert(dis(gen));
	}

	//set these mines into board
	for (auto num : random_numbers)
	{
		board[num].SetMine();
	}
}