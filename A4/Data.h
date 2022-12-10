#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define RAM_SIZE 32
#define PT_SIZE 256

typedef struct Entry{

  int valid, frameNum, pageNum;
  struct Entry* next;

} Entry;

typedef struct ExitQueue{

  Entry* first, *last;
  int length;

} ExitQueue;
