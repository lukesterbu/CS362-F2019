/**************************************************************************
** Author: 		Luke Burris
** Description:	Tests the tributeCardEffect() function using my checkTrue function()
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
    int tributeRevealedCards[2] = {-1, -1};
    
    int k[10] = {adventurer, council_room, feast, gardens, mine,
        remodel, smithy, village, baron, great_hall};

    struct gameState state;

    printf("\n\n");
    printFormatted("UNITTEST4 - tributeCardEffect()");
	
    /***************************************************************************************
    ** (state->discardCount[nextPlayer] + state->deckCount[nextPlayer]) <= 1
    ** state->deckCount[nextPlayer] > 0
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
    state.deckCount[otherPlayer] = 1;

    tributeCardEffect(0, choice1, choice2, 0, &state, 0, 0); // Need extra arguments because of function sig

    // Do tests
    printFormatted("SUBTEST 1 - state->deckCount[nextPlayer] > 0 (copper)");
    checkTrue(state.deckCount[otherPlayer], 0, "Other Player Deck Count Decreases by 1");

    /***************************************************************************************
    ** (state->discardCount[nextPlayer] + state->deckCount[nextPlayer]) <= 1
    ** state->discardCount[nextPlayer] > 0
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
    state.discardCount[currentPlayer] = 1;
    state.deckCount[otherPlayer] = 0;
    state.discard[otherPlayer][state.discardCount[otherPlayer]] = copper;

    tributeCardEffect(0, choice1, choice2, 0, &state, 0, 0); // Need extra arguments because of function sig

    // Do tests
    printFormatted("SUBTEST 2 - state->discardCount[nextPlayer] > 0.");
    checkTrue(state.deckCount[otherPlayer], 0, "Other Player Discard Count Decreases by 1");
    checkTrue(1, state.coins, "Coins are Correct");

    /***************************************************************************************
    ** else {}
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
    state.discardCount[currentPlayer] = 4;
    state.deckCount[otherPlayer] = 0;

    tributeCardEffect(0, choice1, choice2, 0, &state, 0, 0); // Need extra arguments because of function sig

    // Do tests
    printFormatted("SUBTEST 3 - else{}.");
    checkTrue(state.deckCount[otherPlayer], 0, "Other Player Deck Count Decreases by 1");
    checkTrue(state.deckCount[otherPlayer], 0, "Other Player Discard Count Decreases by 1");

	return 0;
}