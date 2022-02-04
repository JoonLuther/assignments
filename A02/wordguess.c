#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>


int main() {

  srand(time(NULL)); 
  FILE *infile;
  int maxLen = 33;
  char word[maxLen];
  char wordGuess[maxLen];
  char blank[2] = "_";
  int r = rand() % 69000;
  bool guessed = false;

  infile = fopen("words.txt", "r");
  if (infile == NULL) {
    printf("Error: unable to open file %s\n", "input.txt");
    exit(1);
  }

  const unsigned MAX_LENGTH = 256;
  char buffer[MAX_LENGTH];

  for(int i = 0; i < r; i++) {

    fgets(buffer, MAX_LENGTH, infile);

  }

  strcpy(word, buffer);
  printf("%s\n", word);

  fclose(infile);

  for(int i = 0; i < strlen(word); i++) {

    strcpy(&wordGuess[i], blank);

  }

  for(int count = 1; count < 21; count++) {

    char guessedChar;

    printf("Turn: %d\n", count);
    printf("\n%s\n", wordGuess);
    printf("\nGuess a character: ");
    scanf("%c", &guessedChar);

    for(int i = 0; i < strlen(word); i++) {
      if(word[i] == guessedChar) {
        wordGuess[i] = guessedChar;
      }
    }

    if(strcmp(wordGuess,word) == 0) {
      printf("%s\n", wordGuess);
      printf("congratulations, you guessed the word!\n");
      return 0;
    }
  }

  printf("out of guesses, the correct word was: %s", word);
  return 0;

}
