/**************************************************************************
** Author: 		Luke Burris
** Description:	Tests the doBaron() function using my checkTrue function()
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
    // Estate Variables
    int numOldEstatesInHand = 0;
    int estateSupply = 0;
    int numNewEstatesInHand = 0;

    int numOrigTotalCards = 0;
    int numCoinsBefore = 0;
    int numCoinsAfter = 0;
    int success = 0;
    // Choice variables
    int choice1 = 0;
    int choice2 = 0;
    int choice3 = 0;
    // Supply piles
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};

    // Seed the random number generator
    srand(time(NULL));
    // Initialize the Game
    memset(&state, 23, sizeof(struct gameState));
    initializeGame(numPlayers, k, 618, &state);
    // Print out title of test
    printFormatted("RANDOM TEST 1 - doBaron()");

    // While loop variables
    int currIter = 0;
    int iterations = 10;

    while (currIter < iterations) {
        // Randomly set the size of the hand
        state.handCount[currentPlayer] = rand() % 10;

        // Add random cards to the hand
        for (int card = 0; card < state.handCount[currentPlayer]; card++) {
            state.hand[currentPlayer][card] = rand() % (treasure_map + 1);
        }

        // Gain a baron card
        gainCard(baron, &state, TO_HAND, currentPlayer);

        // Check how many estate cards are in the player's hand
        for (int card = 0; card < numHandCards(&state); card++) {
            if (handCard(card, &state) == estate) {
                numOldEstatesInHand++;
            }
        }

        numOrigTotalCards = fullDeckCount(currentPlayer, &state);
        numCoinsBefore = updateCoins(currentPlayer, &state, 0); // Last parameter is bonus
        estateSupply = supplyCount(estate, &state);

        choice1 = rand() % 2; // Get a random choice1
        // Play the baron card
        success = playCard(numHandCards(&state) - 1, choice1, choice2, choice3, &state);
        numCoinsAfter = updateCoins(currentPlayer, &state, 0);

        checkTrue(success, 0, "Check if Card was Played Successfully");
        checkTrue(state.numBuys, 2, "Check if numBuys == 2");

        // Check how many estate cards are in the player's hand
        for (int card = 0; card < numHandCards(&state); card++) {
            if (handCard(card, &state) == estate) {
                numNewEstatesInHand++;
            }
        }

        endTurn(&state);
        currIter++; // Increment Iterator
    }

    printFormatted("RANDOM TEST 1 COMPLETED - doBaron()");

    return 0;
}