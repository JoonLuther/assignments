#include <stdio.h>
#include "read_ppm.h"
#include <stdlib.h>

void print_ascii(struct ppm_pixel *img, int *w, int *h) {
  int intensity;
  for(int i = 0; i < *h; i++) {
    for(int j = 0; j < *w; j++) {

      int idx = (*w * i) + j;
      intensity = ((img[idx].red + img[idx].green + img[idx].blue)/3);

      if(intensity <= 25) {
        printf("@");
      } else if(intensity <= 50) {
        printf("#");
      } else if(intensity <= 75) {
        printf("%%");
      } else if (intensity <= 100) {
        printf("*");
      } else if (intensity <= 125) {
        printf("o");
      } else if (intensity <= 150) {
        printf(";");
      } else if (intensity <= 175) {
        printf(":");
      } else if (intensity <= 200) {
        printf(",");
      } else if (intensity <= 225) {
        printf(".");
      } else if (intensity <= 255) {
        printf(" ");
      } else {
        printf("?");
      }
    }
    printf("\n");
  }
}

int main(int argc, char** argv) {
  // todo
  int width = 0;
  int height = 0;
  int *w = &width;
  int *h = &height;
  struct ppm_pixel *img;

  img = read_ppm(argv[1], w, h);
  print_ascii(img, w, h);
  free(img);
  img = NULL;
  return 0;
}

