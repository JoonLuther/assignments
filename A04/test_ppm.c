#include <stdio.h>
#include "read_ppm.h"
#include <stdlib.h>

int main() {
  // todo: call read_ppm
  int width = 4;
  int height = 4;
  int *w = &width;
  int *h = &height;
  struct ppm_pixel *img;

  img = read_ppm("feep-ascii.ppm", w, h);
  print_ppm("feep-ascii.ppm", img, w, h);
  free(img);
  img = NULL;
  return 0;
}

