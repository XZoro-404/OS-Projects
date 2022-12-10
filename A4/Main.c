#include "Data.h"

Entry fTable[PT_SIZE], lTable[PT_SIZE];
int ffCount = 0, lfCount = 0;
ExitQueue* fqueue, *lqueue;

void lru_found_first(Entry* current) {
  
  lqueue->first = current->next;
  lqueue->last->next = current;
  current->next = NULL;
  lqueue->last = current;

}

void lru_found_middle(Entry* current, Entry* previous) {

  previous->next = current->next;
  lqueue->last->next = current;
  current->next = NULL;
  lqueue->last = current;

}

void full(ExitQueue *queue, Entry* used) {

  queue->first->valid = 0;
  used->frameNum = queue->first->frameNum;
  queue->first = queue->first->next;
  queue->last->next = used;
  used->valid = 1;
  queue->last = used;

}

void partial(ExitQueue *queue, Entry* used) {

  used->valid = 1;
  queue->last->next = used;
  queue->last = used;
  used->frameNum = queue->length;
  queue->length++;

}

void lru_use(Entry* used) {

  Entry *previous = NULL;
  Entry *current = lqueue->first;
  if(current == NULL) {

    lqueue->first = used;
    lqueue->last = used;
    lqueue->length++;
    lfCount++;
    return;

  }
  
  if (used->valid) {
    
    for(int idx = 0; idx < lqueue->length - 1; idx++) {

      if (used->pageNum == current->pageNum) {

	if (previous == NULL) {

	  lru_found_first(current);
	  return;

	}
      
	else {

	  lru_found_middle(current, previous);
	  return;

	}
      
      }

      else{
        
        previous = current;
	current = current->next;
      }
      
    }
    
    return;
    
  }
  
  if (lqueue->length == RAM_SIZE) {
  
    full(lqueue, used);
    lfCount++;
    
  }
  
  else {
  
    partial(lqueue, used);
    lfCount++;
    
  }
  
}

void fifo_use(Entry* used) {
  
  if(fqueue->first == NULL) {

    fqueue->first = used;
    fqueue->last = used;
    fqueue->length++;
    ffCount++;
    return;

  }
  
  if(!used->valid) {
  
    if (fqueue->length == RAM_SIZE) {
  
      full(fqueue, used);
      ffCount++;
    
    }
  
    else {
  
      partial(fqueue, used);
      ffCount++;
    
    }
  
  }

}

int run(char* fileName, int mode) {

  FILE* readFile = fopen(fileName, "r");
  FILE* writeFile;
  if (mode)
    writeFile = fopen("FIFO_PhysicalAdresses.txt", "w");
  else
    writeFile = fopen("LRU_PhysicalAdresses.txt", "w");

  if (readFile == NULL){

    printf("Input file does not exist\n");
    exit(1);

  }

  char numText[10];
  while (fgets(numText, 10, readFile) != NULL) {
	
    int readNum = atoi(numText)>>8;
    if (mode) {
    
      fifo_use(&fTable[readNum]);
      fprintf(writeFile, "%d\n", fTable[readNum].frameNum);
      
    }
      
    else {
    
      lru_use(&lTable[readNum]);
      fprintf(writeFile, "%d\n", lTable[readNum].frameNum);
    
    }

  }
  
  fclose(readFile);
  fclose(writeFile);
  if (mode)
    printf("The page faults for FIFO are: %d\n", ffCount);
  else
    printf("The page faults for LRU are: %d\n", lfCount);
  
}

ExitQueue initialize_queue() {

  ExitQueue original;
  original.first = NULL;
  original.last = NULL;
  original.length = 0;
  return original;

}

void initialize_table(Entry* table) {

  for (int idx = 0; idx < PT_SIZE; idx++) {
  
    table[idx].valid = 0;
    table[idx].frameNum = 0;
    table[idx].pageNum = idx;
    table[idx].next = NULL;
  
  }
  
}

int main(int argc, char** argv) {
  
  ExitQueue lOg = initialize_queue(), fOg = initialize_queue();
  
  lqueue = &lOg;
  fqueue = &fOg;
  
  initialize_table(lTable);
  initialize_table(fTable);

  run(argv[1], 0);
  run(argv[1], 1);

}
