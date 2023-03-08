#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void merge(int* A, int p, int q, int r) {
    int n1 = q-p+1;
    int n2 = r-q;

    int* L = malloc((n1+1)*sizeof(int));
    for(int i = 0; i < n1; i++) {
        L[i] = A[p+i];
    }
    int* R = malloc((n2+1)*sizeof(int));
    for(int j = 0; j < n2; j++) {
        R[j] = A[q+j+1];
    }
    int i = 0;
    int j = 0;
    for(int k = p; k <= r; k++) {
        if (L[i] <= R[j]) {
            A[k] = L[i];
            i++;
        }
        else {
            A[k] = R[j];
            j++;
        }
    }
    return;
}


void mergeSort(int* A, int p, int r) {
    if (p < r) {
        int q = floor((p+r)/2);
        mergeSort(A,p,q);
        mergeSort(A,q+1,r);
        merge(A,p,q,r);
    }
    return;
}


int main() {
    int n = 7;
    int A[] = {5,4,2,3,1,2,7};
    mergeSort(A,0,n-1);


    for(int i = 0; i <= n-1; i++) {
        printf("%d ", A[i]);
    }
}