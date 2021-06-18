#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define USER_TOKEN 'x'
#define COMPUTER_TOKEN 'o'

// print the play board on the screen
void printBoard(char board[9])
{
	printf("\n\n\t\t|%c|%c|%c|\n", board[0], board[1], board[2]);
	printf("\t\t|%c|%c|%c|\n", board[3], board[4], board[5]);
	printf("\t\t|%c|%c|%c|\n\n", board[6], board[7], board[8]);
}

void userRound(char *board)
{
	int choice;
	// ask the user to choose a box and verify if it's empty
	do
	{
		printf("Please, enter a number\n");
		scanf("%d", &choice);
		choice %= 9;

	}
	while (*(board+choice) != '_' && choice > 0);

	// fill the chosen box with the user token
	*(board+choice) = USER_TOKEN;
}

void computerRound(char *board)
{
	int choice;
	// randomly generates a box and verify if it's empty
	do
	{
		srand(time(NULL));
		choice = rand() % 9;
	}
	while (*(board+choice) != '_');
	
	// fill the chosen box with the computer token
	*(board+choice) = COMPUTER_TOKEN;
}

int checkVictory(char *board)
{
	// Check if there is 3 identic tokens on a winning combination
	// Winning combinations => 0 1 2 , 3 4 5 , 6 7 8 , 0 3 6 , 1 4 7 , 2 5 8 , 0 4 8 , 2 4 6

	if ( *(board+0) != '_' && *(board+0) == *(board+1) && *(board+1)  == *(board+2) )
	{
		if ( *(board+0) == USER_TOKEN)
			return 0;
		else
			return 1;
	}

	if ( *(board+3) != '_' && *(board+3) == *(board+4) && *(board+4)  == *(board+5) )
	{
		if ( *(board+3) == USER_TOKEN)
			return 0;
		else
			return 1;
	}

	if ( *(board+6) != '_' && *(board+6) == *(board+7) && *(board+7)  == *(board+8) )
	{
		if ( *(board+6) == USER_TOKEN)
			return 0;
		else
			return 1;
	}

	if ( *(board+0) != '_' && *(board+0) == *(board+3) && *(board+3)  == *(board+6) )
	{
		if ( *(board+0) == USER_TOKEN)
			return 0;
		else
			return 1;
	}


	if ( *(board+1) != '_' && *(board+1) == *(board+4) && *(board+4)  == *(board+7) )
	{
		if ( *(board+1) == USER_TOKEN)
			return 0;
		else
			return 1;
	}
	
	if ( *(board+2) != '_' && *(board+2) == *(board+5) && *(board+5)  == *(board+8) )
	{
		if ( *(board+2) == USER_TOKEN)
			return 0;
		else
			return 1;

	}

	if ( *(board+2) != '_' && *(board+0) == *(board+4) && *(board+4)  == *(board+8) )
	{
		if ( *(board+2) == USER_TOKEN)
			return 0;
		else
			return 1;
	}
	
	if ( *(board+2) != '_' && *(board+2) == *(board+4) && *(board+4)  == *(board+6) )
	{
		if ( *(board+2) == USER_TOKEN)
			return 0;
		else
			return 1;
	}

	return -1;
}

int play()
{
	int strikes = 0, firstPlayer;
	char board[9] = {'_','_','_','_','_','_','_','_','_'};

	printBoard(board);

	// choose randomly who begins
	srand(time(NULL));
	firstPlayer = rand() % 2;
	
	printf("%s starts!\n", firstPlayer == 0 ? "User" : "Computer");

	while (1)
	{

		if (firstPlayer == 0)
		{
			userRound(&board[0]);
			printBoard(board);
		} 
		else {
			computerRound(&board[0]);
			printBoard(board);
		}

		// if there is no more available boxes on the board
		if (strikes >= 4)
		{
			// if user wins
			if (checkVictory(&board[0]) == 0)
			{
				return 0;			
			}

			// if computer wins
			else if (checkVictory(&board[0]) == 1)
			{
				return 1;
			}

			// if nobody wins
			else
			{
				return -1;
			}
		}

		if (firstPlayer == 0)
		{
			computerRound(&board[0]);
			printBoard(board);
		} 
		else {
			userRound(&board[0]);
			printBoard(board);
		}

		// if user wins
		if (checkVictory(&board[0]) == 0)
		{
			return 0;
		}

		// if computer wins	
		if (checkVictory(&board[0]) == 1)
		{
			return 1;
		}

		strikes++;
	}
}

int main()
{
	int winner = play();
	printf("\n%s wins!\n", winner == 0 ? "User" : "Computer" );	
	return 0;
}
