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
    ** The deck card is a treasure card so the coins should only be increased by 2
    ***************************************************************************************/
    // Standard Estate setup
    memset(&state, 23, sizeof(struct gameState));
    initializeGame(numPlayers, k, 618, &state);
    state.handCount[currentPlayer] = 5;
    for (int i = 0; i < state.handCount[currentPlayer]; i++) {
    	state.hand[currentPlayer][i] = estate; // Set all of the cards to estates
    }

    // Switch variables so test should pass
    state.coins = 0;
    state.numActions = 0;
    state.deckCount[currentPlayer] = 10; // So we can draw cards
    state.discardCount[otherPlayer] = 0;
    state.deckCount[otherPlayer] = 1;
    state.deck[otherPlayer][0] = copper;

    tributeCardEffect(0, 0, 0, 0, &state, 0, 0); // Need extra arguments because of function sig

    // Do tests
    printFormatted("SUBTEST 1 - state->deckCount[nextPlayer] > 0 (copper)");
    checkTrue(state.deckCount[otherPlayer], 0, "Other Player Deck Count Decreases by 1");
    checkTrue(state.coins, 2, "Coins are Correct");
    checkTrue(state.numActions, 0, "Actions are Correct");
    checkTrue(state.handCount[currentPlayer], 5, "Hand Count is Correct");

    /***************************************************************************************
    ** (state->discardCount[nextPlayer] + state->deckCount[nextPlayer]) <= 1
    ** state->deckCount[nextPlayer] > 0
    ** The deck card is a victory card so the handCount should only be increased by 2
    ***************************************************************************************/
    // Standard Estate setup
    memset(&state, 23, sizeof(struct gameState));
    initializeGame(numPlayers, k, 618, &state);
    state.handCount[currentPlayer] = 5;
    for (int i = 0; i < state.handCount[currentPlayer]; i++) {
        state.hand[currentPlayer][i] = estate; // Set all of the cards to estates
    }

    // Switch variables so test should pass
    state.coins = 0;
    state.numActions = 0;
    state.deckCount[currentPlayer] = 10; // So we can draw cards
    state.discardCount[otherPlayer] = 0;
    state.deckCount[otherPlayer] = 1;
    state.deck[otherPlayer][0] = estate;

    tributeCardEffect(0, 0, 0, 0, &state, 0, 0); // Need extra arguments because of function sig

    // Do tests
    printFormatted("SUBTEST 2 - state->deckCount[nextPlayer] > 0 (estate)");
    checkTrue(state.deckCount[otherPlayer], 0, "Other Player Deck Count Decreases by 1");
    checkTrue(state.coins, 0, "Coins are Correct");
    checkTrue(state.numActions, 0, "Actions are Correct");
    checkTrue(state.handCount[currentPlayer], 7, "Hand Count is Correct"); // 5 + 2 = 7


    /***************************************************************************************
    ** (state->discardCount[nextPlayer] + state->deckCount[nextPlayer]) <= 1
    ** state->deckCount[nextPlayer] > 0
    ** The deck card is a action card so the numActions should only be increased by 2
    ***************************************************************************************/
    // Standard Estate setup
    memset(&state, 23, sizeof(struct gameState));
    initializeGame(numPlayers, k, 618, &state);
    state.handCount[currentPlayer] = 5;
    for (int i = 0; i < state.handCount[currentPlayer]; i++) {
        state.hand[currentPlayer][i] = estate; // Set all of the cards to estates
    }

    // Switch variables so test should pass
    state.coins = 0;
    state.numActions = 0;
    state.deckCount[currentPlayer] = 10; // So we can draw cards
    state.discardCount[otherPlayer] = 0;
    state.deckCount[otherPlayer] = 1;
    state.deck[otherPlayer][0] = adventurer;

    tributeCardEffect(0, 0, 0, 0, &state, 0, 0); // Need extra arguments because of function sig

    // Do tests
    printFormatted("SUBTEST 3 - state->deckCount[nextPlayer] > 0 (action)");
    checkTrue(state.deckCount[otherPlayer], 0, "Other Player Deck Count Decreases by 1");
    checkTrue(state.coins, 0, "Coins are Correct");
    checkTrue(state.numActions, 2, "Actions are Correct");
    checkTrue(state.handCount[currentPlayer], 5, "Hand Count is Correct");

    /***************************************************************************************
    ** (state->discardCount[nextPlayer] + state->deckCount[nextPlayer]) <= 1
    ** state->discardCount[nextPlayer] > 0
    ** Card should be moved to deck and then treated the same way
    ** The card is a treasure card so the coins should be increased by 2
    ***************************************************************************************/

    // Standard Estate setup
    memset(&state, 23, sizeof(struct gameState));
    initializeGame(numPlayers, k, 618, &state);
    state.handCount[currentPlayer] = 5;
    for (int i = 0; i < state.handCount[currentPlayer]; i++) {
        state.hand[currentPlayer][i] = estate; // Set all of the cards to estates
    }

    // Switch variables so test should pass
    state.coins = 0;
    state.numActions = 0;
    state.deckCount[currentPlayer] = 10; // So we can draw cards
    state.discardCount[otherPlayer] = 1;
    state.deckCount[otherPlayer] = 0;
    state.deck[otherPlayer][0] = copper;

    tributeCardEffect(0, 0, 0, 0, &state, 0, 0); // Need extra arguments because of function sig

    // Do tests
    printFormatted("SUBTEST 4 - state->deckCount[nextPlayer] > 0 (copper)");
    checkTrue(state.deckCount[otherPlayer], 0, "Other Player Deck Count Decreases by 1");
    checkTrue(state.coins, 2, "Coins are Correct");
    checkTrue(state.numActions, 0, "Actions are Correct");
    checkTrue(state.handCount[currentPlayer], 5, "Hand Count is Correct");

    /***************************************************************************************
    ** (state->discardCount[nextPlayer] + state->deckCount[nextPlayer]) <= 1
    ** state->discardCount[nextPlayer] > 0
    ** Card should be moved to deck and then treated the same way
    ** The card is a victory card so the handCount should be increased by 2
    ***************************************************************************************/

    // Standard Estate setup
    memset(&state, 23, sizeof(struct gameState));
    initializeGame(numPlayers, k, 618, &state);
    state.handCount[currentPlayer] = 5;
    for (int i = 0; i < state.handCount[currentPlayer]; i++) {
        state.hand[currentPlayer][i] = estate; // Set all of the cards to estates
    }

    // Switch variables so test should pass
    state.coins = 0;
    state.numActions = 0;
    state.deckCount[currentPlayer] = 10; // So we can draw cards
    state.discardCount[otherPlayer] = 1;
    state.deckCount[otherPlayer] = 0;
    state.deck[otherPlayer][0] = estate;

    tributeCardEffect(0, 0, 0, 0, &state, 0, 0); // Need extra arguments because of function sig

    // Do tests
    printFormatted("SUBTEST 5 - state->deckCount[nextPlayer] > 0 (estate)");
    checkTrue(state.deckCount[otherPlayer], 0, "Other Player Deck Count Decreases by 1");
    checkTrue(state.coins, 0, "Coins are Correct");
    checkTrue(state.numActions, 0, "Actions are Correct");
    checkTrue(state.handCount[currentPlayer], 7, "Hand Count is Correct"); // 5 + 2 = 7

    /***************************************************************************************
    ** (state->discardCount[nextPlayer] + state->deckCount[nextPlayer]) <= 1
    ** state->discardCount[nextPlayer] > 0
    ** Card should be moved to deck and then treated the same way
    ** The card is a action card so the numActions should be increased by 2
    ***************************************************************************************/

    // Standard Estate setup
    memset(&state, 23, sizeof(struct gameState));
    initializeGame(numPlayers, k, 618, &state);
    state.handCount[currentPlayer] = 5;
    for (int i = 0; i < state.handCount[currentPlayer]; i++) {
        state.hand[currentPlayer][i] = estate; // Set all of the cards to estates
    }

    // Switch variables so test should pass
    state.coins = 0;
    state.numActions = 0;
    state.deckCount[currentPlayer] = 10; // So we can draw cards
    state.discardCount[otherPlayer] = 1;
    state.deckCount[otherPlayer] = 0;
    state.deck[otherPlayer][0] = adventurer;

    tributeCardEffect(0, 0, 0, 0, &state, 0, 0); // Need extra arguments because of function sig

    // Do tests
    printFormatted("SUBTEST 6 - state->deckCount[nextPlayer] > 0 (action)");
    checkTrue(state.deckCount[otherPlayer], 0, "Other Player Deck Count Decreases by 1");
    checkTrue(state.coins, 0, "Coins are Correct");
    checkTrue(state.numActions, 2, "Actions are Correct");
    checkTrue(state.handCount[currentPlayer], 5, "Hand Count is Correct");

    /***************************************************************************************
    ** else {}
    ***************************************************************************************/
    // Standard Estate setup
    memset(&state, 23, sizeof(struct gameState));
    initializeGame(numPlayers, k, 618, &state);
    state.handCount[currentPlayer] = 5;
    for (int i = 0; i < state.handCount[currentPlayer]; i++) {
    	state.hand[currentPlayer][i] = estate; // Set all of the cards to estates
    }

    // Switch variables so test should pass
    state.coins = 0;
    state.discardCount[currentPlayer] = 4;
    state.deckCount[otherPlayer] = 0;

    tributeCardEffect(0, 0, 0, 0, &state, 0, 0); // Need extra arguments because of function sig

    // Do tests
    printFormatted("SUBTEST 3 - else{}.");
    checkTrue(state.deckCount[otherPlayer], 0, "Other Player Deck Count Decreases by 1");
    checkTrue(state.deckCount[otherPlayer], 0, "Other Player Discard Count Decreases by 1");

	return 0;
}