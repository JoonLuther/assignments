#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"

// TODO: Implement this function
// Feel free to change the function signature if you prefer to implement an 
// array of arrays
struct ppm_pixel* read_ppm(const char* filename, int* w, int* h) {
  FILE *infile;
  int maxVal;
  char mode[32];
  char line;
  infile = fopen(filename, "rb");

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
    while(fgetc(infile) != '\n');
    fscanf(infile, "%d %d %d", w, h, &maxVal);
  }

  printf("Reading %s with width %d, height %d\n", filename, *w, *h);

  struct ppm_pixel *ptr = malloc(sizeof(struct ppm_pixel) * *h * *w);
  fread(ptr, sizeof(int), *h * *w, infile);

  fclose(infile);
  return ptr;
}

// TODO: Implement this function
// Feel free to change the function signature if you prefer to implement an 
// array of arrays

extern void write_ppm(const char* filename, struct ppm_pixel* pxs, int w, int h) {
  FILE *outfile = NULL;
  unsigned char oldcolorvalue;
  unsigned char newcolorvalue;

  outfile = fopen(filename, "wb");

  if(outfile == NULL) {
    printf("Error: unable to open file %s\n", filename);
    exit(1);
  }

  printf("Writing file %s\n", filename);

  for(int i = 0; i < (w * h); i++) {
    oldcolorvalue = pxs[i].red << (rand() % 2);
    newcolorvalue = oldcolorvalue << (rand() % 2);
    pxs[i].red = newcolorvalue;

    oldcolorvalue = pxs[i].green << (rand() % 2);
    newcolorvalue = oldcolorvalue << (rand() % 2);
    pxs[i].green = newcolorvalue;

    oldcolorvalue = pxs[i].blue << (rand() % 2);
    newcolorvalue = oldcolorvalue << (rand() % 2);
    pxs[i].blue = newcolorvalue;
  }

  for(int i = 0; i < (w*h); i++) {
    fwrite(&(pxs[i]), sizeof(struct ppm_pixel), 1, outfile);
  }

  fclose(outfile);
}
