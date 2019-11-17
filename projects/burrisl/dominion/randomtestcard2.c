/**************************************************************************
** Author:      Luke Burris
** Description: Tests the doMinion() function using my checkTrue function()
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

// Prints PASSED if true and FAILED if false. Alos prints the passed in description
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

    // Supply piles
    int k[10] = {adventurer, council_room, feast, gardens, minion, remodel, smithy, village, baron, great_hall};

    // Seed the random number generator
    srand(time(NULL));
 
    // Print out title of test
    printFormatted("RANDOM TEST 2 - doMinion()");

    // While loop variables
    int currIter = 0;
    int iterations = 10;

    while (currIter < iterations) {
        // Variable declarations
        int numCoinsBefore = 0;
        int handSizeBefore = 0;
        // Choice variables
        int choice1 = 0;
        int choice2 = 0;

        printf("** ITERATION %d **\n", currIter + 1);
        // Initialize the Game
        memset(&state, 23, sizeof(struct gameState));
        initializeGame(numPlayers, k, 618, &state);

        // Randomly set the size of the hand
        state.handCount[currentPlayer] = rand() % 10;

        // Add random cards to the hand
        for (int card = 0; card < state.handCount[currentPlayer]; card++) {
            state.hand[currentPlayer][card] = rand() % (treasure_map + 1);
        }

        printf("Hand Count Before: %d\n", state.handCount[currentPlayer]);
        // Gain a minion card
        gainCard(minion, &state, TO_HAND, currentPlayer);

        printf("Hand Count After: %d\n", state.handCount[currentPlayer]);

        // Get variable snapshots
        numCoinsBefore = state.coins;
        handSizeBefore = state.handCount[currentPlayer];

        choice1 = rand() % 2; // Get a random choice1
        choice2 = rand() % 2; // Get a random choice2

        // Call doMinion()
        doMinion(currentPlayer, choice1, choice2, &state, state.handCount[currentPlayer]);

        checkTrue(state.numActions, 2, "Number of Actions Equals 2");

        // Player chooses gain 2 coins
        if (choice1 > 0) {
            checkTrue(handSizeBefore - 1, state.handCount[currentPlayer], "Hand Size Decreased By 1");
            checkTrue(numCoinsBefore + 2, state.coins, "Coins Increased By 2");
        }

        currIter++; // Increment Iterator
    }

    printFormatted("RANDOM TEST 1 COMPLETED - doBaron()");

    return 0;
}