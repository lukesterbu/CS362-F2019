#include "dominion.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// Returns 1 if true and 0 if false
int checkTrue(int x, int y, char* desc) {
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
    
    /***************************************************************************************
    ** Test to see if an estate card is found in the hand when choice1 <= 0
    ***************************************************************************************/
    // Standard setup
    memset(&state, 23, sizeof(struct gameState));
    r = initializeGame(2, k, 618, &state);
    state.handCount[currentPlayer] = 5;
    for (int i = 0; i < state.handCount[currentPlayer]; i++) {
    	state.hand[currentPlayer][i] = estate; // Set all of the cards to estates
    }
    // Switch variables so test should pass
    choice1 = 0;
    state.hand[currentPlayer][4] = estate; // Set one of the cards to be an estate
    state.coins = 0;
    state.discardCount[currentPlayer] = 0;

    // Call the function being tested;
    doBaron(currentPlayer, choice1, &state);

    // Do tests
    printf("%d\n", state.coins);
    checkTrue(state.numBuys, 2, "Buys Increased By 1");
    checkTrue(state.coins, 4, "Coins Increased By 4");
    checkTrue(state.discardCount[currentPlayer], 1, "Discard Count Increased By 1");
    checkTrue(state.handCount[currentPlayer], 4, "Hand Count Decreased By 1");

    /***************************************************************************************
    ** Test to see if an estate card is not found in the hand when choice 1 <= 0
    ***************************************************************************************/
    // Standard setup
    memset(&state, 23, sizeof(struct gameState));
    r = initializeGame(2, k, 618, &state);
    state.handCount[currentPlayer] = 5;
    for (int i = 0; i < state.handCount[currentPlayer]; i++) {
    	state.hand[currentPlayer][i] = copper;
    }

    // Switch variables so test should pass
    choice1 = 0;

    // Call the function being tested;
    doBaron(currentPlayer, choice1, &state);

    // Do tests
    checkTrue(state.supplyCount[estate], 7, "Estate Supply decreased by 1"); // Should be one less than 8 since 2 players

    return 0;
}