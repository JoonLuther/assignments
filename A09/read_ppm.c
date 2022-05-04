#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"

struct ppm_pixel* read_ppm(const char* filename, int* w, int* h) {

  // your code here
  return NULL;
}

void write_ppm(const char* filename, struct ppm_pixel** pixels, int w, int h) {

  FILE *outfile = NULL;
  int s = strlen(filename);
  char newName[100];
  strncpy(newName, filename, s-4);
  newName[s-4] = '\0';
  strcat(newName,".ppm");

  outfile = fopen(newName, "wb");

  if(outfile == NULL) {
    printf("Error: unable to open file %s\n", newName);
    exit(1);
  }

  printf("Writing file %s\n", newName);

  fprintf(outfile, "P6\n%d %d\n255\n", w, h);

  for(int i = 0; i < h; i++) {
    for(int j = 0; j < w; j++) {
      //printf("Row: %d Col: %d\n", i, j);
      fwrite(&(pixels[i][j]), sizeof(struct ppm_pixel), 1, outfile);
    }
  }

  fclose(outfile);

}

