// Unit test for Ambassador
// set your card array
int k[10] = { adventurer, council_room, feast, gardens, mine
 , remodel, smithy, village, baron, great_hall };
// declare the game state
struct gameState G;
// declare the arrays
int coppers[MAX_HAND];
int silvers[MAX_HAND];
int golds[MAX_HAND];
printf("Begin Testing someFunction():\n");
//
// set the state of your variables
 // comment on what this is going to test
//
memset(&G, 23, sizeof(struct gameState)); // set the game state
r = initializeGame(2, k, seed, &G); // initialize a new game
G.handCount[p] = handCount; // set any other variables
memcpy(G.hand[p], coppers, sizeof(int) * handCount);
// call the refactored function
myrefactoredfunction(p, &G, bonus);
// verify that your asserts pass, for the bugs your asserts may fail
assert(G.coins == something); // check a condition
assert(some condition);
assert(some condition);
//
// adjust the state of your variables to continue testing the function
 // comment on what this is going to test
//
memset(&G, 0, sizeof(struct gameState)); // set the game state
r = initializeGame(3, k, seed, &G); // initialize a new game
G.handCount[p] = handCount; // set any other variables
memcpy(G.hand[p], silvers, sizeof(int) * handCount);
// call the refactored function again
myrefactoredfunction(p, &G, bonus);
// verify that your asserts pass, for the bugs your asserts may fail
assert(G.coins == something); // check a condition
assert(some condition);
assert(some condition);
printf("Test completed!\n");