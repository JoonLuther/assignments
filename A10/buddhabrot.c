#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <pthread.h>
#include "read_ppm.h"
#include <sys/time.h>
#include <math.h>

pthread_mutex_t mutex;
pthread_barrier_t barrier;

struct thread_data {
  int startrow;
  int endrow;
  int startcol;
  int endcol;
  float xmin;
  float xmax;
  float ymin;
  float ymax;
  int maxIterations;
  int size;
  int** membership;
  int** count;
  struct ppm_pixel** img;
  struct ppm_pixel *pallet;
  struct ppm_pixel black;
};

void *compute_image(void *args) {

  struct thread_data *data = (struct thread_data *) args;
  printf("Thread %lu) sub-image block: cols (%d, %d) to rows (%d,%d)\n", (unsigned long)pthread_self(), data->startcol, data->endcol, data->startrow, data->endrow);

  //Step 1:

  for(int row = data->startrow; row < data->endrow; row++) {
    for(int col = data->startcol; col < data->endcol; col++) {
      float xfrac = ((float)col)/data->size;
      float yfrac = ((float)row)/data->size;
      float x0 = data->xmin + xfrac * (data->xmax - data->xmin);
      float y0 = data->ymin + yfrac * (data->ymax - data->ymin);

      float x = 0;
      float y = 0;
      int iter = 0;

      while(iter < data->maxIterations && ((x*x) + (y*y)) < (2*2)) {
        float xtmp = (x*x) - (y*y) + x0;
        y = (2*x*y) + y0;
        x = xtmp;
        iter++;
      }

      if(iter < data->maxIterations) { //escaped!
        data->membership[row][col] = 0;
      } else { //did not escape
        data->membership[row][col] = 1;
      }
    }
  }

  //Step 2:

  long max_count = 0;
  for(int row = data->startrow; row < data->endrow; row++) {
    for(int col = data->startcol; col < data->endcol; col++) {
      //printf("loop: %d\n\n", (row*col) + col);
      if (data->membership[row][col] == 1) {
        continue;
      } else {
        float xfrac = ((float)col) / data->size;
        float yfrac = ((float)row) / data->size;
        float x0 = data->xmin + xfrac * (data->xmax - data->xmin);
        float y0 = data->ymin + yfrac * (data->ymax - data->ymin);

        float x = 0;
        float y = 0;
	int iter = 0;

        while (x*x + y*y < 2*2 && iter < data->maxIterations) {
          //printf("(%f, %f)\n", x, y);
	  iter++;
          float xtmp = x * x - y * y + x0;
          y = 2 * x * y + y0;
          x = xtmp;

          float yrow = round(data->size * (y - data->ymin) / (data->ymax - data->ymin));
          float xcol = round(data->size * (x - data->xmin) / (data->xmax - data->xmin));

          if (yrow < 0 || yrow >= data->size) continue; // out of range
          if (xcol < 0 || xcol >= data->size) continue; // out of range

          pthread_mutex_lock(&mutex);
          data->count[(int)yrow][(int)xcol]++;

          if (data->count[(int)yrow][(int)xcol] > max_count) {
            max_count = data->count[(int)yrow][(int)xcol];
          }
          pthread_mutex_unlock(&mutex);
        }

	if(iter >= data->maxIterations) {
		printf("%d, %d, escaped: %d\n",row,col, data->membership[row][col]);
	}
      }
    }
  }
  pthread_barrier_wait(&barrier);

  //Step 3:

  float gamma = 0.681;
  float factor = 1.0/gamma;
  
  for(int row = data->startrow; row < data->endrow; row++) {
    for(int col = data->startcol; col < data->endcol; col++) {

      float value = 0;
      struct ppm_pixel color;

      if(data->count[row][col] > 0) {
        value = log(data->count[row][col]) / log(max_count);
        value = pow(value, factor);
      }

      color.red = value * 255;
      color.green = value * 255;
      color.blue = value * 255;

      data->img[row][col] = color;

    }
  }

  return (void*) NULL;
}

int main(int argc, char* argv[]) {
  int size = 480;
  float xmin = -2.0;
  float xmax = 0.47;
  float ymin = -1.12;
  float ymax = 1.12;
  int maxIterations = 1000;
  int numProcesses = 4;
  struct ppm_pixel* pallet;
  struct ppm_pixel black;
  double timer;
  struct timeval tstart, tend;

  int opt;
  while ((opt = getopt(argc, argv, ":s:l:r:t:b:p:")) != -1) {
    switch (opt) {
      case 's': size = atoi(optarg); break;
      case 'l': xmin = atof(optarg); break;
      case 'r': xmax = atof(optarg); break;
      case 't': ymax = atof(optarg); break;
      case 'b': ymin = atof(optarg); break;
      case '?': printf("usage: %s -s <size> -l <xmin> -r <xmax> "
        "-b <ymin> -t <ymax> -p <numProcesses>\n", argv[0]); break;
    }
  }
  printf("Generating mandelbrot with size %dx%d\n", size, size);
  printf("  Num processes = %d\n", numProcesses);
  printf("  X range = [%.4f,%.4f]\n", xmin, xmax);
  printf("  Y range = [%.4f,%.4f]\n", ymin, ymax);

  // todo: your code here
  pthread_mutex_init(&mutex, NULL);
  pthread_barrier_init(&barrier, NULL, 4);
  pthread_t tid[4];

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

  black.red = 0;
  black.green = 0;
  black.blue = 0;

  // compute image

  gettimeofday(&tstart, NULL);

  struct ppm_pixel** img = malloc(sizeof(struct ppm_pixel*) * size);
  int** membership = malloc(sizeof(int*) * size);
  int** counts = malloc(sizeof(int*) * size);

  for (int i = 0; i < size; i++) {
    img[i] = malloc(sizeof(struct ppm_pixel) * size); 
  }
  for (int i = 0; i < size; i++) {
    membership[i] = malloc(sizeof(int*) * size); 
  }
  for (int i = 0; i < size; i++) {
    counts[i] = malloc(sizeof(int*) * size); 
  }

  struct thread_data* ids = malloc(sizeof(struct thread_data) * numProcesses); // 4 threads
  int count = 0;

  for (int i = 0; i < numProcesses/2; i++) {
    for (int j = 0; j < numProcesses/2; j++) {
      ids[count].startcol = j*(size/2);
      ids[count].endcol = (j*(size/2))+(size/2);
      ids[count].startrow = i*(size/2);
      ids[count].endrow = (i*(size/2))+(size/2);
      ids[count].maxIterations = maxIterations;
      ids[count].xmin = xmin;
      ids[count].xmax = xmax;
      ids[count].ymin = ymin;
      ids[count].ymax = ymax;
      ids[count].size = size;
      ids[count].img = img;
      ids[count].pallet = pallet;
      ids[count].black = black;
      ids[count].membership = membership;
      ids[count].count = counts;
      pthread_create(&tid[count], NULL, compute_image, &ids[count]);
      count++;
    }
  }

  for (int i = 0; i < 4; i++) {
    pthread_join(tid[i], NULL);
  }

  write_ppm("threaded_buddhabrot.ppm", img, size, size);

  gettimeofday(&tend, NULL);
  timer = tend.tv_sec - tstart.tv_sec + (tend.tv_usec - tstart.tv_usec)/1.e6;
  printf("time is %g\n", timer);

  free(pallet);
  for (int i = 0; i < size; i++) {
    free(img[i]);
    free(membership[i]);
    free(counts[i]);
  }

  free(img);
  free(ids);
  pallet = NULL;
  img = NULL;
  ids = NULL;
  pthread_mutex_destroy(&mutex); 

}