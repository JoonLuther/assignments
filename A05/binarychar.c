#include <stdio.h>
#include <math.h>

int main() {
  char c[9];
  int k = 7;
  int dec = 0;

  printf("Enter 8 bits: ");
  scanf("%s",c);

  for(int i = 0; i < 8; i++) {
    if (c[i] == '1') {
      dec = dec + (1*pow(2,k));
      //printf("1* 2^%d = %d\n", k, (int)(1*pow(2,k)));
    } else {
      //printf("0 * 2^%d = %d\n", k, (int)(0*pow(2,k)));
    }
    
    k--;
  }

  printf("Your character is: %c\n ", dec);

  return 0;
}
