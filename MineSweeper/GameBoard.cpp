#include "GameBoard.h"
#include <vector>

std::map<GameBoardState, std::string> GameBoard::GameBoardStateString
{
	{GameBoardState::Idle, "Idle"},
	{GameBoardState::Playing, "Playing"},
	{GameBoardState::End, "End"}
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

void GameBoard::IncrementSurroundMineCounts(int row_center, int col_center)
{
	for (int m = -1; m <= 1; m++)
	{
		for (int n = -1; n <= 1; n++)
		{
			//if not out of range
			if (ValidPosition(row_center + m, col_center + n))
			{
				board[(row_center + m) * width + (col_center + n)].AddMineCount();
			}
		}
	}
}


void GameBoard::CalculateMines() //after the gameboard created
{
	//for all tiles find mine and add 1 minecount to 3x3 tiles
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (board[i * width + j].IsMine())
			{
				//surrouding tiles all +=1
				IncrementSurroundMineCounts(i, j);
			}
		}
	}
}

void GameBoard::LoadBoardFile(std::string relative_path)
{
	// load file format:
	// row, column in first line
	// mine map in other lines, which O means no mine, and X means mine

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

	// check first row is composed by 2 integers
	std::regex widthHeightChecker(R"(^(\d+)\s+(\d+)$)");

	//then check first line is two integer or not, then put integers to width and height
	if (!std::regex_match(line, widthHeightChecker))
	{
		//throw GameBoardException("Invalid file format");
		std::cout << "Invalid file format" << std::endl;
		return;
	}

	//load these two integers as width and height
	std::stringstream ss(line);
	ss >> width >> height;
	//close stringstream
	//delete &ss;

	//create board(allocate)
	board = new Tile[height * width];//construct

	//remain row must with O or X in all
	std::regex rowContentChecker(R"(^[OX]+$)");
	
	int currentHeight = 0;
	// read file line by line
	while (file >> line)
	{
		//check each row length is same as width
		//check each row only contains O or X
		//readi n board info
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
	
	file.close();
	
	// if height is not same as currentHeight, then throw exception
	if (currentHeight != height)
	{
		//throw GameBoardException("Invalid file format with height");
		std::cout << "Invalid file format with height" << std::endl;
	}

	//initialize members
	EnableGameInput();
	flagCount = 0;
	openedTileCount = 0;
	remainClosedBlankTileCount = width * height - mineCount;

	//initialize mine count to every tile
	CalculateMines();

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
	EnableGameInput();
	gameBoardState = GameBoardState::Playing;
	flagCount = 0;// no flags will be set at begin
	openedTileCount = 0;// no tiles will be opened at begin
	remainClosedBlankTileCount = width * height - mineCount;// all tiles are closed at begin

	CalculateMines();
}

void GameBoard::LoadRandomCountMine(int height, int width, float mineGenerateRate)
{
	//assign width, height
	//allocate board
	//generate mines
	

	// if rate is not between 0 and 1, then throw exception
	if (mineGenerateRate < 0 || mineGenerateRate >= 1)
	{
		//throw GameBoardException("Invalid mine generate rate");
		std::cout << "Invalid mine generate rate" << std::endl;
		return;
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
	remainClosedBlankTileCount = width * height - mineCount;

	//calculate mines
	CalculateMines();
}

// printer
void GameBoard::PrintGameState()
{
	//print game state
	std::cout << "Game State: " << GameBoardStateString[gameBoardState] << std::endl;

}

std::string GameBoard::GetGameStateString()
{
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
			std::cout << board[i * width + j].getAnswer();
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
			std::cout << board[i * width + j].GetMask();
		}
		std::cout << std::endl;
	}
}


//click operation
void GameBoard::RevealTile(int row, int col)
{
	// open tiles: only unmarked tiles can be opened

	//還要擴散到周圍
	//直到遇到數字為止

	//if valid position
	if (!ValidPosition(row, col))
	{
		//throw GameBoardException("Invalid position");
		std::cout << "Invalid position" << std::endl;
		return;
	}

	// if is mine, turn game to lose
	if (board[row * width + col].IsMine())
	{
		gameBoardResult = GameBoardResult::Lose;
		return;
	}

	//if already opened, return error mesage
	if (!board[row * width + col].IsMasking())
	{
		std::cout << "Tile already opened" << std::endl;
		return;
	}

	//if flagged or question marked, return error message
	if (board[row * width + col].IsFlagged() || 
		board[row * width + col].IsQuestionMarked())
	{
		//cout true of two conditions
		/*std::cout << (board[row * width + col].IsFlagged() ? "flag true" : "flag false") << "\n";
		std::cout << (board[row * width + col].IsQuestionMarked() ? "question true" : "question false") << "\n";*/
		//cout error
		std::cout << "Tile is flagged or question marked" << std::endl;
		return;
	}

	//if target tile mine count is 0, then keep reveal surround until meet a minecount number is bigger than 0
	//using BFS
	// if current this tile has 0 mine count, then add surround to next(expect flagged) to reveal
	// if current this tile has mine count (1~8), stop spread, but reveal

	bool isIteratorOpened;
	bool isIteratorFlagged;

	std::vector<std::pair<int, int>> current;
	std::vector<std::pair<int, int>> next;

	//push the first tile to spread blank tile map
	current.push_back(std::make_pair(row, col));
	
	while (!current.empty())
	{
		//clear next
		next.clear();
		
		//for each tile in current
		for (auto& tile : current)
		{
			//then reveal it
			board[tile.first * width + tile.second].SetReveal();
			
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
							//if is not flagged // this is no need.
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
	
	UpdateOpenedTileCount();
	UpdateRemainClosedBlankTileCount();
	
}

// click operation
void GameBoard::FlagTile(int row, int col)
{
	// mark the tile: tile can be only marked when it is not opened

	//if not valid position
	if (!ValidPosition(row, col))
	{
		//throw GameBoardException("Invalid position");
		std::cout << "Invalid position" << std::endl;
	}
	// and if not Masked
	if (!board[row * width + col].IsMasking())
	{
		//throw GameBoardException("Invalid operation");
		std::cout << "Invalid operation" << std::endl;
	}

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
	
}

//actions
bool GameBoard::CheckGame()
{
	// losegame
		// the position pass in of your pick if it's a mine, then lose the game, terminate current play -> responsible by in the charge of GameController
		
	//iff all mines are flagged
	if (gameBoardResult == GameBoardResult::Lose)
	{
		//output lose message
		std::cout << "You lose the game" << std::endl;
		return true;
	}

	
	// wingame
		// if remainClosedBlankTileCount == 0, then win the game, terminate current play -> responsible by in the charge of GameController
		// if and only if all flags are on all mines
		// all blank tiles are opened 
	int totalTileCount = width * height;
	
	if (remainClosedBlankTileCount == 0 && flagCount == mineCount)
	{
		//output win message
		std::cout << "You win the game" << std::endl;
		gameBoardResult = GameBoardResult::Win;
		return true;
	}

	// if all tiles are opened
	if (totalTileCount - openedTileCount == mineCount)
	{
		//output win message
		std::cout << "You win the game" << std::endl;
		gameBoardResult = GameBoardResult::Win;
		return true;
	}
	// probably disable this condition, due to with last several mines, player will try to flag all mines in order to win
	//else if all flags only on mines
	else if (flagCount == mineCount)
	{
		//check if all flags are on mines
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				if (board[i * width + j].IsFlagged() && !board[i * width + j].IsMine())
				{
					return false;
				}
			}
		}

		gameBoardResult = GameBoardResult::Win;
		return true;
	}



	return false;
}

void GameBoard::StartGame()
{
	//start game
	//set game state to playing
	gameBoardState = GameBoardState::Playing;
}


void GameBoard::UpdateOpenedTileCount() 
{
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