/**************************************************************************
** Author: 		Luke Burris
** Description:	Tests the doBaron() function using my checkTrue function()
**************************************************************************/
#include "dominion.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

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

int main () {
    int r;
    int choice1;
    // This is a real value
    int numPlayers = 2;
    int currentPlayer = 0;
    
    int k[10] = {adventurer, council_room, feast, gardens, mine,
        remodel, smithy, village, baron, great_hall};

    struct gameState state;

    printFormatted("UNITTEST1 - doBaron()");
    /***************************************************************************************
    ** Test to see if an estate card is found in the hand when choice1 > 0
    ***************************************************************************************/
    // Standard Estate setup
    memset(&state, 23, sizeof(struct gameState));
    r = initializeGame(numPlayers, k, 618, &state);
    state.handCount[currentPlayer] = 5;
    for (int i = 0; i < state.handCount[currentPlayer]; i++) {
    	state.hand[currentPlayer][i] = estate; // Set all of the cards to estates
    }
    // Switch variables so test should pass
    choice1 = 1;
    state.coins = 0;
    state.discardCount[currentPlayer] = 0;

    // Call the function being tested;
    doBaron(currentPlayer, choice1, &state);

    // Do tests
    printFormatted("SUBTEST 1 - choice1 = 1. Check for Estate Card in Hand With All Estate Hand.");
    checkTrue(state.numBuys, 2, "Buys Increased By 1."); // This will Fail because of my bug
    checkTrue(state.coins, 4, "Coins Increased By 4.");
    checkTrue(state.discardCount[currentPlayer], 1, "Discard Count Increased By 1.");
    checkTrue(state.handCount[currentPlayer], 4, "Hand Count Decreased By 1.");

    /***************************************************************************************
    ** Test to see if an estate card is found in the hand when choice1 > 0.
    ** This will find the bug isnce the first card is ignored because of my bug with the
    ** iterator in doBaron.
    ***************************************************************************************/
    // Standard Copper setup
    memset(&state, 23, sizeof(struct gameState));
    r = initializeGame(numPlayers, k, 618, &state);
    state.handCount[currentPlayer] = 5;
    for (int i = 0; i < state.handCount[currentPlayer]; i++) {
    	state.hand[currentPlayer][i] = copper; // Set all of the cards to estates
    }
    state.hand[currentPlayer][0] = estate;
    // Switch variables so test should pass
    choice1 = 1;
    state.coins = 0;
    state.discardCount[currentPlayer] = 0;

    // Call the function being tested;
    doBaron(currentPlayer, choice1, &state);

    // Do tests
    printFormatted("SUBTEST 2 - choice1 = 1. Check for Estate at Index 0 of Hand.");
    checkTrue(state.coins, 4, "Coins Increased By 4"); // This will fail because of my bug
    checkTrue(state.discardCount[currentPlayer], 1, "Discard Count Increased By 1.");
    checkTrue(state.handCount[currentPlayer], 4, "Hand Count Decreased By 1."); // This will fail because of my bug

    /***************************************************************************************
    ** Test to see if an estate card is not found in the hand when choice 1 > 0
    ***************************************************************************************/
    // Standard Copper setup
    memset(&state, 23, sizeof(struct gameState));
    r = initializeGame(numPlayers, k, 618, &state);
    state.handCount[currentPlayer] = 5;
    for (int i = 0; i < state.handCount[currentPlayer]; i++) {
    	state.hand[currentPlayer][i] = copper;
    }

    // Switch variables so test should pass
    choice1 = 1;
    state.supplyCount[estate] = 1; // Set to 1 since it will be decremented and then checked if = 0
    state.discardCount[currentPlayer] = 0;

    // Call the function being tested;
    doBaron(currentPlayer, choice1, &state);

    // Do tests
    printFormatted("SUBTEST 3 - choice1 = 1. No Estate Card Found in Hand.");
    checkTrue(state.supplyCount[estate], 0, "Estate Supply decreased by 1."); // Should be 0
    checkTrue(state.discardCount[currentPlayer], 1, "Discard Count Increased by 1."); // Should be 1

    /***************************************************************************************
    ** Test to see if an estate card is not found in the hand when choice1 > 0
    ***************************************************************************************/
    // Standard Copper setup
    memset(&state, 23, sizeof(struct gameState));
    r = initializeGame(numPlayers, k, 618, &state);
    state.handCount[currentPlayer] = 5;
    for (int i = 0; i < state.handCount[currentPlayer]; i++) {
    	state.hand[currentPlayer][i] = copper;
    }
   	// Switch variables so test should pass
    choice1 = 0;
    state.supplyCount[estate] = 1; // Set to 1 since it will be decremented and then checked if = 0
    state.discardCount[currentPlayer] = 0;

        // Call the function being tested;
    doBaron(currentPlayer, choice1, &state);

    // Do tests
    printFormatted("SUBTEST 4 - choice1 = 0.");
    checkTrue(state.supplyCount[estate], 0, "Estate Supply decreased by 1."); // Should be 0
    checkTrue(state.discardCount[currentPlayer], 1, "Discard Count Increased by 1."); // Should be 1

    return 0;
}