#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;

// Create a class for sudoku game creation
class sudoku
{
	//Public can be used in "int main()"
	public:
		void makeBoard();
		void printBoard();
		void insertNumber();
		void removeNumber();
		bool checkComplete();
	//Private can only be used inside class functions
	private:
		bool checkAll(int row, int col, int num);
		bool checkBlock(int row, int col, int num);
		bool checkRow(int row, int num);
		bool checkCol(int col, int num);
		int board[13][13];
};

//Randomly Generate the Board
void sudoku::makeBoard()
{
	//Establish RNG
	srand(time(0));

	//Counter Variables
	int row, col, x;

	// # of clue and num variables
	int clue;
	int num;

	//Generate random # of clues (17-38)
	clue = rand() % 21 + 17;
	//cout << clue << endl;

	//Fill the 2D Array (empty)
	for(row=1;row<12;row++)
	{
		for(col=1;col<12;col++)
		{
			board[row][col] = 0;
		}
	}

	//Fill the 2d Array (Clues)
	while(x < clue)
	{

		row = rand() % 10 + 1;
		col = rand() % 10 + 1;
		num = rand() % 8 + 1;

		//Decrement if not valid spot
		if( row != 4 && row != 8 && col != 4 && col != 8 && board[row][col] == 0 )
		{
			if(checkAll(row, col, num))
			{
				board[row][col] = num;
				x++;
			}
		}
	}

	return;
};

//Print the Board
void sudoku::printBoard()
{

	int row, col;

	for(row=1;row<12;row++)
	{
		for(col=1;col<12;col++)
		{
			//Print Dashes
			if( row == 4 || row == 8)
			{
				cout << setw(3);
				cout << "-";
			}
			//Print "|" (Whatever these are called?) (pipes lol)
			else if( col == 4 || col == 8 )
			{
				cout << setw(3);
				cout << "|";
			}
			//Print numbers on the board
			else
			{
				cout << setw(3);
				cout << board[row][col];
			}
		}
		cout << endl;
	}

	return;
};

bool sudoku::checkAll(int row, int col, int num)
{
	bool colCheck, rowCheck, boxCheck;

	//Calls Collumn Checking Function
	colCheck = checkCol(col, num);
	//Calls Row Checking Function
	rowCheck = checkRow(row, num);
	//Calls 3x3 Box Checking Function
	boxCheck = checkBlock(row, col, num);

	//If all come back as true allow number to be placed on board!
	if(colCheck == true && rowCheck == true && boxCheck == true)
	{
		return true;
	}
	else
	{
	return false;
	}
}

//Check Row
bool sudoku::checkRow( int row, int num )
{
	int count;

	for(count=1;count<12;count++)
	{
		if(board[row][count] == num)
		{
			return false;
		}
	}

	return true;
}

//Check Collumn
bool sudoku::checkCol( int col, int num )
{
	int count;

	for(count=1;count<12;count++)
	{
		if(board[count][col] == num)
		{
			return false;
		}
	}

	return true;
}

bool sudoku::checkBlock(int row, int col, int num)
{
	int xCount, yCount, xStart, yStart;

	//Ignore this, just allows board to look nicer (im lazy)
	if(row == 1 || row == 2 || row == 3)
		xStart = 1;
	if(row == 5 || row == 6 || row == 7)
		xStart = 5;
	if(row == 9 || row == 10 || row == 11)
		xStart = 9;
	if(col == 1 || col == 2 || col == 3)
		yStart = 1;
	if(col == 5 || col == 6 || col == 7)
		yStart = 5;
	if(col == 9 || col == 10 || col == 11)
		yStart = 9;

	for(xCount=0;xCount<3;xCount++)
	{
		for(yCount=0;yCount<3;yCount++)
		{
			if(board[xStart+xCount][yStart+yCount] == num)
			{
				return false;
			}
		}
	}

	return true;
}

void sudoku::insertNumber()
{
	//Player Input Variables
	int row, col, num;

	//Read in values from player
	cout << "Choose Row #: ";
	cin >> row;

	cout << "Choose Col #: ";
	cin >> col;

	cout << "Enter number: ";
	cin >> num;

	//fixes numbers to simplify intput
	if(row > 3 && row < 7)
	{
		row++;
	}
	if(row > 6 && row <10 )
	{
		row+=2;
	}
	if(col > 3 && col < 7)
	{
		col++;
	}
	if(col > 6 && col <10 )
	{
		col+=2;
	}

	///Make Sure that values are valid
	if(checkAll(row, col, num))
	{
		board[row][col] = num;
	}
	else
	{
		cout << "Invalid row, collumn, or number!" << endl;
	}

	return;

}

void sudoku::removeNumber()
{
	int row, col;

	//Take User Input
	cout << "Enter Row #: ";
	cin >> row;
	cout << "Enter Column #: ";
	cin >> col;

	//Adjust for board offset
	if(row > 3 && row < 7)
	{
		row++;
	}
	if(row > 6 && row <10 )
	{
		row+=2;
	}
	if(col > 3 && col < 7)
	{
		col++;
	}
	if(col > 6 && col <10 )
	{
		col+=2;
	}

	//Return value back to default (0)
	board[row][col] = 0;

	return;
}

//Checks All Board Spaces to Determine if Game is Complete
bool sudoku::checkComplete()
{
	int x, y, count;

	for(x=1;x<12;x++)
	{
		for(y=1;y<12;y++)
		{
			if(board[x][y] == 0)
			{
				count++;
			}
		}
	}

	if(x > 0)
		return false;
	else
		return true;
}

//Main program
int main()
{

	//game finish condition
	bool solved;
	solved = false;

	//Create game class
	sudoku game;

	//Call makeBoard Function
	game.makeBoard();

	//Runs the Game
	while(!solved)
	{
		//Checks if game is complete
		solved = game.checkComplete();

		//Print Board
		game.printBoard();

		//Player Input
		int choice;

		cout << "Option #1: Insert a Number" << endl;
		cout << "Option #2: Remove a Number" << endl;
		cout << "Option #3: Quit" << endl;
		cout << "What would you like to do?: ";
		cin >> choice;
		cout << endl;

		if(choice == 1)
			game.insertNumber();
		else if(choice == 2)
			game.removeNumber();
		else if(choice == 3)
			solved = true;

		//Clears the screen so you dont have multiple boards at once.
		system("clear");
	}

	cout << "Game Complete!" << endl;

	return 0;
}
