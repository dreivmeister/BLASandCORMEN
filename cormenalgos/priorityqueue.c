#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct PriorityQueue{
    // int array of values
    int* heap;
    int heapSize;
}PriorityQueue;

PriorityQueue* createPriorityQueue(int* A, int n) {
    PriorityQueue* tmp = malloc(sizeof(PriorityQueue));
    tmp->heap = malloc(n*sizeof(int));
    tmp->heapSize = n;

    for(int i = 0; i < n; i++) {
        tmp->heap[i] = A[i];
    }

    return tmp;
}


// returns index of parent from i
int parent(int i){
    (i-1)/2;
}
// returns index of left child from i
int left(int i){
    return 2*i+1;
}
// returns index of right child from i
int right(int i){
    return 2*i+2;
}

// max heap operations

void maxHeapify(PriorityQueue* A,int i) {
    int largest = -1;
    int l = left(i);
    int r = right(i);
    if (l <= A->heapSize && A->heap[l] > A->heap[i]) {
        largest = l;
    }
    else {
        largest = i;
    }
    if (r <= A->heapSize && A->heap[r] > A->heap[largest]) {
        largest = r;
    }
    if (largest != i) {
        int tmp = A->heap[i];
        A->heap[i] = A->heap[largest];
        A->heap[largest] = tmp;
        maxHeapify(A,largest);
    }
}


void buildMaxHeap(PriorityQueue* A) {
    // floor(A->heapSize/2)
    for(int i = A->heapSize/2-1; i >= 0; i--) {
        maxHeapify(A,i);
    }
}


// priority queue operations

int heapMaximum(PriorityQueue* A) {
    return A->heap[0];
}

int heapExtractMax(PriorityQueue* A) {
    if (A->heapSize < 1) {
        printf("heap underflow\n");
        return -1;
    }
    int max = heapMaximum(A);
    A->heap[0] = A->heap[A->heapSize-1];
    A->heapSize--;
    maxHeapify(A,0);
    return max;
}

void heapIncreaseKey(PriorityQueue* A, int i, int key) {
    if (key < A->heap[i]) {
        printf("new key is smaller than current\n");
        return;
    }
    A->heap[i] = key;
    while(i>0 && A->heap[parent(i)] < A->heap[i]) {
        int tmp = A->heap[i];
        A->heap[i] = A->heap[parent(i)];
        A->heap[parent(i)] = tmp;
        i = parent(i);
    }
}


void maxHeapInsert(PriorityQueue* A, int key) {
    A->heapSize++;
    A->heap[A->heapSize-1] = -10e6;
    heapIncreaseKey(A,A->heapSize-1,key);
}



int main() {
    int n = 10;
    int arr[] = {4,1,3,2,16,9,10,14,8,7};

    PriorityQueue* A = createPriorityQueue(arr,n);

    buildMaxHeap(A);

    for(int i = 0; i < n; i++) {
        printf("%d ", A->heap[i]);
    }
    printf("\n");

    heapExtractMax(A);


    for(int i = 0; i < n; i++) {
        printf("%d ", A->heap[i]);
    }
    printf("\n");

    heapIncreaseKey(A, 1, 12);

    for(int i = 0; i < n; i++) {
        printf("%d ", A->heap[i]);
    }
    printf("\n");




}