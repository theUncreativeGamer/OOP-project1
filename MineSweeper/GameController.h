#pragma once
#include <iostream>
#include <string>
#include <stdlib.h>
#include "GameBoard.h"

using namespace std;

class GameController {
	GameBoard* board;
public:
	GameController() {
		board = new GameBoard();
	};
	void LoadPath(string path);
	void LoadRate(int m, int n, float rate);
	void LoadCount(int m, int n, int c);
	void StartGame();
	void Print(string inst);
	void LeftClick(int rol, int col);
	void RightClick(int rol, int col);
	void Replay();
	void Quit();
};


// commands: execute correspond commands if command exist, else make error message

// commands          idle ,		playing,		end
	// Load			yes			no				no
		// format: Load <mineMapFile>
		// format2: Load RandomRate <row> <column> <mineNumber> <minePossibility>
		// format3: Load RandomCount <row> <column> <mineNumber>
	// startgame 	yes			no				no
	// print 		yes			yes				yes
	// leftclick 	no			yes				no, "left click" the binding function will be replace to other events when not in game play
	// rightclick 	no			yes				no
	// replay 		no			no				yes
	// quit 		no			no				yes
