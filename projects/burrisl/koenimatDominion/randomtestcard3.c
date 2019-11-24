/**************************************************************************
** Author:      Luke Burris
** Description: Tests the tributeCardEffect() function using my checkTrue function()
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

// Prints PASSED if true and FAILED if false. Also prints the passed in description
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
    int otherPlayer = 1;

    // Supply piles
    int k[10] = {adventurer, council_room, feast, tribute, minion, remodel, smithy, village, baron, great_hall};

    // Seed the random number generator
    srand(time(NULL));
 
    // Print out title of test
    printFormatted("RANDOM TEST 3 - tributeCardEffect()");

    // While loop variables
    int currIter = 0;
    int iterations = 10000;

    while (currIter < iterations) {
        // Variable declarations
        int numCoinsBefore = 0;
        int handSizeBefore = 0;
        int numActionsBefore = 0;
        int numTreasureCards = 0;
        int numVictoryCards = 0;
        int numActionCards = 0;
        int tributeRevealedCards[2] = {-1, -1};

        printf("** ITERATION %d **\n", currIter + 1);
        // Initialize the Game
        memset(&state, 23, sizeof(struct gameState));
        initializeGame(numPlayers, k, 618, &state);

        // Randomly set the size of different variables
        state.handCount[otherPlayer] = rand() % 10;
        state.discardCount[otherPlayer] = rand() % 100;
        state.deckCount[otherPlayer] = rand() % 100;

        // Add random cards to the hand
        for (int card = 0; card < state.handCount[otherPlayer]; card++) {
            state.hand[otherPlayer][card] = rand() % 3 + 1;
        }

        // Add random cards to the deck
        for (int card = 0; card < state.deckCount[otherPlayer]; card++) {
            state.deck[otherPlayer][card] = rand() % 3 + 1;
        }

        // Add random cards to the discard pile
        for (int card = 0; card < state.discardCount[otherPlayer]; card++) {
            state.discard[otherPlayer][card] = rand() % 3 + 1;
        }

        // Gain a tribute card
        //gainCard(tribute, &state, TO_HAND, currentPlayer);

        // Get variable snapshots
        numActionsBefore = state.numActions;
        numCoinsBefore = state.coins;
        handSizeBefore = state.handCount[currentPlayer];

        // Do nothing for more coverage
        if (state.deckCount[otherPlayer] + state.discardCount[otherPlayer] == 0) {
            // Both tributeRevealedCards will be -1
        }
        // Get 2 random cards from top of discard pile
        else if (state.deckCount[otherPlayer] == 0 && state.discardCount[otherPlayer] > 1) {
            tributeRevealedCards[0] = state.discard[otherPlayer][state.discardCount[otherPlayer] - 1];
            tributeRevealedCards[1] = state.discard[otherPlayer][state.discardCount[otherPlayer] - 2];
        }
        // Get 2 random cards from top of deck
        else if (state.deckCount[otherPlayer] > 1) {
            tributeRevealedCards[0] = state.deck[otherPlayer][state.deckCount[otherPlayer] - 1];
            tributeRevealedCards[1] = state.deck[otherPlayer][state.deckCount[otherPlayer] - 2];
        }

        printf("Card 1: %d\n", tributeRevealedCards[0]);
        printf("Card 2: %d\n", tributeRevealedCards[1]);

        // Increment variables appropriately
        int dupFlag = 1;
        int card = 0;
        while (dupFlag == 1 && card < 2) {
            if (tributeRevealedCards[0] == tributeRevealedCards[1]) {
                dupFlag = 0;
            }
            // Treasure Card (copper = 4, silver = 5, gold = 6)
            if (tributeRevealedCards[card] == copper || tributeRevealedCards[card] == silver || tributeRevealedCards[card] == gold) {
                numTreasureCards++;
            }
            // Victory Card (estate = 1, duchy = 2, province = 3, gardens = 10, great_hall = 16)
            else if (tributeRevealedCards[card] == estate || tributeRevealedCards[card] == duchy || tributeRevealedCards[card] == province || tributeRevealedCards[card] == gardens || tributeRevealedCards[card] == great_hall) {
                numVictoryCards++;
            }
            // Card equals -1 which means it wasn't set
            else if (tributeRevealedCards[card] == -1) {
                // Do nothing
            }
            // Action Card (any other number between 0 and 26)
            else {
                numActionCards++;
            }
            card++;
        }

        // Call tributeCardEffect()
        tributeCardEffect(0, 0, 0, 0, &state, 0, 0); // Need extra arguments because of function sig

        checkTrue(numActionsBefore + (2 * numActionCards), state.numActions, "Actions Are Correct");
        checkTrue(numCoinsBefore + (2 * numTreasureCards), state.coins, "Coins Are Correct");
        checkTrue(handSizeBefore + (2 * numVictoryCards), state.handCount[currentPlayer], "Hand Count is Correct");

        currIter++; // Increment Iterator
    }

    printFormatted("RANDOM TEST 3 COMPLETED - tributeCardEffect()");

    return 0;
}