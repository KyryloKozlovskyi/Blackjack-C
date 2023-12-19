#include"Functions.h"
#include<stdio.h> 
#include<stdlib.h>
#include<windows.h>


void Menu()
{
	int userInpt; //used to store user's choice

	//menu
	printf("**************** Welcome to Blackjack - C! ****************\n");
	printf("*                                                         *\n");
	printf("*                  1 - Start a new game                   *\n");
	printf("*                  2 - Load a saved game                  *\n");
	printf("*                  3 - Exit the game                      *\n");
	printf("*                                                         *\n");
	printf("***********************************************************\n");
	Sleep(1000);

	//read user input
	printf("Select an option from 1 - 3: ");
	scanf_s("%d", &userInpt); 

	switch (userInpt)
	{
	case 1: //start a new game
		StartNewGame();
		break;
	case 2: //load a game from the save file
		LoadGame();
		break;
	case 3: //exit the game
		ExitGame();
		break;
	}

}

void StartNewGame()
{
	int numPlayers;

	system("cls"); //clear previous output
	printf("Starting a new game...\n");
	Sleep(500); //sleep for 0.5 sec

	//read user input
	printf("Enter a number of players (The dealer and player - 1, 2, 3): ");
	scanf_s("%d", &numPlayers);
}

void LoadGame()
{
	system("cls"); //clear previous output
	printf("Loading a game...\n");
	Sleep(500); //sleep for 0.5 sec
}

void ExitGame()
{
	system("cls"); //clear previous output
	printf("Exiting the game...\n");
	Sleep(500); //sleep for 0.5 sec
	exit(0); //terminate program execution
}