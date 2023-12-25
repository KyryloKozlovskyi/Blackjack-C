#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include "Functions.h"

// Const
#define MAX_DECKS 4
#define CARDS_PER_DECK 52
#define MAX_PLAYERS 4 // 3 players + dealer
// Global variables
int deck[MAX_DECKS * CARDS_PER_DECK]; // Fixed-size array to store the deck
int playerHands[MAX_PLAYERS][20]; // last plyaer is the dealer
int playerBusted[MAX_PLAYERS][1]; // players with the blackjack
int numPlayers = 0;
int numDecks = 0;
int lastUsedCard = 0;
int dealerHasBlackjack = 0; // Blackjack check

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

// Function to deal initial 2 cards to all players
void dealInitialCards(int numPlayers)
{
    printf("Dealing initial cards...\n");
    system("cls");

    // Deal two cards to each player and the dealer
    for (int i = 0; i < 2; i++) {
        for (int player = 0; player <= numPlayers; player++) {
            // Assign a card to a player
            int card = deck[player * 2 + i];
            lastUsedCard = player * 2 + i;
            playerHands[player][i] = card;
        }
    }

    // Print the dealer's hand
    printf("The dealer has: %d and a hole card\n", playerHands[numPlayers][0]);

    // Dealer blackjack check
    if (playerHands[numPlayers][0] == 10) {
        printf("The dealer peeks at his hole card\n");
        if (playerHands[numPlayers][1] == 11) {
            printf("The dealer has a Blackjack!\nDealer's hand: %d %d\n",
                playerHands[numPlayers][0], playerHands[numPlayers][1]);
            dealerHasBlackjack = 1;
        }
    }
    else if (playerHands[numPlayers][0] == 11) {
        printf("The dealer peeks at his hole card\n");
        if (playerHands[numPlayers][1] == 10) {
            printf("The dealer has a Blackjack!\nDealer's hand: %d %d\n",
                playerHands[numPlayers][0], playerHands[numPlayers][1]);
            dealerHasBlackjack = 1;
        }
    }
}

// Function to print player's cards
void printPlayerCards(int player)
{
    if (player == numPlayers) {
        printf("Dealer's cards: ");
    }
    else {
        printf("Player %d cards: ", player + 1);
    }

    for (int card = 0; card < 20;
        card++) // 20 - max number of cards in player's hand
    {
        if (playerHands[player][card] >= 1 && playerHands[player][card] <= 11) {
            printf("%d ", playerHands[player][card]);
        }
        else {
            break;
        }
    }
    printf("\n");
}

void playerTurn(int player) // player turn + hit() call
{
    int choice;

    do {
        printf("\n***** Player %d turn *****\n", player + 1);
        printPlayerCards(player);
        printf("Choose an option (1 - Stand, 2 - Hit, 3 - Save and Exit)\n");
        printf("Your choice: ");
        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
            printf("Player %d stands.\n", player + 1);
            printf("%d - hand total\n", calculateHandTotal(player));
            // printPlayerCards(player);
            printf("\n");
            break;
        case 2:
            printf("Player %d hits.\n", player + 1);
            hit(player);
            printf("\n");
            break;
        case 3:
            saveGame();
            break;
        default:
            printf("Invalid choice. Try again.\n");
            printf("\n");
        }

    } while (choice != 1 && choice != 2);
}

// Checks if the hand is soft 17
int isSoft17()
{
    // Check if there is an ace and any number of cards totaling six points in the
    // hand
    return (playerHands[numPlayers][1] == 11)
        && (calculateHandTotal(numPlayers) == 17);
}

// Function to calculate total points in the hand. Returns points total for the
// player
int calculateHandTotal(int player)
{
    int total = 0;
    int numAces = 0;

    // Iterate over the cards in the player's hand
    for (int i = 0; i < 20; ++i) {
        int cardValue = playerHands[player][i];

        // Track the number of aces in the hand
        if (cardValue == 11) {
            numAces++;
        }

        total += cardValue;
    }

    // The Ace is always valued at 11 unless that would result in the hand going
    // over 21, in which case it is valued as 1.
    while (total > 21 && numAces > 0) {
        total -= 10; // ace = 1
        numAces--;
    }
    return total;
}

void dealerTurn()
{
    printf("\n***** Dealer turn *****\n");

    // Show the hole card
    printf("Dealer reveals the hole card: %d\n", playerHands[numPlayers][1]);

    // Find the last card index to add an additional card
    int cardIndex;
    for (cardIndex = 0; cardIndex < 20; ++cardIndex) {
        if (playerHands[numPlayers][cardIndex] == 0) {
            break;
        }
    }

    // If hand total is less than 16, the dealer will draw another card
    while (calculateHandTotal(numPlayers) <= 16) {
        // Draw a card for the dealer
        int card = deck[lastUsedCard++];
        playerHands[numPlayers][cardIndex++] = card;
        printf("Dealer draws a card: %d\n", card);

        if (calculateHandTotal(numPlayers) > 21) {
            printf("Dealer is BUSTED!\n");
            playerBusted[numPlayers][0] = 1; // keeps track of busted players
        }
    }

    // Check for a soft 17 and draw another card
    if (isSoft17()) {
        int card = deck[lastUsedCard++];
        playerHands[numPlayers][cardIndex++] = card;
        printf("Dealer draws a card (Soft 17): %d\n", card);

        if (calculateHandTotal(numPlayers) > 21) {
            printf("Dealer is BUSTED!\n");
            playerBusted[numPlayers][0] = 1; // keeps track of busted players
        }
    }

    // Print the dealer's hand
    printPlayerCards(numPlayers);
    printf("%d - hand total\n", calculateHandTotal(numPlayers));
}

// Hit function
void hit(int player)
{
    // Find the first 0 in the hand (0 means empty)
    int cardIndex; // first empty slot in the hand
    for (cardIndex = 0; cardIndex < 20; ++cardIndex) {
        if (playerHands[player][cardIndex] == 0) {
            break;
        }
    }

    // Draw a card for the player
    int card = deck[lastUsedCard++];
    // printf("%d - Last used card\n", lastUsedCard);
    playerHands[player][cardIndex] = card;

    printf("Player %d draws a card: %d\n", player + 1, card);
    printPlayerCards(player);
    printf("%d - hand total\n", calculateHandTotal(player));
    // Check if the player is busted
    if (calculateHandTotal(player) > 21) {
        printf("Player %d BUSTED!\n", player + 1);
        playerBusted[player][0] = 1; // keeps track of busted players
    }
}

void findWinner()
{
    int allPlayerTotal[MAX_PLAYERS][1];
    int highestTotalPlayerIndex = 0;
    int numberOfCards[MAX_PLAYERS][1];

    printf("\nDetermining a winner...\n");

    // Calculate total for all players including the dealer
    for (int player = 0; player <= numPlayers; player++) {
        allPlayerTotal[player][0] = calculateHandTotal(player);
    }

    // Calculate the number of cards for all players including the dealer
    for (int player = 0; player <= numPlayers; player++) {
        // Count the number of cards for each player
        int numCards = 0;
        for (int cardIndex = 0; cardIndex < 20; cardIndex++) {
            if (playerHands[player][cardIndex] != 0) {
                numCards++;
            }
            else {
                break;
            }
        }
        numberOfCards[player][0] = numCards;
    }

    // printf("Highest total player index %d\n", highestTotalPlayerIndex);

    // If the dealer does have a blackjack, then all players will lose, unless the
    // player also has a blackjack, which will result in a tie.
    if (dealerHasBlackjack) {
        printf("The dealer has a Blackjack!\nDealer's hand: %d %d\n",
            playerHands[numPlayers][0], playerHands[numPlayers][1]);

        for (int player = 0; player < numPlayers; player++) {
            if (calculateHandTotal(player) == 21 && playerHands[player][2] == 0) {
                // playerHasBlackjack[player][0] = 1;
                printf("Player %d also has a Blackjack! It's a TIE!\n", player + 1);
            }
            else {
                printf("Dealer WINS!\n");
            }
        }
    }

    // If the dealer goes over 21 points (BUSTED), then any player who didn't
    // already bust will win.
    if (playerBusted[numPlayers][0] == 1) {
        for (int player = 0; player < numPlayers; player++) {
            if (playerBusted[player][0] != 1) {
                printf("Player %d WINS!\n", player + 1);
            }
        }
    }

    // If the dealer does not bust, then the higher point total between the player
    // and dealer will win
    if (playerBusted[numPlayers][0] != 1) {
        int highestTotalPlayerIndex = 0;

        // Find the highest total player index
        for (int player = 0; player <= numPlayers; player++) {
            if (allPlayerTotal[player][0] > allPlayerTotal[highestTotalPlayerIndex][0]
                && playerBusted[player][0] != 1) {
                highestTotalPlayerIndex = player;
            }
        }

        // printf("Highest total player index %d\n", highestTotalPlayerIndex);

        // Check for a tie in the higher total
        for (int player = 0; player <= numPlayers; player++) {
            if (player != highestTotalPlayerIndex
                && allPlayerTotal[player][0]
                == allPlayerTotal[highestTotalPlayerIndex][0]) {
                // Compare the number of cards to break the tie
                if (numberOfCards[player][0]
        > numberOfCards[highestTotalPlayerIndex][0]) {
                    highestTotalPlayerIndex = player;
                }
            }
        }
        if (highestTotalPlayerIndex == numPlayers) {
            printf("Dealer WINS!\n");
        }
        else {
            printf("Player %d WINS!\n", highestTotalPlayerIndex + 1);
        }
    }
}

void startNewGame()
{
    system("cls"); // Clear previous output
    printf("Starting a new game...\n");
    // Sleep(500); // Sleep for 0.5 sec

    // Read user input
    printf("Enter a number of players (The dealer and player - 1, 2, 3): ");
    scanf_s("%d", &numPlayers);

    // Read player1 input
    printf("Enter a number of decks to shuffle (1, 2, 3, 4): ");
    scanf_s("%d", &numDecks);
    system("cls");

    // Initialize the deck
    initializeDeck(numDecks);
    shuffleDeck(numDecks);
    system("cls");
    dealInitialCards(numPlayers);

    // Player turn loop
    for (int player = 0; player <= numPlayers - 1; player++) {
        playerTurn(player);
    }
    dealerTurn();
    findWinner();

    /*
    for (int player = 0; player <= numPlayers; player++) {
        printf("Busted players: player %d - %d\n", player,
    playerBusted[player][0]);
    }
    */
}

void saveGame() {
    FILE* file; // File pointer
    fopen_s(&file, "saveFile.txt", "w"); // Open file for writing

    if (file != NULL) {
        // Save game state (all variables)
        fprintf(file, "%d\n", numPlayers); // Used for loops
        fprintf(file, "%d\n", numDecks); // Used for loops
        fprintf(file, "%d\n", lastUsedCard); // Used for loops
        fprintf(file, "%d\n", dealerHasBlackjack); // Used for loops

        // Save the deck
        for (int i = 0; i < MAX_DECKS * CARDS_PER_DECK; i++) {
            fprintf(file, "%d ", deck[i]);
        }
        fprintf(file, "\n");

        // Save player hands
        for (int player = 0; player <= numPlayers; player++) {
            for (int cardIndex = 0; cardIndex < 20; cardIndex++) {
                fprintf(file, "%d ", playerHands[player][cardIndex]);
            }
            fprintf(file, "\n");
        }

        // Save busted players
        for (int player = 0; player <= numPlayers; player++) {
            fprintf(file, "%d\n", playerBusted[player][0]);
        }

        fclose(file);
        printf("Game saved successfully!\n");
    }
    else {
        printf("Error saving the game.\n");
    }
    exitGame();
}

// Loads the saved game status into the varibles
void loadGame()
{
    FILE* file;
    fopen_s(&file, "saveFile.txt", "r");

    if (file != NULL) {
        // Load game state
        fscanf_s(file, "%d", &numPlayers);
        fscanf_s(file, "%d", &numDecks);
        fscanf_s(file, "%d", &lastUsedCard);
        fscanf_s(file, "%d", &dealerHasBlackjack);

        // Load the deck
        for (int i = 0; i < MAX_DECKS * CARDS_PER_DECK; i++) {
            fscanf_s(file, "%d", &deck[i]);
        }

        // Load player hands
        for (int player = 0; player <= numPlayers; player++) {
            for (int cardIndex = 0; cardIndex < 20; cardIndex++) {
                fscanf_s(file, "%d", &playerHands[player][cardIndex]);
            }
        }

        // Load busted players 
        for (int player = 0; player <= numPlayers; player++) {
            fscanf_s(file, "%d", &playerBusted[player][0]);
        }

        fclose(file);
        printf("Game loaded successfully!\n");

        // Continue the game from the loaded state
        dealInitialCards(numPlayers);

        // Player turn loop
        for (int player = 0; player <= numPlayers - 1; player++) {
            playerTurn(player);
        }
        dealerTurn();
        findWinner();
    }
    else {
        printf("Error loading the game.\n");
    }
}