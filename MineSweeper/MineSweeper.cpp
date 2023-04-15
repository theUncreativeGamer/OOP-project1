// Author:
// Created Date:
// Last Modified Date:
// Description: This program is a game of MineSweeper.

#include <iostream>
#include <vector>
#include <functional>

//#include "Command.cpp"
#include "GameController.h"


int main()
{

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
			exit(0);
		}
		else {
			cout << "Input Error, try again.";
		}
	}

}


// Intent:
// Pre:
// Post:
