#include <stdio.h>
#include <stdlib.h>
#include "minheap.h"


typedef struct Symbol{
    char symbol;
    int freq;
}Symbol;



typedef struct HuffNode {
    int key;
    Symbol* symbol;
    struct HuffNode* left;
    struct HuffNode* right;
}HuffNode;

HuffNode* huffman(Symbol* C, int n) {
    Heap* Q = createHeap(n);

}




int main() {
    Heap* tmp = createHeap(10);
    insert(tmp,10);
    insert(tmp,9);
    printHeap(tmp);
}