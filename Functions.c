#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include "Functions.h"

// Const
#define MAX_DECKS 4
#define CARDS_PER_DECK 52
// Global variables
int deck[MAX_DECKS * CARDS_PER_DECK]; // Fixed-size array to store the deck

void menu()
{
    int userInpt; // Used to store user's choice

    // Menu
    printf("**************** Welcome to Blackjack - C! ****************\n");
    printf("*                                                         *\n");
    printf("*                  1 - Start a new game                   *\n");
    printf("*                  2 - Load a saved game                  *\n");
    printf("*                  3 - Exit the game                      *\n");
    printf("*                                                         *\n");
    printf("***********************************************************\n");
    // Sleep(1000);

    // Read user input
    printf("Select an option from 1 - 3: ");
    scanf_s("%d", &userInpt);

    switch (userInpt) {
    case 1: // Start a new game
        startNewGame();
        break;
    case 2: // Load a game from the save file
        loadGame();
        break;
    case 3: // Exit the game
        exitGame();
        break;
    }
}

void startNewGame()
{
    int numPlayers;
    int numDecks;

    system("cls"); // Clear previous output
    printf("Starting a new game...\n");
    // Sleep(500); // Sleep for 0.5 sec

    // Read user input
    printf("Enter a number of players (The dealer and player - 1, 2, 3): ");
    scanf_s("%d", &numPlayers);

    // Read player1 input
    printf("Enter a number of decks to shuffle (1, 2, 3, 4): ");
    scanf_s("%d", &numDecks);

    // Initialize the deck
    initializeDeck(numDecks);
    shuffleDeck(numDecks);

    // Deck validation
    //printf("1st - %d\n ", deck[0]);
    //printf("last - %d\n ", deck[207]);
    printf("Shuffled deck:\n");
    for (int i = 0; i < numDecks * CARDS_PER_DECK; i++) {
        printf("%d\n", deck[i]);
        printf("i = %d\n", i);
    }
}

void loadGame()
{
    system("cls"); // Clear previous output
    printf("Loading a game...\n");
    // Sleep(500); // Sleep for 0.5 sec
}

void exitGame()
{
    system("cls"); // Clear previous output
    printf("Exiting the game...\n");
    // Sleep(500); // Sleep for 0.5 sec
    exit(0); // Terminate program execution
}

// Function to populate decks(arrays of cards) with cards values
void initializeDeck(int numDecks)
{
    printf("Initializing the deck...\n");
    int cardIndex = 0;
    for (int deckNum = 0; deckNum < numDecks; deckNum++) {
        // Cards value 2 to 10
        for (int rank = 2; rank <= 10; rank++) {
            for (int suit = 1; suit <= 4; suit++) {
                deck[cardIndex++] = rank;
            }
        }

        // Face cards (Jack, Queen, King) - value of 10
        for (int rank = 11; rank <= 13; rank++) {
            for (int suit = 1; suit <= 4; suit++) {
                deck[cardIndex++] = 10;
            }
        }

        // Aces value 1 or 11
        for (int suit = 1; suit <= 4; suit++) {
            deck[cardIndex++] = 11;
        }
    }
}

// Function to shuffle the deck
void shuffleDeck(int numDecks)
{
    srand(time(NULL)); // seed the rand()
    printf("Shuffling the deck...\n");
    int totalCards = numDecks * CARDS_PER_DECK;
    for (int i = totalCards - 1; i > 0; i--) {
        int j = rand() % (i + 1);

        // Swap deck[i] and deck[j]
        int temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;
    }
}
