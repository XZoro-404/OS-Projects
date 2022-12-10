/*
Authors: Ben Richmond and Christian Black
Assignment No.: 4
Date: 12/8/22
Name of File: Data.h
Short Description:
    Contains the values for the assumed max Ram size and PT (page table) max size, a structure for the Entry to the arrays, and
        the structure for the exiting queue
*/

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
