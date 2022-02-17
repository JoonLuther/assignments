//---------------------------------------------------------------------
// magic_square.c 
// CS223 - Spring 2022
// Identify whether a matrix is a magic square
// Name:
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void isMagicSquare(int *sq, int len) {

    //Calculate magic square constant using 1st row:
    int mgc = 0;

    for(int i = 0; i < len; i++) {
        mgc = mgc + sq[i];
    }

    //Sum rows:

    for(int i = 1; i < len; i++) {
        int sum = 0;
        for(int j = 0; j < len; j++) {
            sum = sum + sq[i * len +j];
        }

        if(sum != mgc) {
            printf("Not a Magic Square :(\n");
            return;
        }
    }

    //Sum cols:

    for(int j = 0; j < len; j++) {
        int sum = 0;
        for(int i = 0; i < len; i++) {
            sum = sum + sq[i * len +j];
        }
        if(sum != mgc) {
            printf("Not a Magic Square :(\n");
            return;
        }
    }

    //Sum diagonals:

    int s = 0;
    for(int i = 0; i < len; i++) {
        s = s + sq[i * len + i];
    }
    if(s != mgc) {
        printf("Not a Magic Square :(\n");
        return;
    }

    s = 0;
    for(int i = len-1; i >= 0; i--) {
        s = s + sq[i * len + i];
    }
    if(s != mgc) {
        printf("Not a Magic Square :(\n");
        return;
    }

    printf("M is a magic square (magic constant = %d)\n", mgc);
    return;

}

void readMatrix(char *p) {
    FILE *infile;
    int c = 1;

    infile = fopen(p, "r");

    if (infile == NULL) {
        printf("Error: unable to open file %s\n", "input.txt");
        exit(1);
    }

    fscanf(infile, "%d", &c);
    int h = c;
    fscanf(infile, "%d", &c);
    int l = c;
    fscanf(infile, "%d", &c);

    if(h != l) {
        printf("Matrix is not a square\n");
        return;
    }

    int *ptr = malloc(sizeof(int)*h*l);

    for(int i = 0; i < h*l; i++) {

        ptr[i] = c;
        printf("%d ",c);
        if((i+1)%l == 0) {
            printf("\n");
        }
        fscanf(infile, "%d", &c);
    }

    isMagicSquare(ptr,l);
    free(ptr);
    ptr = NULL;
    fclose(infile);

}



int main(int argc, char *argv[]) {
    int count = 1;
    while(argv[count] != NULL) {
        char *path = argv[count];
        readMatrix(path);
        count++;
    }
}

