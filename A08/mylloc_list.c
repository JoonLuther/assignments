#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct chunk {
  int size;
  int in_use;
  struct chunk *next;
};
struct chunk *flist = NULL;

void *malloc (size_t size) {
  if (size == 0){
    return NULL;
  }

  struct chunk *next = flist;
  struct chunk *prev = NULL;

  while(next != NULL) {
	  if(next->size >=size) {
		  next->in_use = size;
		  if(prev != NULL) {
			  prev->next = next->next;
		  }  else {
			  flist = next->next;
		  }
		  return (void*)(next + 1);
	  } else {
		  prev = next;
		  next = next->next;
	  }
  }
	
  void *memory = sbrk(size + sizeof(struct chunk));
  if (memory == (void *) -1) {
    return NULL;
  } else {
    struct chunk* cnk = (struct chunk*)memory;
    cnk->size = size;
    cnk->in_use = size;
    return (void*) (cnk + 1);
  }
}

void free(void *memory) {
  if(memory != NULL) {
	  struct chunk *cnk = (struct chunk*)((struct chunk*)memory - 1);
	  cnk->in_use = 0;
	  cnk->next = flist;
	  flist = cnk;
  }
  return;
}

void fragstats(void* buffers[], int len) {
	int totalBlocks = 0;
	int totalFree = 0;
	int totalUsed = 0;
	int idx = 0;
	while(buffers[idx] == NULL) {
		idx++;
	}
	struct chunk *first = (struct chunk*)((struct chunk*)(buffers[idx])-1);
	int intUnused = 0;
	int intMin = first->size;
	int intMax = first->size;
	struct chunk *curr = flist;
	int extUnused = 0;
	int extMin, extMax;

	if(curr != NULL) {
		extMin = curr->size;
		extMax = curr->size;
	}
	
	while(curr != NULL) {
		totalFree++;
		//printf("size of free: %d\n", curr->size);
		extUnused += curr->size;
		if(curr->size > extMax) {
			extMax = curr->size;
		}
		if(curr->size < extMin) {
			extMin = curr->size;
		}
		curr = curr->next;
	}

	for(int i = 0; i < len; i++) {
		if(buffers[i] != NULL) {
			struct chunk *cnk = (struct chunk*)((struct chunk*)(buffers[i])-1);
			//printf("idx: %d, size: %d, in use: %d\n", i, cnk->size, cnk->in_use);
			totalUsed++;
			intUnused += (cnk->size)-(cnk->in_use);

			if(cnk->size > intMax) {
				intMax = cnk->size;
			}
			if(cnk->size < intMin) {
				intMin = cnk->size;
			}
		}
	}

	totalBlocks = totalUsed + totalFree;
	printf("Total blocks: %d Free: %d Used: %d\n", totalBlocks, totalFree, totalUsed);
	printf("Internal unused: total: %d average: %f smallest: %d largest: %d\n", intUnused, (float)(intUnused/len), intMin, intMax);
	printf("External unused: total: %d average: %f smallest: %d largest: %d\n", extUnused, (float)(extUnused/totalFree), extMin, extMax);

}