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

    // Supply piles
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};

    // Seed the random number generator
    srand(time(NULL));
 
    // Print out title of test
    printFormatted("RANDOM TEST 1 - doBaron()");

    // While loop variables
    int currIter = 0;
    int iterations = 10;

    while (currIter < iterations) {
        // Estate Variables
        int numOldEstatesInHand = 0;
        int estateSupply = 0;
        int numNewEstatesInHand = 0;
        int numOrigTotalCards = 0;
        int numCoinsBefore = 0;
        // Choice variables
        int choice1 = 0;

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

        // Gain a baron card
        gainCard(baron, &state, TO_HAND, currentPlayer);

        // Check how many estate cards are in the player's hand
        for (int card = 0; card < numHandCards(&state); card++) {
            if (handCard(card, &state) == estate) {
                numOldEstatesInHand++;
            }
        }

        numOrigTotalCards = fullDeckCount(currentPlayer, baron, &state);
        numCoinsBefore = state.coins;
        estateSupply = supplyCount(estate, &state);

        choice1 = rand() % 2; // Get a random choice1

        // Call doBaron()
        doBaron(currentPlayer, choice1, &state);

        checkTrue(state.numBuys, 2, "Number of Buys Equals 2"); // This should fail every time because of my bug

        // Check how many estate cards are in the player's hand
        for (int card = 0; card < numHandCards(&state); card++) {
            if (handCard(card, &state) == estate) {
                numNewEstatesInHand++;
            }
        }

        // Player chooses to discard an estate and has one in their hand
        if (choice1 > 0 && numOldEstatesInHand > 0) {
            checkTrue(numOldEstatesInHand - 1, numNewEstatesInHand, "Estate was Discarded");
            checkTrue(numCoinsBefore + 4, state.coins, "Coins Incremented By 4");
        }
        // Player chooses to discard an estate but doesn't have any in their hand
        // OR
        // Player did not want to discard an estate
        else {
            checkTrue(estateSupply - 1, supplyCount(estate, &state), "Estate Supply Decremented");
            checkTrue(numCoinsBefore, state.coins, "Coins are the Same After Gaining an Estate");
        }

        currIter++; // Increment Iterator
    }

    printFormatted("RANDOM TEST 1 COMPLETED - doBaron()");

    return 0;
}