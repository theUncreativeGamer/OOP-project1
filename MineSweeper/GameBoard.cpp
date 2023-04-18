#include "GameBoard.h"
#include <vector>

GameBoard::GameBoard()
{
	width = 0;
	height = 0;

	board = NULL;

	isEnableGameInput = false;
	gameBoardState = GameBoardState::Idle;
	gameBoardResult = GameBoardResult::Playing;		//??

	mineCount = 0;
	flagCount = 0;
	QuestionMarkCount = 0;
	openedTileCount = 0;
	remainClosedTileCount = 0;
}


void GameBoard::ChangeGameInput() 
{
	//enable or disable game input
	//but seems unneeded, processed by GameController lul.
}

void GameBoard::EnableGameInput()
{
	isEnableGameInput = true;
}

void GameBoard::DisableGameInput()
{
	isEnableGameInput = false;
}

bool GameBoard::ValidPosition(int x, int y)
{
	//if already opened return false;
	//if out of range return false
	if (x < 0 || x >= width || y < 0 || y >= height)
	{
		return false;
	}
	return true;
}

void GameBoard::CalculateMines() //after the gameboard created
{
	//A: for all tiles
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if (board[i * width + j].IsMine())
			{
				//B: surrouding tiles	
							// surround all ++
				for (int k = -1; k <= 1; k++)
				{
					for (int l = -1; l <= 1; l++)
					{
						//if not out of range
						if (ValidPosition(i + k, j + l))
						{
							board[(i + k) * width + (j + l)].AddMineCount();
						}
					}
				}

			}
		}
	}
}

void GameBoard::LoadBoardFile(std::string relative_path)
{
	// load file format:
	// row, column in first line
	// mine map in other lines, which O means no mine, and X means mine

	//load file
	//load width, height
	//load board
	//calculate mines

	//open file
	std::ifstream file(relative_path);
	if (!file.is_open())
	{
		//throw GameBoardException("File not found");
		std::cout << "File not found" << std::endl;
		return;
	}


	std::string line;
	std::getline(file, line);

	//first row must be only two integer
	//std::regex widthHeightChecker(R"(((\d+)\s+(\d+))");
	std::regex widthHeightChecker(R"(^(\d+)\s+(\d+)$)");

	//then check first line is two integer or not, then put integers to width and height
	if (!std::regex_match(line, widthHeightChecker))
	{
		//throw GameBoardException("Invalid file format");
		std::cout << "Invalid file format" << std::endl;
		return;
	}

	//put integers to width and height
	//conver string to stringstream, and read integers to width and height
	std::stringstream ss(line);
	ss >> width >> height;

	//delete &ss;

	board = new Tile[height * width];//construct

	//remain row must with O or X in all
	std::regex rowContentChecker(R"(^[OX]+$)");


	//check each row length is same as width
	//check each row only contains O or X
	//read board
	int currentHeight = 0;
	while (file >> line)
	{
		if (line.length() != width)
		{
			throw GameBoardException("Invalid file format with row length in map");
		}
		if (!std::regex_match(line, rowContentChecker))
		{
			throw GameBoardException("Invalid file format with content");
		}

		//then put each character if is mine,put to board
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

	// if height is not same as currentHeight, then throw exception
	if (currentHeight != height)
	{
		//throw GameBoardException("Invalid file format with height");
		std::cout << "Invalid file format with height" << std::endl;
	}

	//initialize members
	flagCount = 0;
	openedTileCount = 0;
	remainClosedTileCount = width * height - mineCount;

	//initialize mine count to every tile
	CalculateMines();

	file.close();
}


void GameBoard::LoadRandomGenerateMine(int height, int width, int mineCount)
{
	//set width and height
	this->width = width;
	this->height = height;

	// if mineCount is bigger than total tiles, then throw exception
	if (mineCount >= width * height)
	{
		//throw GameBoardException("Mine count is bigger than total tiles");
		std::cout << "Error: Mine count is bigger than total tiles" << std::endl;
	}

	//set mine count
	mineCount = mineCount;



	//set board
	board = new Tile[height * width];//construct
	//initialize all tiles
	for (int i = 0; i < height * width; i++)
	{
		board[i] = Tile();
	}


	//set mines
	//random generate mines
	int minBoardIndex = 0;
	int maxBoardIndex = height * width - 1;

	std::random_device rd;
	std::mt19937 gen(rd());

	std::set<int> random_numbers;

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

	//initialize members
	isEnableGameInput = true;
	gameBoardState = GameBoardState::Playing;
	flagCount = 0;
	openedTileCount = 0;
	remainClosedTileCount = width * height - mineCount;

	CalculateMines();
}

void GameBoard::LoadRandomCountMine(int height, int width, float mineGenerateRate)
{
	//load width, height
	//load mines
	//load board
	//calculate mines

	// if rate is not between 0 and 1, then throw exception
	if (mineGenerateRate < 0 || mineGenerateRate >= 1)
	{
		//throw GameBoardException("Invalid mine generate rate");
		std::cout << "Invalid mine generate rate" << std::endl;
	}

	//set width and height
	this->width = width;
	this->height = height;

	//set mine count
	mineCount = height * width * mineGenerateRate;


	//set board
	board = new Tile[height * width];//construct
	//initialize all tiles
	for (int i = 0; i < height * width; i++)
	{
		board[i] = Tile();
	}

	//set mines
	//random generate mines
	int minBoardIndex = 0;
	int maxBoardIndex = height * width - 1;

	std::random_device rd;
	std::mt19937 gen(rd());

	std::set<int> random_numbers;

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

	//initialize members
	isEnableGameInput = true;
	gameBoardState = GameBoardState::Playing;
	flagCount = 0;
	openedTileCount = 0;
	remainClosedTileCount = width * height - mineCount;

	CalculateMines();
}

// printer
void GameBoard::PrintGameState()
{
	std::map<GameBoardState, std::string> GameBoardStateString
	{
		{GameBoardState::Idle, "Idle"},
		{GameBoardState::Playing, "Playing"},
		{GameBoardState::End, "End"}
	};
	//print game state
	std::cout << "Game State: " << GameBoardStateString[gameBoardState] << std::endl;

}

std::string GameBoard::GetGameStateString()
{
	std::map<GameBoardState, std::string> GameBoardStateString
	{
		{GameBoardState::Idle, "Idle"},
		{GameBoardState::Playing, "Playing"},
		{GameBoardState::End, "End"}
	};
	//print game state
	return GameBoardStateString[gameBoardState];
}

GameBoardState GameBoard::getBoardState()
{
	return gameBoardState;
}


void GameBoard::PrintBoard()//print answer
{
	//print board
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			std::cout << board[i * width + j].getAnswer();//cout tiles with overloaded stream operator to decide its print
		}
		std::cout << std::endl;
	}
}

void GameBoard::PrintBoardWithMask()
{
	//print board with mask
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			std::cout << board[i * width + j].GetMask();//cout tiles with overloaded stream operator to decide its print
		}
		std::cout << std::endl;
	}
}


//click operation
void GameBoard::RevealTile(int row, int col)
{
	// open tiles: only unmarked tiles can be opened

	//if valid position
	//if not mine
	//if mine
	//if already opened
	//if not flagged

	//還要擴散到周圍
	//直到遇到數字為止

	if (!ValidPosition(row, col))
	{
		throw GameBoardException("Invalid position");
	}

	// if is mine, turn game to lose
	if (board[row * width + col].IsMine())
	{
		gameBoardResult = GameBoardResult::Lose;
		return;
	}

	//if opened, return error mesage
	if (!board[row * width + col].IsMasking())
	{
		//cout error
		std::cout << "Tile already opened" << std::endl;
	}

	bool isOpened;
	bool isFlagged;
	bool isIteratorOpened;
	bool isIteratorFlagged;

	std::vector<std::pair<int, int>> current;
	std::vector<std::pair<int, int>> next;

	//push the first tile to spread blank tile map
	current.push_back(std::make_pair(row, col));

	//if target tile mine count is 0, then keep reveal surround until meet a minecount number is bigger than 0
	//using BFS

	// if current this tile has 0 mine count, then add surround to next(expect flagged) to reveal
	// if current this tile has mine count (1~8), stop spread, but reveal

	while (!current.empty())
	{
		//clear next
		next.clear();

		//for each tile in current
		for (auto& tile : current)
		{
			//then reveal it
			board[tile.first * width + tile.second].SetReveal();
			openedTileCount++;
			remainClosedTileCount--;

			//if current tile is not mine, and mine count is 0, then add surround to next
			if (board[tile.first * width + tile.second].GetMineCount() == 0)
			{
				//add surround to next
				for (int i = -1; i <= 1; i++)
				{
					for (int j = -1; j <= 1; j++)
					{
						//if is not current tile
						if (i == 0 && j == 0)
						{
							continue;
						}

						//if is valid position
						if (ValidPosition(tile.first + i, tile.second + j))
						{
							//if is not opened
							isIteratorOpened = !board[(tile.first + i) * width + tile.second + j].IsMasking();
							//if is not flagged
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

		//swap current and next
		current.swap(next);
	}
}

// click operation
void GameBoard::FlagTile(int row, int col)
{
	// mark the tile: tile can be only marked when it is not opened

	// in order of :
		//Blank-> Flagged
		//Flagged -> QuestionMark
		//QuestionMark -> Blank
	//if not valid position
	if (!ValidPosition(row, col))
	{
		throw GameBoardException("Invalid position");
	}
	// and if not Masked
	if (!board[row * width + col].IsMasking())
	{
		throw GameBoardException("Invalid operation");
	}


	board[row * width + col].FlagMark();
}

//actions
bool GameBoard::CheckGame()
{
	// losegame
		// the position pass in of your pick if it's a mine, then lose the game, terminate current play
	// wingame
		// if whole the plane have no more flags justly on mines, then the game wins

	//if all mines are flagged
	//if all tiles are opened
	//if mine is opened




	return false;
}

void GameBoard::StartGame()
{
	//start game
	//set game state to playing
	gameBoardState = GameBoardState::Playing;
}
