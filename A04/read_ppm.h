#ifndef PPM_READ_H_
#define PPM_READ_H_

struct ppm_pixel {
  unsigned char red;
  unsigned char green;
  unsigned char blue;
};

extern struct ppm_pixel* read_ppm(const char* filename, int* w, int* h);
extern void print_ppm(const char* filename, struct ppm_pixel *pix, int* w, int* h);
#endif

