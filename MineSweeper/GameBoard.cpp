#include "GameBoard.h"

void GameBoard::ChangeGameInput() {

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
						//if not out of range, and if not mine
						if (i + k >= 0 && i + k < width && j + l >= 0 && j + l < height)
						{
							board[(i + k) * width + j + l].AddMineCount();
						}
					}
				}

			}
		}
	}
}

void GameBoard::LoadBoardFile(std::string relative_path)
{
	//load file
	//load width, height
	//load mines
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
	//-----------------
	std::getline(file, line);
	std::cout << line << std::endl;
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

	//------------------
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
			}
		}
		currentHeight++;
	}

	CalculateMines();

	file.close();
}

void GameBoard::LoadRandomGenerateMine(int height, int width, int mineCount)
{
	//load width, height
	//load mines
	//load board
	//calculate mines

	//set width and height
	this->width = width;
	this->height = height;

	//set mine count
	MineCount = mineCount;

	//set board
	board = new Tile[height * width];//construct

	//set mines
	//random generate mines


}

void GameBoard::LoadRandomCountMine(int height, int width, float mineGenerateRate)
{
	//load width, height
	//load mines
	//load board
	//calculate mines


}

// printer
//void PrintGameState()
//{
//	//print game state
//	std::cout << "Game State: " << GameBoardStateString[gameBoardState] << std::endl;
//	
//}

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
			std::cout << board[i * width + j].getMask();//cout tiles with overloaded stream operator to decide its print
		}
		std::cout << std::endl;
	}
}


//click operation
void GameBoard::RevealTile(int row, int col)
{
	//if valid position
	//if not mine
	//if mine
	//if already opened
	//if not flagged

	if (!ValidPosition(row, col))
	{
		throw GameBoardException("Invalid position");
	}
	//if target tile is 

	board[row * width + col].SetReveal();

}

void GameBoard::FlagTile(int row, int col)
{
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
bool GameBoard::checkGame()
{
	//if all mines are flagged
	//if all tiles are opened
	//if mine is opened
	return false;
}

void GameBoard::StartGame() {

}

GameBoardState GameBoard::getBoardState() {
	return gameBoardState;
}



//std::map<GameBoardState, std::string> GameBoardStateString
//{
//	{GameBoardState::Idle, "Idle"},
//	{GameBoardState::Playing, "Playing"},
//	{GameBoardState::Win, "Win"},
//	{GameBoardState::Lose, "Lose"},
//	{GameBoardState::End, "End"}
//};



// load file format:
// row, column in first line
// mine map in other lines, which O means no mine, and X means mine

// generate a random plane
// with paremeters: row, column, number of mines, possibility of mines generates

// open tiles: in some conditions, some of marked tiles cannot be opened, and some of unmarked tiles can be opened

// mark the tile: tile can be only marked when it is not opened

// losegame
	// the position pass in of your pick if it's a mine, then lose the game, terminate current play

// wingame
	// if whole the plane have no more flags justly on mines, then the game wins

// show surround tiles if it is a blank
	// if it is a blank, show the blank, and show the number of mines around it

// print, with paremeters
	// if bool reveal is true, then print the whole plane
	// if bool reveal is false, then print the plane with the hidden tiles and the flags