/**************************************************************************
** Author: 		Luke Burris
** Description:	Tests the doAmbassador() function using my checkTrue function()
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
    
    int k[10] = {adventurer, council_room, feast, gardens, mine,
        remodel, smithy, village, baron, great_hall};

    struct gameState state;

    printf("\n\n");
    printFormatted("UNITTEST3 - doAmbassador()");
	
    /***************************************************************************************
    ** choice2 > 2. This will fail due to my bug
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
    choice2 = 3;
    state.coins = 0;
    state.discardCount[currentPlayer] = 0;

    // Call the function being tested;
    doAmbassador(currentPlayer, choice1, choice2, &state, 0);

    // Do tests
    printFormatted("SUBTEST 1 - choice2 = 3.");
    checkTrue(doAmbassador(currentPlayer, choice1, choice2, &state, 0), -1, "Should Return -1."); // This should fail because of my bug

    /***************************************************************************************
    ** choice2 < 0.
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
    choice2 = -1;
    state.coins = 0;
    state.discardCount[currentPlayer] = 0;

    // Call the function being tested;
    doAmbassador(currentPlayer, choice1, choice2, &state, 0);

    // Do tests
    printFormatted("SUBTEST 2 - choice2 = -1.");
    checkTrue(doAmbassador(currentPlayer, choice1, choice2, &state, 0), -1, "Should Return -1.");

	return 0;
}