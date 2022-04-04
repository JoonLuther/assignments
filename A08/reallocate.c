#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "rand.h"

int main (int argc, char* argv[]) {
	void *init = sbrk(0);
  	void *current;
 	printf("The initial top of the heap is %p.\n", init);
	
       	for(int i = 0; i < 10; i++) {
		int *memory = NULL;
		memory = malloc(100);
		if (memory == NULL) {
        		fprintf(stderr, "malloc failed\n");
       			return(1);
      		}
		*memory = 246;
		free(memory);
	}	

	current = sbrk(0);
	int difference = (int) ((current - init));
	printf("The current top of the heap is %p.\n", current);
	printf("Difference of %d (0x%x) bytes\n", difference, difference);
       	return 0 ;
}