#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct snack {
  char name[32];
  float cost;
  int quantity;
};

int main() {

    int numSnacks;

    printf("Enter a number of snacks: ");
    scanf("%d", &numSnacks);
    struct snack snacks[numSnacks];

    for(int i = 0; i < numSnacks; i++) {

      printf("Enter a name: ");
      scanf("%s", snacks[i].name);
      printf("Enter a cost: ");
      scanf("%f", &snacks[i].cost);
      printf("Enter a quantity: ");
      scanf("%d", &snacks[i].quantity);

    }

    for(int i = 0; i < numSnacks; i++) {

      printf("%d) name: %s, cost: %f, quantity: %d\n", i+1, snacks[i].name, snacks[i].cost, snacks[i].quantity);

    }

  return 0;

}
