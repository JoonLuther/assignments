#include <stdio.h>
#include "read_ppm.h"
#include <stdlib.h>

int main(int argc, char** argv) {
  int width = 0;
  int height = 0;
  int *w = &width;
  int *h = &height;
  struct ppm_pixel *pixels;

  pixels = read_ppm("feep-raw.ppm", w, h);
  write_ppm("feep-raw-test.ppm", pixels, *w, *h);
  free(pixels);
  pixels = NULL;
  return 0;
}

