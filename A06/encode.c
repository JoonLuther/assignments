#include <stdio.h>
#include "read_ppm.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

void encode_ppm(const char* filename, struct ppm_pixel* pxs, char *message, int w, int h) {
  FILE *outfile = NULL;
  int *int_array = malloc(sizeof(int) * w * h * 3);
  int maxChars = (w * h * 3)/8;
  int binary_array_length = strlen(message)*8;
  printf("%d\n", binary_array_length);
  print_ppm(filename, pxs, &w, &h);
  int s = strlen(filename);
  char newName[100];
  strncpy(newName, filename, s-4);
  newName[s-4] = '\0';
  strcat(newName,"_ENCODED_TEST.ppm");

  outfile = fopen(newName, "wb");

  if(outfile == NULL) {
    printf("Error: unable to open file %s\n", newName);
    exit(1);
  }

  printf("Writing file %s\n", newName);

  fprintf(outfile, "P6\n%d %d\n255\n", w, h);

  if(strlen(message) > maxChars) {
    printf("Max character limit exceeded\n");
    return;
  }

//Create array of 1s and 0s to represent chars
  for(int i = 0; i < binary_array_length/8; i++) {
    
    for(int j = 0; j < 8; j++) {
      if(message[i] - ((int)pow(2,(8-(j+1)))) >= 0) {
        message[i] -= ((int)pow(2,(8-(j+1)))); 
        int_array[8*i+j] = 1;
      } else {
        //printf("\n(%d - %d) = %d\n", message[i], ((int)pow(2,(8-(j+1)))), message[i] - ((int)pow(2,(8-(j+1)))));
        int_array[8*i+j] = 0;
      }
      printf("%d",int_array[8*i+j]);
    }
    printf("\n");
  }

//Change values in pixel array to have 1s and 0s

  printf("pixel 0: (%d, %d, %d)\n", pxs[0].red, pxs[0].green, pxs[0].blue);

  for(int i = 0; i < w * h; i++) {
    if((3*i + 2) <= binary_array_length) {
      if((pxs[i].red)%2 != int_array[3*i]) {
        if((pxs[i].red)%2 == 0) {
          pxs[i].red += 1;
        } else {
          pxs[i].red -= 1;
        }
      }
      if((pxs[i].green)%2 != int_array[3*i+1]) {
        if((pxs[i].green)%2 == 0) {
          pxs[i].green += 1;
        } else {
          pxs[i].green -= 1;
        }
      }
      if((pxs[i].blue)%2 != int_array[3*i+2]) {
        if((pxs[i].blue)%2 == 0) {
          pxs[i].blue += 1;
        } else {
          pxs[i].blue -= 1;
        }
      }
      //printf("pixel %d: (%d, %d, %d)\n", i, pxs[i].red, pxs[i].green, pxs[i].blue);
    }
  }

  //print_ppm(newName, pxs, &w, &h);

  for(int i = 0; i < (w*h); i++) {
    fwrite(&(pxs[i]), sizeof(struct ppm_pixel), 1, outfile);
  }

  free(int_array);
  int_array = NULL;
  fclose(outfile);
}

int main(int argc, char** argv) {
  int default_dim = 0;
  int width = default_dim;
  int height = default_dim;
  int *w = &width;
  int *h = &height;
  int maxChars;
  struct ppm_pixel *pixels;
  pixels = read_ppm(argv[1], w, h);
  maxChars = ((*w * *h * 3)/8);
  printf("Max number of characters in the image: %d\n", maxChars);
  char *message = argv[2];
  encode_ppm(argv[1], pixels, message, *w, *h);
  printf("%s\n", message);
  free(pixels);
  pixels = NULL;
  return 0;
}

