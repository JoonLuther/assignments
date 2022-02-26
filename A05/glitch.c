#include <stdio.h>
#include "read_ppm.h"
#include <stdlib.h>

int main(int argc, char** argv) {
  int width = 4;
  int height = 4;
  int *w = &width;
  int *h = &height;
  struct ppm_pixel *img;

  img = read_ppm(argv[1], w, h);
  write_ppm(argv[1], img, *w, *h);
  
  free(img);
  img = NULL;
  return 0;
}
