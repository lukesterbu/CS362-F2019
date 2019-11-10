#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
  // TODO: rewrite this function
  int n = rand() % (126 - 32) + 32;
  // Make the letter lowercase if uppercase
  if (n >= 65 && n <= 90) {
    n += 32;
  }
  return n;
}

char *inputString()
{
  // TODO: rewrite this function
  // According to testme() this should return a 5 letter word
  // If the word is "reset" the program will end
  int chance = rand() % 100;
  char *s = malloc(5);
  if (chance < 100) {
    for(int i = 0; i < 5; i++) {
      // Only lowercase letters
      s[i] = rand() % (126 - 97) + 97;
    }
  }
  else {
    s = "reset";
  }
  return s;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' ' && state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}

int main(int argc, char *argv[])
{
  srand(time(NULL));
  testme();
  return 0;
}