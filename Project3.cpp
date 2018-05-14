// Author: Joseph Fergen
// Date: 3/28/19
// Instructor: Dr.Thompson
// Description: Creating a connect 1030(4) game. A great amount of fun is bound to be had
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <stdio.h>
#include <string>
using namespace std;

enum Spaces {OPEN = '-', RED = 'O', BLUE = 'o'}; // Global enum to keep track of the spaces
const int NUM_COLS = 6; // Global number of columns will always be 6

void BasicInfo(); // Function that gives just the basic info at beginning of program
void WelcomeMsg(); // Function that gives user welcome message and instructions
void MakeBoard(Spaces arr[ ][NUM_COLS], int numRows); // Function to create the board
bool IsDone(Spaces arr[ ][NUM_COLS], int numRows, int colInput, int whosTurn, bool &keepGoing, int &numChars); // Function to check if there is a winner
void PrintBoard(Spaces arr[ ][NUM_COLS], int numRows, int &totalChars); // Function that prints the board out before and afer every turn

int main()
{
	int rows; // Variable to hold number of rows	
	int userCol = 1; // Where the user wants to put their piece
	bool gameOver = false; // Will change to false if there is a winner
	int turnToMove = 0; // Determines if user (0) or AI (1) turn to move. Starts with usert
	int numChars = 0; // Total number of characters placed

	srand(time(NULL)); // Seeding random number

	BasicInfo(); // Outputting my basic information

	WelcomeMsg(); // Outputting instructions and welcome message

	// Getting number of rows from user
	cout << "Enter the number of rows for the board (4-6 inclusive): " << endl;
	cin >> rows;

	// Making sure rows is between 4 and 6 inclusively
	while(rows < 4 || rows > 6)
	{
	cout << "That is an invalid number of rows. Please enter the number of rows again (4-6 inclusive): " << endl;
	cin >> rows;
	}

	Spaces Board[rows][NUM_COLS]; // Initializing a 2-D array that holds the board area

	// Initializes all of the array variables to '-' 
	cout << "Initializing game board..." << endl;	
	MakeBoard(Board, rows);

	// Prints the board
	PrintBoard(Board, rows, numChars);
	
	// Keeps going until there is a winner or no more room
	while(!gameOver)
//	while(!IsDone(Board, rows, userCol, turnToMove, gameOver))
	{
		int numReds = 0; // Number of reds in a row
	
		// Starting with user (REDS) turn
		if(turnToMove == 0)
		{
			cout << "RED MOVE: Enter column number to place RED disc (1-6 Inclusive): ";
			cin >> userCol;
			
			if(userCol > 0 && userCol < 7)
			{
				--userCol; // To fit the array
						
				// Place the marker and see if the game should continue
				IsDone(Board, rows, userCol, turnToMove, gameOver, numChars);
				
				
				// Print the board after placing the marker
				PrintBoard(Board, rows, numChars);

				++turnToMove; // Change to Ai	 
			}
			else
			{
				cout << "Invalid entry... Please try again." << endl << endl;
				userCol = -1;
			}
			
		}
		// AI turn
		else if (turnToMove == 1)
		{
			cout << "Outputting AI's turn..." << endl;
			userCol = (rand() % 6) + 1; // Random number between 1 and 6
			userCol--; // To fit the array

			// AI Logic, if 3 REDS in a row horizontally, put a BLUE
			for(int i = 0; i < rows; ++i)
			{
				for(int j = 0; j < NUM_COLS; ++j)
				{
				
					if(Board[i][j] == RED)
					{
						++numReds;
						if(numReds == 3)
						{
							// If the sapce after is not open, dont place a BLUE there
							if(Board[i][j + 1] = OPEN)
							{
								numReds = 0;
								break;
							}
							userCol = j + 1; // Place a blue 1 after the 3 REDS
						}
					}
				}
				numReds = 0;
			}

			// AI Logic, if 3 REDS in a row vertically, put a BLUE
			for(int i = 0; i < NUM_COLS; ++i)
			{
				for(int j = 0; j < rows; ++j)
				{
					if(Board[i][j] == RED)
					{
						++numReds;
						if(numReds == 3)
						{
							// If the space after is not open, dont place a BLUE there
							if(Board[i][j + 1] == OPEN)
							{
								numReds = 0;
								break;
							}
							userCol = j + 1; // Place a blue 1 after the 3 REDs
						}
					}
				}
				numReds = 0;
			}

			// Place the disc and see if game should continue
			IsDone(Board, rows, userCol, turnToMove, gameOver, numChars);
			
			// Print the updated board
			PrintBoard(Board, rows, numChars);
					
			--turnToMove; // Makes it User's turn
		}	
	}

	return 0;
}

// Basic information
void BasicInfo()
{
	cout <<"\t +----------------------------------------------+" << endl;
	cout <<"\t | Computer Science and Engineering             |" << endl;
	cout <<"\t | CSCE 1030 - Computer Science I               |" << endl;
	cout <<"\t | Joseph Fergen jpf0095 jpf0095@my.unt.edu     |" << endl;
	cout <<"\t +----------------------------------------------+" << endl << endl;

	return;
}

// Instructions
void WelcomeMsg()
{
	cout << "\t W e l c o m e   t o   1 0 3 0   C o n n e c t" << endl << endl;
	cout << "The user (RED) will start the game." << endl;
	cout << "------------------------------------------------------------------------" << endl;
	cout << "This program will set up a game board to play 1030 Connect using a board" << endl;
	cout << "where the rows are determined by the user to be between 4 and 6, inclus-" << endl;
	cout << "ively, but the number of columns is fixed at 6." << endl << endl;
	cout << "Then, the user (RED) will play against the computer (BLUE) to attempt to" << endl;
	cout << "connect four discs in a row, either horizontal or vertical, on the board" << endl;
	cout << "The user (RED) will start the game." << endl;
	cout << "------------------------------------------------------------------------" << endl << endl;

	return;
}

// Creating the board
void MakeBoard(Spaces arr[ ][NUM_COLS], int numRows)
{
	// Initializes every variable in the array to be '-'
	for (int i = 0; i < numRows; ++i)
	{
		for (int j = 0; j < NUM_COLS; ++j)
		{
			arr[i][j] = OPEN;
		}
	}
	
	return;
}

// Places the disc and then determines if there is a winner at that point
bool IsDone(Spaces arr[][NUM_COLS], int numRows, int colInput, int whosTurn, bool &isGameOver, int &numChars)
{
	int redHorizontalCounter = 0; // Number of red discs in line horizontally
	int blueHorizontalCounter = 0; // Number of blue discs in a line
	
	if(numChars >= (numRows * NUM_COLS))
	{
		isGameOver = true;
		cout << endl << "No more room. Game ends in a tie." << endl;
	}
	
	// Placing the disc in the correct spot	
	for(int i = numRows - 1; i > -1; --i)	
	{
		if(arr[i][colInput] == OPEN)
		{
			if(whosTurn == 0)
			{
				arr[i][colInput] = RED;
				numChars++;
				break;
			}
			else
			{
				arr[i][colInput] = BLUE;
				numChars++;
				break;
			}
		}
		else if(arr[0][colInput] != OPEN)
		{
			cout << "No more room in this column. You have lost your turn, sorry." << endl;
			break;
		}
	}

	// Finding to see if RED wins horizontally
	for(int i = 0;  i < numRows;  ++i)
	{
		for(int j = 0; j < NUM_COLS; j++)
		{
			if(arr[i][j] == RED)
			{
				redHorizontalCounter++;

				// If 4 RED in a row, they win
				if(redHorizontalCounter >= 4)
				{
					isGameOver = true;
					cout << endl << "RED has won!" << endl;
				}
			}
			else
			{
				redHorizontalCounter = 0;
			}
		}
		// New row
		redHorizontalCounter = 0;
	}
	
	// Finding to see if BLUE wins horizontally
	for(int i = 0; i < numRows; ++i)
	{
		for(int j = 0; j < NUM_COLS; j++)
		{
			if(arr[i][j] == BLUE)
			{
				blueHorizontalCounter++;
				
				// If 4 BLUE in a row, they win
				if(blueHorizontalCounter >= 4)
				{
					isGameOver = true;
					cout << endl << "BLUE has won!" << endl;
				}
			}
			
			else
			{
				blueHorizontalCounter = 0;
			}
		}
		// New row
		blueHorizontalCounter = 0;
	}

	// Finding to see if RED wins vertically
	for(int i = 0; i < NUM_COLS; i++)
	{
		for(int j = 0; j < numRows; j++)
		{
			if(arr[j][i] == RED)
			{
				redHorizontalCounter++;
				
				// if 4 RED in a row vertically, they win
				if(redHorizontalCounter >= 4)	
				{
					isGameOver = true;
					cout << endl << "RED has won!" << endl;
				}
			}
			else
			{
				redHorizontalCounter = 0;
			}
		}
		// New column
		redHorizontalCounter = 0;
	}

	// Finding to see if BLUE wins vertically
	for(int i = 0; i < NUM_COLS; i++)
	{
		for(int j = 0; j < numRows; j++)
		{
			if(arr[j][i] == BLUE)
			{
				blueHorizontalCounter++;
				
				// if 4 BLUE in a row vertically, they win
				if(blueHorizontalCounter >= 4)	
				{
					isGameOver = true;
					cout << endl << "BLUE has won!" << endl;
				}
			}
			else
			{
				blueHorizontalCounter = 0;
			}
		}
		// New column
		blueHorizontalCounter = 0;
	}


	return isGameOver;
}

// Prints out the board
void PrintBoard(Spaces arr[ ][NUM_COLS], int numRows, int &numChars)
{
	

	// Sets up column numbers and row letters
	char rowChar = 'A';
	cout << "    1 2 3 4 5 6  " << endl;
	cout << "  +------------+ " << endl;

	// Prints out the board and row numbers
	for (int i = 0; i < numRows; ++i)
	{
		cout << rowChar << " | ";
		for (int j = 0; j < NUM_COLS; ++j)
		{
			if(arr[i][j] != OPEN)
			{
				if(arr[i][j] == RED)
				{
					printf("\033[0;31;49m%c\033[0m", RED);
					cout << " ";
				}
				if(arr[i][j] == BLUE)
				{
					printf("\033[0;34;49m%c\033[0m",toupper(BLUE));
					cout << " ";
				}
			}
			else
			{
				cout << static_cast<char>(arr[i][j]) << " ";
			}
		}
		cout << "|";
		cout << endl;
		++rowChar;
	}

	cout << "  +------------+ " << endl;

	return;
} 
