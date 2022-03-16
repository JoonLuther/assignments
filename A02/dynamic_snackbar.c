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
    struct snack *ptr;

    printf("Enter a number of snacks: ");
    scanf("%d", &numSnacks);
    ptr = (struct snack*) malloc(sizeof(struct snack) * numSnacks);

    for(int i = 0; i < numSnacks; i++) {

      printf("Enter a name: ");
      scanf("%s", ptr[i].name);
      printf("Enter a cost: ");
      scanf("%f", &ptr[i].cost);
      printf("Enter a quantity: ");
      scanf("%d", &ptr[i].quantity);

    }

    for(int i = 0; i < numSnacks; i++) {

      printf("%d) name: %s, cost: %f, quantity: %d\n", i+1, ptr[i].name, ptr[i].cost, ptr[i].quantity);

    }

    free(ptr);
    ptr = NULL;

  return 0;

}
