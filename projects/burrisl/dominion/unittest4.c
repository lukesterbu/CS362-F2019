/**************************************************************************
** Author: 		Luke Burris
** Description:	Tests the doTribute() function using my checkTrue function()
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
    int tributeRevealedCards[2];
    
    int k[10] = {adventurer, council_room, feast, gardens, mine,
        remodel, smithy, village, baron, great_hall};

    struct gameState state;

    printf("\n\n");
    printFormatted("UNITTEST4 - doTribute()");
	
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
    tributeRevealedCards[0] = 0;
    tributeRevealedCards[1] = 1;

    doTribute(currentPlayer, otherPlayer, tributeRevealedCards, choice1, choice2, &state, 0);

    // Do tests
    printFormatted("SUBTEST 1 - state->deckCount[nextPlayer] > 0.");
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
    tributeRevealedCards[0] = 0;
    tributeRevealedCards[1] = 1;

    doTribute(currentPlayer, otherPlayer, tributeRevealedCards, choice1, choice2, &state, 0);

    // Do tests
    printFormatted("SUBTEST 1 - state->discardCount[nextPlayer] > 0.");
    checkTrue(state.deckCount[otherPlayer], 0, "Other Player Discard Count Decreases by 1");
	return 0;
}