#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include "read_ppm.h"
#include <string.h>

int main(int argc, char* argv[]) {
  int size = 480;
  float xmin = -2.0;
  float xmax = 0.47;
  float ymin = -1.12;
  float ymax = 1.12;
  int maxIterations = 1000;
  struct ppm_pixel* pallet;
  struct ppm_pixel** img;
  struct ppm_pixel black;
  char fnameSize[100];
  char fnameTime[100];
  struct timeval timez;
  double timer;
  struct timeval tstart, tend;

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
  }

  // compute image

  gettimeofday(&tstart, NULL);

  img = malloc(sizeof(struct ppm_pixel*) * size);
  for(int i = 0; i < size; i++) {
    img[i] = malloc(sizeof(struct ppm_pixel) * size);
  }
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
        img[col][row] = pallet[iter];
      } else { //did not escape
        img[col][row] = black;
      }
    }
  }
  gettimeofday(&tend, NULL);
  timer = tend.tv_sec - tstart.tv_sec + (tend.tv_usec - tstart.tv_usec)/1.e6;
  printf("time is %g s\n", timer);

  gettimeofday(&timez, NULL);
  sprintf(fnameSize, "%d", size);
  int stringSize = strlen(fnameSize);
  fnameSize[stringSize] = '-';
  sprintf(fnameTime, "%d", (int)timez.tv_sec);
  strcat(fnameTime,"-single-mandelbrot.ppm");
  stringSize+=(strlen(fnameTime) + 1);
  char newName[100];
  strncpy(newName, fnameSize, stringSize + 1);
  strcat(newName, fnameTime);
  newName[stringSize + 1] = '\0';

  write_ppm(newName, img, size, size);
  free(pallet);
  for(int i = 0; i < size; i++) {
    free(img[i]);
  }
  free(img);
  pallet = NULL;
  img = NULL;

}
