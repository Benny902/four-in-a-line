/*
Final Assignment: Game creation
Author: Benny Shalom
*/

#define _CRT_SECURE_NO_WARNINGS	
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <math.h> // for sqrt() function

void FillSpaces(char *gameboard, int size); // fills spaces in the gameboard (array)
void PrintCurrentBoard(char *gameboard, int SIZE); // prints current gameboard status
void PrintLine(char a, int n); // recursive function that prints amount(depends on the input size) of lines after each line (helps to "Printcurrentboard" function)
void PrintNum(int col, int i); // recursive function that prints numbers under each column from 1 to Size (helps to "Printcurrentboard" function)
int PlayerInput(char *gameboard, int player, const char*, int SIZE); // inputs players col choice
int Winner(char *gameboard); // checks after each input if theres a winner (if reached to full board and no winner, its a tie)
int checkIf4Line(char *gameboard, int, int, int, int); // checks if theres a 4 in line (any line: straight, side, diag,)
int RowCheck(char *gameboard, int SIZE); // func to check 4 in a line in row
int ColCheck(char *gameboard,int SIZE); // func to check 4 in a line in col
int DiagonaLineCheck(char *gameboard,int SIZE); // func to check 4 in a line in diagonal

int main() {
    int size = 0;
	printf("\nHello, welcome to Four in a Line GAME \n");
	while (size <= 3) // loop (with main) untill size is bigger than 3
	{
        printf("Please Enter the board size you want: (must be 4 or higher)\n");
        scanf("%d", &size);
        if (size <= 3)
		    printf("\nError, number must be 4 or higher!.  Try again\n");
	}
	//if size>3 : continues
	const char *coin = "AB";
	char *gameboard = { 0 };
	int boardsize = size * size;
	gameboard = (char*)malloc(boardsize * sizeof(char)); // dynamic allocation
	if (gameboard == NULL) // check if allocation succeeded
	{
		printf("Error! memory cannot be allocated");
		exit(0);
	}
	FillSpaces(gameboard, boardsize); // filling the gameboard with spaces
	printf("\ninstructions to play: you need to get 4 coins in a line ( |  _  /  \\ ) \n");
	int i, finish = 0; // i= current player, finish = to check if there is a winner or a tie (1 for winner, 0 for tie)
	for (i = 0; i < boardsize && !finish; i++) //  loop to: printcurrentboard, input from player untill its good input,
	{
		PrintCurrentBoard(gameboard,size);
		while (!PlayerInput(gameboard, i % 2, coin,size))
		{
			PrintCurrentBoard(gameboard,size);
			puts("**This Col is full!**\n");
		}
		finish = Winner(gameboard); // after every GOOD input will check if theres a winner
	}
	PrintCurrentBoard(gameboard,size); // print last gameboard

	if (!finish) // if finish is still 0, theres no winners, its a Tie
	{
		puts("The Board is full which means we have a Tie!");
	}
	else // else someone won:
	{
		i--;
		printf("Player %d (coin %c) wins!\n", i % 2 + 1, coin[i % 2]); // prints the winner
	}
	free(gameboard); // free the dynamic allocated memory
	return 0;
}

void FillSpaces(char *gameboard, int size)
{
	int i = 0;
	for (i = 0;i < size;i++)
	{
		gameboard[i] = ' ';
	}
}

void PrintCurrentBoard(char *gameboard,int SIZE)
{
	int row, col;
	char a = '-';
	puts("\n   +*+*Four in a Line GAME*+*+\n");
	for (row = 0; row < SIZE; row++) 
	{
		printf(" ");
		for (col = 0; col < SIZE; col++) 
		{
			printf("| %c ", gameboard[SIZE * row + col]);
		}
		puts("|");
		PrintLine(a, SIZE); // recursive function to print exact under lines for each col
		printf("\n");
	}
	//puts("  1   2   3   4   5   6   7\n");
	printf("#: ");
	PrintNum(SIZE, 1); // recursive function to print exact Number for each col

	printf("\n\n");
}

void PrintLine(char a, int n) // recursive function to print exact under lines for each col
{
	if (n < 0)
		return;
	else
	{
		printf("%c%c%c%c", a, a, a, a); // per every col: 4 lines will be printed (all in same line: col*4)
		PrintLine(a, n - 1);
	}
}

void PrintNum(int col, int i) // recursive function to print exact Number for each col
{
	if (i > col)
		return;
	else
	{
		printf("%d   ", i); // print number under col for each col
		PrintNum(col, i + 1);
	}
}

int PlayerInput(char *gameboard, int player, const char *coin, int SIZE)
{
	int row, col = 0;
	printf("Player %d (%c):\nChoose column number to insert your coin: ", player + 1, coin[player]);

	for (;;) {
		if (1 != scanf("%d", &col) || col < 1 || col > SIZE) 
		{
			while (getchar() != '\n');
			puts("Coin fell outside the board! Try again.");
		}
		else {
			break;
		}
	}
	col--;

	for (row = SIZE - 1; row >= 0; row--) 
	{
		if (gameboard[SIZE * row + col] == ' ') 
		{
			gameboard[SIZE * row + col] = coin[player];
			return 1;
		}
	}
	return 0;
}

int Winner(char *gameboard)
{
	int size = sqrt(strlen(gameboard)); // size of strlen(gameboard) is size*size, but i need just size, so i get it with sqrt
	return (RowCheck(gameboard,size) || ColCheck(gameboard,size) || DiagonaLineCheck(gameboard,size));
}

int checkIf4Line(char *gameboard, int a, int b, int c, int d) 
{
	return (gameboard[a] != ' ' && gameboard[a] == gameboard[b] && gameboard[a] == gameboard[c] && gameboard[a] == gameboard[d]);
}

int RowCheck(char *gameboard, int SIZE)
{
	int row, col, i;
	const int w = 1; // w=wiedth

	for (row = 0; row < SIZE; row++) 
	{
		for (col = 0; col < SIZE - 3; col++) 
		{
			i = SIZE * row + col;
			if (checkIf4Line(gameboard, i, i + w, i + w * 2, i + w * 3)) 
			{
				return 1;
			}
		}
	}
	return 0;
}

int ColCheck(char *gameboard, int SIZE)
{
	int row, col, i;
	const int h = SIZE; // h = height

	for (row = 0; row < SIZE - 3; row++) 
	{
		for (col = 0; col < SIZE; col++) 
		{
			i = SIZE * row + col;
			if (checkIf4Line(gameboard, i, i + h, i + h * 2, i + h * 3))
			{
				return 1;
			}
		}
	}
	return 0;
}

int DiagonaLineCheck(char *gameboard, int SIZE)
{
	int row, col, i, count = 0;
	const int d_right = SIZE+1, d_left = SIZE+1; // diognal right and left

	for (row = 0; row < SIZE - 3; row++) 
	{
		for (col = 0; col < SIZE; col++) 
		{
			i = SIZE * row + col;
			if (count <= 3 && checkIf4Line(gameboard, i, i + d_left, i + d_left * 2, i + d_left * 3) || 
				count >= 3 && checkIf4Line(gameboard, i, i + d_right, i + d_right * 2, i + d_right * 3)) // same line
			{
				return 1;
			}
			count++;
		}
		count = 0;
	}
	return 0;
}
