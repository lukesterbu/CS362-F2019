/**************************************************************************
** Author:      Luke Burris
** Description: Tests the doTribute() function using my checkTrue function()
**************************************************************************/
#include "dominion.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

// Makes certain function calls easier to understand
#define TO_DISCARD 0
#define TO_DECK 1
#define TO_HAND 2

// Prints out the description formatted with asterisks around it
void printFormatted(char* desc) {
    printf("**************************************************************\n");
    printf("%s\n", desc);
    printf("**************************************************************\n");
}

// Prints PASSED if true and FAILED if false. Also prints the passed in description
void checkTrue(int x, int y, char* desc) {
    if (x == y) {
        printf("PASSED - %s\n", desc);
    }
    else {
        printf("FAILED - %s\n", desc);
    }
}

int main() {
    struct gameState state;
    int numPlayers = 2; // May need to randomize this
    int currentPlayer = 0; // May need to randomize this
    int otherPlayer = 1;

    // Supply piles
    int k[10] = {adventurer, council_room, feast, tribute, minion, remodel, smithy, village, baron, great_hall};

    // Seed the random number generator
    srand(time(NULL));
 
    // Print out title of test
    printFormatted("RANDOM TEST 3 - doTribute()");

    // While loop variables
    int currIter = 0;
    int iterations = 10;

    while (currIter < iterations) {
        // Variable declarations
        int numCoinsBefore = 0;
        int handSizeBefore = 0;
        int numActionsBefore = 0;
        int numTreasureCards = 0;
        int numVictoryCards = 0;
        int numActionCards = 0;
        int tributeRevealedCards[2];

        printf("** ITERATION %d **\n", currIter + 1);
        // Initialize the Game
        memset(&state, 23, sizeof(struct gameState));
        initializeGame(numPlayers, k, 618, &state);

        // Randomly set the size of the hand
        state.handCount[currentPlayer] = rand() % 10;
        state.handCount[otherPlayer] = rand() % 10;

        // Add random cards to the hand
        for (int card = 0; card < state.handCount[currentPlayer]; card++) {
            state.hand[currentPlayer][card] = rand() % (treasure_map + 1);
        }

        // Gain a tribute card
        gainCard(tribute, &state, TO_HAND, currentPlayer);

        for (int card = 0; card < 2; card++) {
            tributeRevealedCards[card] = rand() % (treasure_map + 1);
        }

        // Get variable snapshots
        numActionsBefore = state.numActions;
        numCoinsBefore = state.coins;
        handSizeBefore = state.handCount[currentPlayer];

        // Call doTribute()
        doTribute(currentPlayer, otherPlayer, tributeRevealedCards, &state);

        int dupFlag = 1;
        int card = 0;
        while (dupFlag == 1 && card < 2) {
            if (tributeRevealedCards[0] == tributeRevealedCards[1]) {
                dupFlag = 0;
            }
            // Treasure Card
            if (tributeRevealedCards[card] == copper || tributeRevealedCards[card] == silver || tributeRevealedCards[card] == gold) {
                numTreasureCards++;
            }
            // Victory Card
            else if (tributeRevealedCards[card] == estate || tributeRevealedCards[card] == duchy || tributeRevealedCards[card] == province || tributeRevealedCards[card] == gardens || tributeRevealedCards[card] == great_hall) {
                numVictoryCards++;
            }
            // Action Card
            else {
                numActionCards++;
            }
            card++;
        }

        printf("Action Cards: %d\n", numActionCards);
        printf("Actions Before: %d\n", numActionsBefore);
        printf("Actions After: %d\n", state.numActions);

        checkTrue(numActionsBefore + (2 * numActionCards), state.numActions, "Actions Are Correct");
        checkTrue(numCoinsBefore + (2 * numTreasureCards), state.coins, "Coins Are Correct");
        checkTrue(handSizeBefore + (2 * numVictoryCards), state.handCount[currentPlayer], "Hand Count is Correct");

        currIter++; // Increment Iterator
    }

    printFormatted("RANDOM TEST 3 COMPLETED - doTribute()");

    return 0;
}