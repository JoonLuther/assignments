#include <stdio.h>
#include <stdlib.h>
#include "read_ppm.h"
#include <math.h>

unsigned char * decode_ppm(struct ppm_pixel *pix, int *w, int *h) {
  int *int_array = malloc(sizeof(int) * *w * *h *3);
  unsigned char *ch_array = malloc((sizeof(char)* *w * *h *3)/8);
  int curr_ch;

  for(int i = 0; i < (*w * *h); i++) {
    int_array[3*i] = (pix[i].red)%2;
    int_array[(3*i+1)] = (pix[i].green)%2;
    int_array[3*i+2] = (pix[i].blue)%2;
  }

  for(int i = 0; i < ((sizeof(char)* *w * *h *3)/8); i++) {
    curr_ch = 0;
    for(int j = 0; j < 8; j++) {
      printf("%d", int_array[8 * i + j]);
      curr_ch += (int_array[(8*i)+j]*(int)(pow(2,(8-(j+1)))));
    }
    printf("\n");
    ch_array[i] = curr_ch;
  }

  free(int_array);
  int_array = NULL;
  return ch_array;

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
  unsigned char *message = NULL;
  message = decode_ppm(pixels, w, h);
  printf("%s\n", message);
  free(pixels);
  free(message);
  pixels = NULL;
  return 0;
}

