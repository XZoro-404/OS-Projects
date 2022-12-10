/*
Authors: Ben Richmond and Christian Black
Assignment No.: 4
Date: 12/8/22
Name of File: Main.c
Short Description:
 This program simulates what it is like to demand paging from the MMU by the use of frame allocation for pages.
 A page fault occurs when this program looks up a page to check if it is on the ram and if not a page fault is created.
 If there is not a free frame when a page fault occurs a page will be removed from the Ram using either the FIFO
    (First in First out) page replacement policy or the LRU (Least Recently Used) page replacement policy.
The user will provide an input file that contains integers that represent addresses (16 bits long)represented by a cpu.
*/

#include "Data.h"

Entry fTable[PT_SIZE], lTable[PT_SIZE]; // Two arrays with the size of PT_Size
int ffCount = 0, lfCount = 0; //
ExitQueue* fqueue, *lqueue;

/*
	Function Name: lru_found_first
	Input to Method: Takes in the current Entry pointer
	Output: N/A
	Brief Description: Finds the
 */
void lru_found_first(Entry* current) {
  
  lqueue->first = current->next;
  lqueue->last->next = current;
  current->next = NULL;
  lqueue->last = current;

}

/*
	Function Name: lru_found_middle
	Input to Method:
	Output:
	Brief Description:
 */
void lru_found_middle(Entry* current, Entry* previous) {

  previous->next = current->next;
  lqueue->last->next = current;
  current->next = NULL;
  lqueue->last = current;

}

/*
	Function Name: full
	Input to Method:
	Output: N/A
	Brief Description: Indicates that a queue is full
 */
void full(ExitQueue *queue, Entry* used) {

  queue->first->valid = 0;
  used->frameNum = queue->first->frameNum;
  queue->first = queue->first->next;
  queue->last->next = used;
  used->valid = 1;
  queue->last = used;

}

/*
	Function Name: partial
	Input to Method:
	Output: N/A
	Brief Description:
 */
void partial(ExitQueue *queue, Entry* used) {

  used->valid = 1;
  queue->last->next = used;
  queue->last = used;
  used->frameNum = queue->length;
  queue->length++;

}

/*
	Function Name: lru_use
	Input to Method:
	Output: N/A
	Brief Description:
 */
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

/*
	Function Name: fifo_use
	Input to Method:
	Output: N/A
	Brief Description:
 */
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

/*
	Function Name: ExitQueue
	Input to Method:
	Output: prints the amount of page faults and writes to two different files (a FIFO file and a LRU file)
	Brief Description: writes to the
 */
int run(char* fileName, int mode) {
  //opens the readfile which is the file provided by the user
  FILE* readFile = fopen(fileName, "r");
  // initializes FILE pointer named writeFile
  FILE* writeFile;
  if (mode)
    // Opens the file FIFO_FIFO_PhysicalAdresses.txt in write mode
    writeFile = fopen("FIFO_PhysicalAdresses.txt", "w");
  else
    // Opens the file LRU_PhysicalAdresses.txt in write mode
    writeFile = fopen("LRU_PhysicalAdresses.txt", "w");

  // Checks if the user provided file exists
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

  // Closes the files
  fclose(readFile);
  fclose(writeFile);
  if (mode)
    printf("The number of page faults for FIFO was: %d\n", ffCount); // prints the amount of page faults for FIFO
  else
    printf("The number of page faults for LRU was: %d\n", lfCount); // prints the amount of page faults for LRU
  
}

/*
	Function Name: ExitQueue
	Input to Method:
	Output:
	Brief Description:
 */
ExitQueue initialize_queue() {

  ExitQueue original;
  original.first = NULL;
  original.last = NULL;
  original.length = 0;
  return original;

}

/*
	Function Name: initialize_table
	Input to Method:
	Output: N/A
	Brief Description: Used to initialize both tables for FIFO and LRU
 */
void initialize_table(Entry* table) {

  for (int idx = 0; idx < PT_SIZE; idx++) {
  
    table[idx].valid = 0;
    table[idx].frameNum = 0;
    table[idx].pageNum = idx;
    table[idx].next = NULL;
  
  }
  
}

/*
	Function Name: main
	Input to Method:
	Output:
	Brief Description:
 */
int main(int argc, char** argv) {
  
  ExitQueue lOg = initialize_queue(), fOg = initialize_queue();
  
  lqueue = &lOg;
  fqueue = &fOg;
  
  initialize_table(lTable);
  initialize_table(fTable);

  run(argv[1], 0);
  run(argv[1], 1);

}
