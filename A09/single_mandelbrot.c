#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include "read_ppm.h"

int main(int argc, char* argv[]) {
  int size = 480;
  float xmin = -2.0;
  float xmax = 0.47;
  float ymin = -1.12;
  float ymax = 1.12;
  int maxIterations = 1000;
  struct ppm_pixel* pallet;
  struct ppm_pixel* img;
  struct ppm_pixel black;

  int opt;
  while ((opt = getopt(argc, argv, ":s:l:r:t:b:")) != -1) {
    switch (opt) {
      case 's': size = atoi(optarg); break;
      case 'l': xmin = atof(optarg); break;
      case 'r': xmax = atof(optarg); break;
      case 't': ymax = atof(optarg); break;
      case 'b': ymin = atof(optarg); break;
      case '?': printf("usage: %s -s <size> -l <xmin> -r <xmax> -b <ymin> -t <ymax>\n", argv[0]); break;
    }
  }
  printf("Generating mandelbrot with size %dx%d\n", size, size);
  printf("  X range = [%.4f,%.4f]\n", xmin, xmax);
  printf("  Y range = [%.4f,%.4f]\n", ymin, ymax);

  // todo: your work here
  // generate pallet
  pallet = malloc(sizeof(struct ppm_pixel)*maxIterations);
  srand(time(0));
  for(int i = 0; i < maxIterations; i++) {
    struct ppm_pixel color;
    color.red = rand()%255;
    color.green = rand()%255;
    color.blue = rand()%255;
    pallet[i] = color;
    //printf("%d color: %d\n", i, pallet[i].red);
  }

  // compute image

  img = malloc(sizeof(struct ppm_pixel) * size * size);
  black.red = 0;
  black.green = 0;
  black.blue = 0;

  for(int row = 0; row < size; row++) {
    for(int col = 0; col < size; col++) {
      float xfrac = ((float)row)/size;
      float yfrac = ((float)col)/size;
      float x0 = xmin + xfrac * (xmax - xmin);
      float y0 = ymin + yfrac * (ymax - ymin);

      float x = 0;
      float y = 0;
      int iter = 0;

      while(iter < maxIterations && ((x*x) + (y*y)) < (2*2)) {
        float xtmp = (x*x) - (y*y) + x0;
        y = (2*x*y) + y0;
        x = xtmp;
        iter++;
      }
      if(iter < maxIterations) { //escaped!
        img[(col * size) + row] = pallet[iter];
      } else { //did not escape
        img[(col * size) + row] = black;
      }
    }
  }

  write_ppm("test.ppm", img, size, size);
  free(pallet);
  free(img);
  pallet = NULL;
  img = NULL;

}
