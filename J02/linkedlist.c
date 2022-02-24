#include <stdio.h>
#include <string.h>

struct cake {
  float cost;
  char flavor[16];
  struct cake* next;
};

struct cake makeCake(const char* flavor, float cost) {
  struct cake newCake;
  strncpy(newCake.flavor, flavor, 16);
  newCake.cost = cost;
  newCake.next = NULL;
  return newCake;
}

struct cake cheapestCake(struct cake head) {
  struct cake cheapest = head;
  struct cake curr = head;
  printf("cake: %s ($%f)\n", curr.flavor, curr.cost);
  while (curr.next != NULL) {
    curr = *curr.next;
    printf("cake: %s ($%f)\n", curr.flavor, curr.cost);
    if(curr.cost < cheapest.cost) {
      cheapest = curr;
    }
  }

  return cheapest;

}

// todo: implement cheapestCake

int main() {
  struct cake cake1 = makeCake("red velvet", 2.00);
  struct cake cake2 = makeCake("chocolate", 1.75);
  struct cake cake3 = makeCake("mocha", 3.50);
  struct cake cake4 = makeCake("peach", 20.00);
  // todo: define 4th cake

  cake1.next = &cake2;
  cake2.next = &cake3;
  cake3.next = &cake4;

  // draw stack and heap here

  // todo: call cheapestCake
  printf("cheapest cake: %s\n", cheapestCake(cake1).flavor);
}
