//---------------------------------------------------------------------
// sorted_snackbar.c 
// CS223 - Spring 2022
// Ask the user for a list of snacks and store them in alphabetical order
// Name:
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct snack {
  char name[32];
  int quantity;
  float cost;
  struct snack* next;
};

// Insert a new node to a list (implemented as a linked list). 
// The new node should store the given properties
// Param snacks: the first item in the list (NULL if empty)
// Param name: the snack name (max length is 32 characters)
// Param quantity: the snack quantity
// Param cost: the snack cost
// Returns the first item in the list
struct snack* insert_sorted(struct snack* snacks, const char* name, int quantity, float cost) {

  struct snack* newNode;
  newNode = (struct snack*)malloc(sizeof(struct snack));
  strcpy(newNode->name, name);
  newNode->quantity = quantity;
  newNode->cost = cost;

  struct snack* curr = snacks;

  if(curr == NULL) {
    newNode->next = NULL;
    return newNode;
  }

  if (strcmp(newNode->name,curr->name) < 0) { //insert head
      newNode->next = curr;
      return newNode;
  } 

  while(curr->next != NULL) {
    if (strcmp(newNode->name,curr->name) >= 0 && strcmp(newNode->name,curr->next->name) < 0) { //insert between nodes
      //printf("inserting %s between %s and %s\n", newNode->name, curr->name, curr->next->name);
      struct snack temp = *curr;
      curr->next = newNode;
      newNode->next = temp.next;
      return snacks;
    }
    curr = curr->next;
  }

  curr->next = newNode; //insert tail
  newNode->next = NULL;
  return snacks;

}
    

// Delete (e.g. free) all nodes in the given list of snacks
// Param snacks: the first node in the list (NULL if empty)
void clear(struct snack* snacks) {
  struct snack* temp;
  while (snacks != NULL) {
      //printf("%s\n", snacks->name);
      temp = snacks;
      snacks = snacks->next;
      free(temp);
      temp = NULL;
  }
  return;
}

void printLL(struct snack* snacks) {
  if(snacks != NULL) {
    struct snack* curr = snacks;
    int count = 1;
    printf("%d) name: %s, cost: %f, quantity: %d\n", count, curr->name, curr->cost, curr->quantity);
    while(curr->next != NULL) {
      curr = curr->next;
      count++;
      printf("%d) name: %s, cost: %f, quantity: %d\n", count, curr->name, curr->cost, curr->quantity); 
    }
  }
}

int main() {
  int numSnacks;
  printf("Enter a number of snacks: ");
  scanf("%d", &numSnacks);
  
  struct snack *head = NULL;
  char temp_name[32];
  float temp_cost;
  int temp_quantity;

  printf("Enter a name: ");
  scanf("%s", temp_name);
  printf("Enter a cost: ");
  scanf("%f", &temp_cost);
  printf("Enter a quantity: ");
  scanf("%d", &temp_quantity);

  head = insert_sorted(head, temp_name, temp_quantity, temp_cost); 

  for(int i = 0; i < numSnacks-1; i++) {
    printf("Enter a name: ");
    scanf("%s", temp_name);
    printf("Enter a cost: ");
    scanf("%f", &temp_cost);
    printf("Enter a quantity: ");
    scanf("%d", &temp_quantity);
    head = insert_sorted(head, temp_name, temp_quantity, temp_cost); 
  }

  printLL(head);
  clear(head);

  return 0;
}