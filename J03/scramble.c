#include <stdio.h>

int main() {
  char input[1000];
  char output[1000];

  printf("Please enter a phrase: ");
  scanf("%s",input);

  unsigned int lbit;
  unsigned int rbit; 
  unsigned char chr;


  for(int i = 0; i < 4; i++){
    chr = input[i];
    printf("iter: %d\n", i);
    lbit = chr & (1 << 2);
    rbit = chr & (1 << 1);

    printf("left: %d right: %d\n", lbit, rbit);

    if((lbit) != (rbit << 1)){
      printf("1\n");
      // output[i] = chr | (rbit & (lbit >> 1));
      // output[i] = chr | (rbit & (lbit >> 1));
      chr = chr ^ (1 << 2);
      chr = chr ^ (1 << 1);
    } 
    // else {
    //   printf("2\n");
    //   lbit = lbit >> 1;
    //   rbit = rbit << 1;
    //   output[i] = chr | (lbit | (1 << 2));
    //   output[i] = chr | (rbit | (1 << 1));
    // }
    output[i] = chr;
    printf("left: %d right: %d\n", lbit, rbit);
  }
 
  printf("%s\n",output);

  return 0;
}
