//---------------------------------------------------------------------
// match_braces.c 
// CS223 - Spring 2022
// Identify matched braces from a given file
// Name:
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
  char sym;
  int linenum;
  int colnum;
  struct node* next;
};

// Push a new node to a stack (implemented as a linked list). 
// The new node should store the given symbol, line number, and column number
// Param sym: a character symbol, '{' for this program
// Param line: the line number of the symbol
// Param line: the column number of the symbol
// Param top: the top node of the stack (NULL if empty)
// Returns the new top of the stack
struct node* push(char sym, int line, int col, struct node* top) {
  struct node* newNode = (struct node*)malloc(sizeof(struct node));
  newNode->sym = sym;
  newNode->linenum = line;
  newNode->colnum = col;

  struct node* curr = top;

  if(curr == NULL) {
    newNode->next = NULL;
    return newNode;
  }
  newNode->next = top;
  return newNode;
}

// Pop the top node from a stack (implemented as a linked list) and frees it
// Param top: the top node of the current stack (NULL if empty)
// Returns the new top of the stack
struct node* pop(struct node* top) {
  if(top == NULL) {
    return NULL;
  } else{
    struct node* temp = top->next;
    free(top);
    top = NULL;
    return temp;
  }
}

// Delete (e.g. free) all nodes in the given stack
// Param top: the top node of the stack (NULL if empty)
void clear(struct node* top) {
  struct node* temp;
  while (top != NULL) {
      temp = top;
      top = top->next;
      free(temp);
      temp = NULL;
  }
  return;
}

// Print all nodes in the given stack (from top to bottom)
// Param top: the top node of the stack (NULL if empty)
void print(struct node* top) {
  if(top != NULL) {
    struct node* curr = top;
    printf("%c ", curr->sym);
    while(curr->next != NULL) {
      curr = curr->next;
      printf("%c ", curr->sym);
    }
    printf("\n");
  }
}

int main(int argc, char* argv[]) {
  FILE *infile;
  char c;
  char *str;
  char open = '{';
  char close = '}';
  struct node* topNode = NULL;
  int line = 1;
  int col = 0;

  if(argv[1] == NULL) {
    printf("No Command Line Args Given");
    return 0;
  }

  str = argv[1];
  infile = fopen(str, "r");

  if (infile == NULL) {
      printf("Error: unable to open file %s\n", "input.txt");
      exit(1);
  }

  while(!feof(infile)) {
    c = fgetc(infile);

    if(c == open) {
      topNode = push(c, line, col, topNode);
    } else if(c == close) {
      if(topNode == NULL) {
        printf("Unmatched brace on Line %d and Column %d\n", line, col);
      } else {
        printf("Found matching braces: (%d, %d) -> (%d, %d)\n", topNode->linenum, topNode->colnum, line, col);
        topNode = pop(topNode);
      }
    } else if(c == '\n') {
      line++;
      col = 0;
    }
    col++;
  }

  while(topNode != NULL) {
    printf("Unmatched brace on Line %d and Column %d\n", topNode->linenum, topNode->colnum);
    topNode = pop(topNode);
  }

  fclose(infile);
  clear(topNode);

  return 0;
}
