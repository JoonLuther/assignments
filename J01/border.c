#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main () {

    char input[32];
    char symbol;

    printf("Enter a word: ");
    scanf(" %s", input);
    printf("enter a symbol: ");
    scanf(" %c", &symbol);

    int len = strlen(input);

    for(int i = 0; i < len + 4; i++) {
        printf("%c", symbol);
    }

    printf("\n%c ", symbol );
    printf("%s", input);
    printf(" %c\n", symbol );
    
    for(int i = 0; i < len + 4; i++) {
        printf("%c", symbol);
    }

    printf("\n");

}