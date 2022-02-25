#include <stdio.h>
#include <stdlib.h>
//#include <string.h>

int main() {
  char input[10];
  int wordLen = 4;
  unsigned int result = 0x00000000;
  printf("Enter a 4 letter word: ");
  scanf("%s", input);

  for(int i = wordLen-1; i >= 0; i--) {
    unsigned char c = input[i];
    unsigned int d = (c<<(8*(7-i)) & (0xffffffff));
    printf("%c: %x\n",c,d);
    result = (d | result);
  }
  printf("Your Number Is: %d (0x%x)\n", result, result);
  return 0;
}
