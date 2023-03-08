#include <stdio.h>
#include <stdlib.h>


void countingSort(int* A, int* B, int n, int k) {
    // A is input array 
    // B is output array
    // all elems in range [0,k]

    int* C = malloc((k+2)*sizeof(int));

    for(int i = 0; i <= k; i++) {
        C[i] = 0;
    }
    for(int j = 0; j < n; j++) {
        C[A[j]]++;
    }
    for(int i = 1; i <= k; i++) {
        C[i] += C[i-1];
    }
    for(int j = n-1; j >= 0; j--) {
        B[C[A[j]]-1] = A[j];
        C[A[j]]--;
    }
}





int main(){
    int n = 8;
    int k = 5;
    int A[] = {2,5,3,0,2,3,0,3};
    int* B = malloc(n*sizeof(int));

    countingSort(A,B,n,k);


    for(int i = 0; i < n; i++) {
        printf("%d ",B[i]);
    }

}