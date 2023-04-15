// using GameController to input command to Commmand Handler
// then  let Command Handler to handle the command
// then let GameBoard to handle the command


/*
MineSweeper.exe CommandFile command.txt output.txt
MineSweeper.exe CommandInput
MineSweeper.exe GUI
*/

//entry point









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




// command handler: handle the command with situation can be executed or not, if not , throw a error message

// operation events
// rightclick, with parameters x and y
	// binding functions
		// set flag, set question mark, set nothing accirding to the current state

// leftclick
	// binding functions
		// if it is a mine, game over
		// if it is not a mine, show the number of mines around it
		// if it is a blank, show the blank, and show the number of mines around it

// replay: reset the game state, and reramdomize the plane if with parameters