// Author: 沈登獻 謝嘉銘 蔡耀羽
// Created Date: Apr.11 2023
// Last Modified Date: Apr.19 2023
// Description: This program is a game of MineSweeper. with multi mode and layered class design.

#include <iostream>
#include <vector>
#include <functional>

#include "GameController.h"


int main(int argc, char* argv[])
{
	/*
	MineSweeper.exe CommandFile command.txt output.txt
	MineSweeper.exe CommandInput
	MineSweeper.exe GUI
	*/
	if (argc == 4 && argv[1] == "CommandFile") {
		//MineSweeper.exe CommandFile command.txt output.txt
	}
	else if (argc == 2 && argv[1] == "CommandInput") {
		//MineSweeper.exe CommandInput
	}
	else if (argc == 2 && argv[1] == "GUI") {
		//MineSweeper.exe GUI
	}
	else {
		//fail, due to wrong syntax
	}

	GameController game;
	string input;
	while (cin >> input) {

		if (input == "Load") {
			cin >> input;
			if (input == "BoardFile") {
				cin >> input;
				game.LoadPath(input);
			}
			else if (input == "RandomCount") {
				int m, n, c;
				cin >> m >> n >> c;
				game.LoadCount(m, n, c);
			}
			else if (input == "RandomRate") {
				int m, n, r;
				cin >> m >> n >> r;
				game.LoadRate(m, n, r);
			}
		}
		else if (input == "StartGame") {
			game.StartGame();
		}
		else if (input == "Print") {
			cin >> input;
			game.Print(input);
		}
		else if (input == "LeftClick") {
			int m, n;
			cin >> m >> n;
			game.LeftClick(m, n);
		}
		else if (input == "RightClick") {
			int m, n;
			cin >> m >> n;
			game.RightClick(m, n);
		}
		else if (input == "Replay") {
			game.Replay();
		}
		else if (input == "Quit") {
			game.Quit();
		}
		else {
			cout << "Input Error, try again.\n";
		}
		fflush(stdin);
	}

}
