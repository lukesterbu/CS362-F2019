/**************************************************************************
** Author: 		Luke Burris
** Description:	Tests the doMine() function using my checkTrue function()
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
    printFormatted("UNITTEST5 - doMine()");
	
    /***************************************************************************************
    ** state->hand[currentPlayer[choice1] < copper]
    ***************************************************************************************/
    // Standard Curse setup
    memset(&state, 23, sizeof(struct gameState));
    r = initializeGame(numPlayers, k, 618, &state);
    state.handCount[currentPlayer] = 5;
    for (int i = 0; i < state.handCount[currentPlayer]; i++) {
    	state.hand[currentPlayer][i] = curse; // Set all of the cards to curse
    }

    // Switch variables so test should pass
    choice1 = 0;
    choice2 = 3;
    state.coins = 0;
    state.hand[currentPlayer][choice1] = -100;

    // Do tests
    printFormatted("SUBTEST 1 - state->hand[currentPlayer][choice1] < copper.");
    checkTrue(doMine(currentPlayer, choice1, choice2, &state, 0), -1, "Should Return -1.");
	
    /***************************************************************************************
    ** state->hand[currentPlayer][choice1] > gold]
    ***************************************************************************************/
    // Standard Province setup
    memset(&state, 23, sizeof(struct gameState));
    r = initializeGame(numPlayers, k, 618, &state);
    state.handCount[currentPlayer] = 5;
    for (int i = 0; i < state.handCount[currentPlayer]; i++) {
    	state.hand[currentPlayer][i] = province; // Set all of the cards to province
    }

    // Switch variables so test should pass
    choice1 = 0;
    choice2 = 3;
    state.coins = 0;
    state.hand[currentPlayer][choice1] = 100;

    // Do tests
    printFormatted("SUBTEST 2 - state->hand[currentPlayer][choice1] > gold.");
    checkTrue(doMine(currentPlayer, choice1, choice2, &state, 0), -1, "Should Return -1.");
    
    /***************************************************************************************
    ** choice 2 > treasure_map
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
    choice2 = 30;
    state.coins = 0;
    state.discardCount[currentPlayer] = 0;

    // Do tests
    printFormatted("SUBTEST 3 - choice2 > treasure_map.");
    checkTrue(doMine(currentPlayer, choice1, choice2, &state, 0), -1, "Should Return -1.");

    /***************************************************************************************
    ** choice 2 < curse
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
    choice2 = -100;
    state.coins = 0;
    state.discardCount[currentPlayer] = 0;

    // Do tests
    printFormatted("SUBTEST 4 - choice2 < curse.");
    checkTrue(doMine(currentPlayer, choice1, choice2, &state, 0), -1, "Should Return -1.");

    /***************************************************************************************
    ** (getCost(state->hand[currentPlayer][choice1] + 3) > getCost(choice2)
    ***************************************************************************************/
    // Standard Province setup
    memset(&state, 23, sizeof(struct gameState));
    r = initializeGame(numPlayers, k, 618, &state);
    state.handCount[currentPlayer] = 5;
    for (int i = 0; i < state.handCount[currentPlayer]; i++) {
    	state.hand[currentPlayer][i] = province; // Set all of the cards to province
    }

    // Switch variables so test should pass
    choice1 = 0;
    choice2 = 0;
    state.coins = 0;
    state.discardCount[currentPlayer] = 0;

    // Do tests
    printFormatted("SUBTEST 5 - (getCost(state->hand[currentPlayer][choice1] + 3) > getCost(choice2).");
    checkTrue(doMine(currentPlayer, choice1, choice2, &state, 0), -1, "Should Return -1.");
	
    /***************************************************************************************
    ** Rest of Code
    ***************************************************************************************/
    // Standard Province setup
    memset(&state, 23, sizeof(struct gameState));
    r = initializeGame(numPlayers, k, 618, &state);
    state.handCount[currentPlayer] = 5;
    for (int i = 0; i < state.handCount[currentPlayer]; i++) {
    	state.hand[currentPlayer][i] = province; // Set all of the cards to province
    }

    // Switch variables so test should pass
    choice1 = 0;
    choice2 = 0;
    state.coins = 0;
    state.discardCount[currentPlayer] = 0;

    // Call the function
    doMine(currentPlayer, choice1, choice2, &state, 0);

    // Do tests
    printFormatted("SUBTEST 6 - Rest of Code.");
    checkTrue(state.handCount[currentPlayer], 5, "Current Player Hand Count Shouldn't Change")
	return 0;
}