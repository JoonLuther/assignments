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
struct ppm_pixel* read_ppm(const char* filename, int* w, int* h) {
  FILE *infile;
  int maxVal;
  char mode[1024];
  infile = fopen(filename, "rb");

  if (infile == NULL) {
      printf("Error: unable to open file %s\n", filename);
      exit(1);
  }

  fgets(mode, sizeof mode, infile);
  fgets(mode, sizeof mode, infile);

  if(mode[0] != '#'){
    sscanf(mode, " %d %d", w, h);
    fgets(mode, sizeof mode, infile);
    sscanf(mode, " %d", &maxVal);
  } else {
    fgets(mode, sizeof mode, infile);
    while(mode[0] == '#') {
      fgets(mode, sizeof mode, infile);
    }
    sscanf(mode, " %d %d", w, h);
    fgets(mode, sizeof mode, infile);
    sscanf(mode, " %d", &maxVal);
  }

  printf("Reading %s with width %d, height %d, max value %d\n", filename, *w, *h, maxVal);

  struct ppm_pixel *ptr = malloc(sizeof(struct ppm_pixel) * *h * *w);
  fread(ptr, sizeof(int), *h * *w, infile);

  //print_ppm(filename, ptr, w, h);

  fclose(infile);
  return ptr;

  return NULL;
}


// TODO: Implement this function
// Feel free to change the function signature if you prefer to implement an 
// array of arrays



extern void write_ppm(const char* filename, struct ppm_pixel* pxs, int w, int h) {
  FILE *outfile = NULL;

  int s = strlen(filename);
  char newName[100];
  strncpy(newName, filename, s-4);
  newName[s-4] = '\0';
  strcat(newName,"_GLITCH_TEST.ppm");

  unsigned char oldcolorvalue;
  unsigned char newcolorvalue;

  outfile = fopen(newName, "wb");

  if(outfile == NULL) {
    printf("Error: unable to open file %s\n", filename);
    exit(1);
  }

  printf("Writing file %s\n", newName);

  fprintf(outfile, "P6\n%d %d\n255\n", w, h);

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