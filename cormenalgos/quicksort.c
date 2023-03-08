#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int partition(int* A, int p, int r) {
    // pivot element
    int x = A[r];
    int i = p-1;
    for(int j = p; j < r; j++) {
        if (A[j] <= x) {
            i++;
            // swap
            int tmp = A[i];
            A[i] = A[j];
            A[j] = tmp;
        }
    }
    // swap
    int tmp = A[i+1];
    A[i+1] = A[r];
    A[r] = tmp;
    return i+1;
}

int randomizedPartition(int* A, int p, int r) {
    // random integer in range [p,r]
    int i = rand() % (r+1-p)+p;
    //swap 'original' pivot with randomly selected
    int tmp = A[r];
    A[r] = A[i];
    A[i] = tmp;
    return partition(A,p,r);
}


void quickSort(int* A, int p, int r) {
    if (p < r) {
        //or: int q = randomizedPartition(A,p,r);
        int q = partition(A,p,r);
        quickSort(A,p,q-1);
        quickSort(A,q+1,r);
    }
    return;
}


int main() {
    int n = 7;
    int A[] = {5,4,2,3,1,6,7};
    quickSort(A,0,n-1);


    for(int i = 0; i <= n-1; i++) {
        printf("%d ", A[i]);
    }
}