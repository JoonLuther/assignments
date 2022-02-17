#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"

void print_ppm(const char* filename, struct ppm_pixel *pix, int *w, int *h) {
  printf("Testing the file %s: %d %d\n", filename, *w, *h);
  for(int i = 0; i < (*h * *w); i++) {
    printf("(%d, %d, %d) ", pix[i].red, pix[i].green, pix[i].blue);
    if((i+1)%*w == 0) {
      printf("\n");
    }
  }
}
// TODO: Implement this function
// Feel free to change the function signature if you prefer to implement an 
// array of arrays
struct ppm_pixel* read_ppm(const char* filename, int *w, int *h) {

  FILE *infile;
  int maxVal;
  int r = 0;
  int g = 0;
  int b = 0;
  char mode[32];
  char line;

  infile = fopen(filename, "r");

  if (infile == NULL) {
      printf("Error: unable to open file %s\n", filename);
      exit(1);
  }

  fgets(mode, sizeof mode, infile);
  line = fgetc(infile);

  if(line != '#'){
    char str[2];
    str[0] = line;
    *w = atoi(str);
    fscanf(infile, "%d %d", h, &maxVal);
  } else {
    //skipping comment
    while(fgetc(infile) != '\n');
    fscanf(infile, "%d %d %d", w, h, &maxVal);
  }


  struct ppm_pixel *ptr = malloc(sizeof(struct ppm_pixel) * *h * *w);

  for(int i = 0; i < *h * *w; i++) {

      fscanf(infile, "%d", &r);
      ptr[i].red = r;
      fscanf(infile, "%d", &g);
      ptr[i].green = g;
      fscanf(infile, "%d", &b);
      ptr[i].blue = b;

  }
  fclose(infile);
  return ptr;
  print_ppm(filename, ptr, w, h);
  return NULL;
}


