/**************************************************************************
** Author: 		Luke Burris
** Description:	Tests the doMinion() function using my checkTrue function()
**************************************************************************/
#include "dominion.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>

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

int main(int argc, char** argv) {
    int r;
    int choice1;
    int choice2;
    // This is a real value
    int numPlayers = 2;
    int currentPlayer = 0;
    int otherPlayer = 1;
    
    int k[10] = {adventurer, council_room, feast, gardens, mine,
        remodel, smithy, village, baron, great_hall};

    struct gameState state;

    printf("\n\n");
    printFormatted("UNITTEST2 - doMinion()");
    /***************************************************************************************
    ** choice1 = 1. Check when player chooses to gain 2 coins
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
    choice2 = 0;
    state.coins = 0;
    state.discardCount[currentPlayer] = 0;

    // Call the function being tested;
    doMinion(currentPlayer, choice1, choice2, &state, 0);

    // Do tests
    printFormatted("SUBTEST 1 - choice1 = 1. Check for When Player Chooses to Gain 2 Coins.");
    checkTrue(state.numActions, 2, "Number of Actions Increase by 1.");
    checkTrue(state.coins, 2, "Coins Increase by 2."); // This should fail because of my bug
	/***************************************************************************************
    ** choice2 = 1. Check when player chooses to discard and redraw.
    ***************************************************************************************/
    // Standard Estate setup
    memset(&state, 23, sizeof(struct gameState));
    r = initializeGame(numPlayers, k, 618, &state);
    state.handCount[currentPlayer] = 5;
    for (int i = 0; i < state.handCount[currentPlayer]; i++) {
    	state.hand[currentPlayer][i] = estate; // Set all of the cards to estates
    }

    // Switch variables so test should pass
    choice1 = 0;
    choice2 = 1;
    state.coins = 0;
    state.discardCount[currentPlayer] = 0;
    state.handCount[otherPlayer] = 5;

    // Call the function being tested;
    doMinion(currentPlayer, choice1, choice2, &state, 0);

    // Do tests
    printFormatted("SUBTEST 2 - choice2 = 1. Check When Player Chooses to Discard.");
    checkTrue(state.handCount[currentPlayer], 4, "Current Player Hand Count Equals 4.");
    checkTrue(state.handCount[otherPlayer], 4, "Other Player Hand Count Equals 4."); // This should fail because of my bug

    return 0;
}