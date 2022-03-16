#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void init_array(char *arr, int size, char str[], int str_length) {
    int i;
    for (i = 0; i < size; i++) {
        arr[i] = (str[i % str_length]);
    }   
    arr[size-1] = '\0';
}

int main() {

  char str1[33];
  int len;
  char *p; 
  int repeat;

  printf("Enter a word: \n");
  scanf("%s", str1);
  str1[strlen(str1)] = '\0';

  printf("Enter a word count: \n");
  scanf("%d", &repeat);
  len = ((strlen(str1)*repeat));
  //printf("total length: %d\n", len);

  p = malloc(sizeof(char)*len+1);

  if (p == NULL) {
        printf("malloc error\n");
        exit(1);
  }
  init_array(p,len+1,str1,strlen(str1));

  for(int i = 0; i < len; i++) {
    printf("%c", p[i]);
  }

  printf("\n");

  free(p);
  p = NULL;
  return 0;
}