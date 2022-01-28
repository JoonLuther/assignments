#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

int main() {
  srand(time(0));
  int rounds;
  int playerScore = 0;
  int AIScore = 0;

  printf("Welcome to Rock Paper Scissors!");
  printf("How many rounds would you like to play? ");
  scanf("%d", &rounds);

  for(int i = 0; i < rounds; i++) {

    int choose;
    char youChoose[9];

    printf("Which do you choose? rock, paper, or scissors? ");
    scanf("%8s", youChoose);

    if(strcmp(youChoose, "rock") == 0 || strcmp(youChoose, "paper") == 0 || strcmp(youChoose, "scissors") == 0) {

      choose = rand() % 3;

      if(choose == 0) {

        printf("AI chooses rock!\n");

        if(strcmp(youChoose, "paper") == 0) {
          printf("Paper covers rock\n");
          playerScore++;
        } else if(strcmp(youChoose, "scissors") == 0) {
          printf("Rock bashes scissors\n");
          AIScore++;
        }

      } else if(choose == 1) {

        printf("AI chooses paper!\n");

        if(strcmp(youChoose, "scissors") == 0) {
          printf("Scissors cut paper\n");
          playerScore++;
        } else if(strcmp(youChoose, "rock") == 0) {
          printf("Paper covers rock\n");
          AIScore++;
        }

      } else {

        printf("AI chooses scissors!\n");

        if(strcmp(youChoose, "rock") == 0) {
          printf("Rock bashes scissors\n");
          playerScore++;
        } else if(strcmp(youChoose, "paper") == 0) {
          printf("Scissors cut paper\n");
          AIScore++;
        }

      }

    } else {

      printf("You entered an invalid choice: %s\n", youChoose);

    }

    printf("AI Score: %d, Player Score: %d\n", AIScore, playerScore);

  }

  if(playerScore > AIScore) {
    printf("Player Wins!\n");
  } else if(AIScore > playerScore) {
    printf("AI Wins!\n");
  } else {
    printf("Tie!\n");
  }

  return 0;
}

