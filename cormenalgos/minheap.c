/* Sudhanshu Patel sudhanshuptl13@gmail.com */
#include<stdio.h>
#include<stdlib.h>
#include "minheap.h"

/*
 Array Implementation of MinHeap data Structure
*/


Heap* createHeap(int capacity){
    Heap* h = (Heap*) malloc(sizeof(Heap)); //one is number of heap

    //check if memory allocation is fails
    if(h == NULL){
        printf("Memory Error (heap)!");
        return NULL;
    }

    h->count = 0;
    h->capacity = capacity;
    h->arr = (int*) malloc(capacity*sizeof(int)); //size in bytes

    //check if allocation succeed
    if (h->arr == NULL){
        printf("Memory Error (heap arr)!");
        return NULL;
    }
    return h;
}

void heapifyBottomTop(Heap *h, int index){
    int temp;
    int parent_node = (index-1)/2;

    if(h->arr[parent_node] > h->arr[index]){
        //swap and recursive call
        temp = h->arr[parent_node];
        h->arr[parent_node] = h->arr[index];
        h->arr[index] = temp;
        heapifyBottomTop(h, parent_node);
    }
}

void heapifyTopBottom(Heap *h, int parent_node){
    int left = parent_node*2+1;
    int right = parent_node*2+2;
    int min;
    int temp;

    if(left >= h->count || left <0)
        left = -1;
    if(right >= h->count || right <0)
        right = -1;

    if(left != -1 && h->arr[left] < h->arr[parent_node])
        min = left;
    else
        min = parent_node;
    if(right != -1 && h->arr[right] < h->arr[min])
        min = right;

    if(min != parent_node){
        temp = h->arr[min];
        h->arr[min] = h->arr[parent_node];
        h->arr[parent_node] = temp;

        // recursive  call
        heapifyTopBottom(h, min);
    }
}


void insert(Heap* h, int key){
    if(h->count < h->capacity){
        h->arr[h->count] = key;
        heapifyBottomTop(h, h->count);
        h->count++;
    }
}


int popMin(Heap *h){
    if(h->count==0){
        printf("\n__Heap is Empty__\n");
        return -1;
    }
    // replace first node by last and delete last
    int pop = h->arr[0];
    h->arr[0] = h->arr[h->count-1];
    h->count--;
    heapifyTopBottom(h, 0);
    return pop;
}

void printHeap(Heap *h){
    printf("____Print Heap____\n");
    for(int i = 0; i < h->count; i++){
        printf("%d -> ",h->arr[i]);
    }
    printf("\n");
}






// int main(){
//     Heap *heap = createHeap(20); //Min Heap
//     if( heap == NULL ){
//         printf("__Memory Issue____\n");
//         return -1;
//     }

//     for(int i = 9; i >= 0; i--)
//         insert(heap, i);

//     printHeap(heap);

//     for(int i = 9; i >= 0; i--){
//         printf("Pop Minima : %d\n", popMin(heap));
//         printHeap(heap);
//     }
//     return 0;
// }