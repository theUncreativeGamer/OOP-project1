//#include <iostream>
//#include <functional>
//#include <vector>
//#include <string>
//#include <sstream>
//
//#include "GameBoard.cpp"

//
//class Command
//{
//public:
//	enum class Type
//	{
//		Quit,
//		Help,
//		Unknown
//	};
//
//	Command(Type type, std::vector<std::string> args)
//		: type(type), args(args)
//	{
//	}
//
//	Type type;
//	std::vector<std::string> args;
//private:
//	std::string CommandName;
//	std::string CommandDescription;
//	std::string CommandArgs;//remain part after command name
//    //function(Command,Args);
//	
//    
//};
//
//
//struct LoadCommand {
//    
//    enum class LoadCommandType {
//        MINE_MAP_FILE,
//        RANDOM_RATE,
//        RANDOM_COUNT
//    };
//    
//    std::string name = "Load";
//    LoadCommandType type;
//    std::function<void(std::string)> execute_mine_map_file;
//    std::function<void(int, int, int, double)> execute_random_rate;
//    std::function<void(int, int, int)> execute_random_count;
//
//    void execute(std::vector<std::string> args) {
//        switch (type) {
//        case LoadCommandType::MINE_MAP_FILE:
//            execute_mine_map_file(args[1]);
//            break;
//        case LoadCommandType::RANDOM_RATE:
//            execute_random_rate(std::stoi(args[1]), std::stoi(args[2]), std::stoi(args[3]), std::stod(args[4]));
//            break;
//        case LoadCommandType::RANDOM_COUNT:
//            execute_random_count(std::stoi(args[1]), std::stoi(args[2]), std::stoi(args[3]));
//            break;
//        }
//    }
//
//    
//};
//
//
//void Command_handler(GameBoard& targetBoard,std::string command, std::string args)
//{
//	//if load
//	if (command == "Load")
//	{
//		//if load mine map file
//		if (args.find(" ") == std::string::npos)
//		{
//			targetBoard.Load(args);
//		}
//		//if load random rate
//		else if (args.find("RandomRate") != std::string::npos)
//		{
//			std::stringstream ss(args);
//			std::string temp;
//			std::vector<std::string> args;
//			while (ss >> temp)
//			{
//				args.push_back(temp);
//			}
//			targetBoard.Load(std::stoi(args[1]), std::stoi(args[2]), std::stoi(args[3]), std::stod(args[4]));
//		}
//		//if load random count
//		else if (args.find("RandomCount") != std::string::npos)
//		{
//			std::stringstream ss(args);
//			std::string temp;
//			std::vector<std::string> args;
//			while (ss >> temp)
//			{
//				args.push_back(temp);
//			}
//			targetBoard.Load(std::stoi(args[1]), std::stoi(args[2]), std::stoi(args[3]));
//		}
//	}
//	// if startgame
//	else if (command == "startgame")
//	{
//		targetBoard.StartGame();
//	}
//	// if print
//	else if (command == "print")
//	{
//		//if print gameboard
//		if (args == "gameboard")
//		{
//			targetBoard.PrintGameBoard();
//		}
//		//if print gamestate
//		else if (args == "gamestate")
//		{
//			targetBoard.PrintGameState();
//		}
//		//if print both
//		else if (args == "both")
//		{
//			targetBoard.PrintGameBoard();
//			targetBoard.PrintGameState();
//		}
//	}
//	// if leftclick
//	else if (command == "leftclick")
//	{
//		std::stringstream ss(args);
//		std::string temp;
//		std::vector<std::string> args;
//		while (ss >> temp)
//		{
//			args.push_back(temp);
//		}
//		targetBoard.RevealTile(std::stoi(args[0]), std::stoi(args[1]));
//	}
//	// if rightclick
//	else if (command == "rightclick")
//	{
//		std::stringstream ss(args);
//		std::string temp;
//		std::vector<std::string> args;
//		while (ss >> temp)
//		{
//			args.push_back(temp);
//		}
//		targetBoard.FlagTile(std::stoi(args[0]), std::stoi(args[1]));
//	}
//	// if replay
//	else if (command == "replay")
//	{
//		//targetBoard.Replay();
//		//delete targetBoard and reconstruct a new one
//		
//		delete& targetBoard;
//		targetBoard = GameBoard();
//		//set state to not started
//	}
//	// if quit
//	else if (command == "quit")
//	{
//		exit(0);
//	}
//	// if unknown
//	else
//	{
//		std::cout << "Unknown command" << std::endl;
//		//throw
//		throw std::exception("Unknown command");
//	}
//	
//};
//
//
//
