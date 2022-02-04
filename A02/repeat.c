#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void init_array(char *arr, int size, char str[], int str_length) {
    int i;
    for (i = 0; i < size; i++) {
        arr[i] = (str[i % str_length]);
    }
}

int main() {

  char str1[33];
  int len;
  char *p;
  int totalSize;
  int repeat;

  printf("Enter a word: \n");
  scanf("%s", str1);
  printf("Enter a word count: \n");
  scanf("%d", &repeat);
  len = ((strlen(str1)*repeat) + 1);

  p = malloc(sizeof(char)*len);
  if (p == NULL) {
        printf("malloc error\n");
        exit(1);
  }
  init_array(p,len,str1,strlen(str1));

  for(int i = 0; i < len*repeat; i++) {
    printf("%c", p[i]);
  }

  printf("\n");

  free(p);
  p = NULL;
  return 0;
}
