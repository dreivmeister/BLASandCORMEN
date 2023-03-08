#pragma once

typedef struct Heap{
    int* arr;
    int count;
    int capacity;
}Heap;


Heap* createHeap(int capacity);
void insert(Heap* h, int key);
int popMin(Heap *h);
void printHeap(Heap *h);