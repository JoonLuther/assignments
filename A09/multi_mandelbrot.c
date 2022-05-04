#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include "read_ppm.h"
#include <string.h>

void set_pixels (struct ppm_pixel** img, int startrow, int endrow, int startcol, int endcol, int size, int xmin, int xmax, int ymin, int ymax, int maxIterations, struct ppm_pixel *pallet, struct ppm_pixel black) {
  for(int row = startrow; row < endrow; row++) {
    for(int col = startcol; col < endcol; col++) {
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
  //struct ppm_pixel* img;
  struct ppm_pixel black;
  char fnameSize[100];
  char fnameTime[100];
  struct timeval timez;
  double timer;
  struct timeval tstart, tend;

  int shmid; 
  shmid = shmget(IPC_PRIVATE, sizeof(struct ppm_pixel) * size * size , 0644 | IPC_CREAT);
  if (shmid == -1) {
    perror("Error: cannot initialize shared memory\n");
    exit(1);
  }

  struct ppm_pixel* buffer = shmat(shmid, NULL, 0);
  if (buffer == (void*) -1) {
    perror("Error: cannot access shared memory\n");
    exit(1);
  }
  
  struct ppm_pixel** img = malloc(sizeof(struct ppm_pixel*) * size);
  // for(int i = 0; i < numProcesses; i++) {
  //   img[i] = &(buffer[i*size]);
  // }
  for (int i = 0; i < size; i++) {
    img[i] = &(buffer[i*size]);
    //malloc(sizeof(struct ppm_pixel) * size); 
  }

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

  //min and max values are the same, pass each thread different indicies

  //img = malloc(sizeof(struct ppm_pixel) * size * size);
  gettimeofday(&tstart, NULL);

  black.red = 0;
  black.green = 0;
  black.blue = 0;

  pid_t pid; 

  for (int i = 0; i < numProcesses/2; i++) {
    for(int j = 0; j < numProcesses/2; j++) {
      //printf("i = %d\n", i);
      pid = fork();
      if (pid == 0) {
        printf("Process %d: row (%d, %d) col (%d, %d)\n", pid, i * (size/2), i * (size/2) + (size/2), j * (size/2), j * (size/2) + (size/2));
        set_pixels(img, i * (size/2), i * (size/2) + (size/2), j * (size/2), j * (size/2) + (size/2), size, xmin, xmax, ymin, ymax, maxIterations, pallet, black);
        exit(0);
      } else {
        printf("Launched child process: %d\n", pid);
      }
    }
  }

  for (int i = 0; i < numProcesses; i++) {
    int status;
    int pid = wait(&status);
    printf("Child process complete: %d\n", pid);
  }

  gettimeofday(&tend, NULL);
  timer = tend.tv_sec - tstart.tv_sec + (tend.tv_usec - tstart.tv_usec)/1.e6;
  printf("time is %g s\n", timer);

  gettimeofday(&timez, NULL);
  sprintf(fnameSize, "%d", size);
  int stringSize = strlen(fnameSize);
  fnameSize[stringSize] = '-';
  sprintf(fnameTime, "%d", (int)timez.tv_sec);
  strcat(fnameTime,"-multi-mandelbrot.ppm");
  stringSize+=(strlen(fnameTime) + 1);
  char newName[100];
  strncpy(newName, fnameSize, stringSize + 1);
  strcat(newName, fnameTime);
  newName[stringSize + 1] = '\0';

  write_ppm(newName, img, size, size);

  //write_ppm("multi_test.ppm", img, size, size);
  free(pallet);

  // for(int i = 0; i < size; i++) {
  //   free(img[i]);
  // }
  free(img);
  if (shmdt(buffer) == -1) {
    perror("Error: cannot detatch from shared memory\n");
    exit(1);
  }
  
  if(shmctl(shmid, IPC_RMID, 0) == -1) {
    perror("Error: cannot remove shared memory\n");
    exit(1);
  }   
  pallet = NULL;
  img = NULL;
}
