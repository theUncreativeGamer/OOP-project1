﻿// Author: 沈登獻 謝嘉銘 蔡耀羽
// Created Date: Apr.11 2023
// Last Modified Date: Apr.19 2023
// Description: This program is a game of MineSweeper. with multi mode and layered class design.
#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <functional>

#include "GameController.h"
#include "../GUI/GameGUI.h"


int main(int argc, char* argv[])
{
	/*
	MineSweeper.exe CommandFile command.txt output.txt
	MineSweeper.exe CommandInput
	MineSweeper.exe GUI
	*/

	istream* iStream = &cin;
	ostream* oStream = &cout;
	
	if (argc == 4 && string(argv[1]) == "CommandFile") 
	{
		//MineSweeper.exe CommandFile command.txt output.txt
		ifstream commandFile(argv[2]);
		ofstream outputFile(argv[3]);
		
		iStream = &commandFile;
		oStream = &outputFile;		
	}
	else if (argc == 2 && string(argv[1]) == "CommandInput") 
	{
		//MineSweeper.exe CommandInput
		iStream = &cin;
	}
	else if (argc == 2 && string(argv[1]) == "GUI") 
	{
		//MineSweeper.exe GUI
		return gui::MakeMainWindow(argc, argv);
	}
	else 
	{
		//fail, due to wrong syntax
		std::cout << "Wrong syntax, please follow syntax like:\n";
		std::cout << "MineSweeper.exe CommandFile <command.txt> <output.txt>\n";
		std::cout << "MineSweeper.exe CommandInput\n";
		std::cout << "MineSweeper.exe GUI\n";
		//return 0;
	}

	//command input
	GameController game(oStream);
	string input;
	while (*iStream >> input) 
	{

		if (input == "Load") 
		{
			*iStream >> input;
			if (input == "BoardFile") 
			{
				*iStream >> input;
				game.LoadPath(input);
			}
			else if (input == "RandomCount") 
			{
				int m, n, c;
				*iStream >> m >> n >> c;
				game.LoadCount(m, n, c);
			}
			else if (input == "RandomRate") 
			{
				int m, n, r;
				*iStream >> m >> n >> r;
				game.LoadRate(m, n, r);
			}
		}
		else if (input == "StartGame") 
		{
			game.StartGame();
		}
		else if (input == "Print") 
		{
			*iStream >> input;
			game.Print(input);
		}
		else if (input == "LeftClick") 
		{
			int m, n;
			*iStream >> m >> n;
			game.LeftClick(m, n);
		}
		else if (input == "RightClick") 
		{
			int m, n;
			*iStream >> m >> n;
			game.RightClick(m, n);
		}
		else if (input == "Replay") 
		{
			game.Replay();
		}
		else if (input == "Quit") 
		{
			game.Quit();
		}
		else 
		{
			cout << "Input Error, try again.\n";
		}
		fflush(stdin);
	}

}
