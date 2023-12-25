#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

// Prototypes for the functions

void menu();
void startNewGame();
void loadGame();
void exitGame();
void saveGame();
void initializeDeck(int numDecks);
void shuffleDeck(int numDecks);
void dealInitialCards(int numPlayers);
void printPlayerCards(int player);
void playerTurn(int player);
int calculateHandTotal(int player);
void hit(int player);
void findWinner();

#endif