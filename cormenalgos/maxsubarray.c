#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Tuple {
    int left;
    int right;
    int maxSum;
}Tuple;


Tuple createTuple(int left, int right, int maxSum) {
    Tuple* tmp = malloc(sizeof(Tuple));
    tmp->left = left;
    tmp->right = right;
    tmp->maxSum = maxSum;
    return *tmp;
}


Tuple maxCrossingSubarray(int* A, int low, int mid, int high) {
    int max_left = -1;
    int max_right = -1;
    int left_sum = -10e6;
    int sum = 0;
    for(int i = mid; i >= low; i--) {
        sum += A[i];
        if(sum > left_sum) {
            left_sum = sum;
            max_left = i;
        }
    }
    int right_sum = -10e6;
    sum = 0;
    for(int j = mid+1; j <= high; j++) {
        sum += A[j];
        if(sum > right_sum) {
            right_sum = sum;
            max_right = j;
        }
    }
    return createTuple(max_left,max_right,left_sum+right_sum);
}

Tuple maxSubarray(int* A, int low, int high) {
    if(high == low) {
        return createTuple(low,high,A[low]);
    }
    int mid = floor((low+high)/2);
    Tuple res1 = maxSubarray(A,low,mid);
    Tuple res2 = maxSubarray(A,mid+1,high);
    Tuple res3 = maxCrossingSubarray(A,low,mid,high);

    if(res1.maxSum >= res2.maxSum && res1.maxSum >= res3.maxSum) {
        return res1;
    }
    else if(res2.maxSum >= res1.maxSum && res2.maxSum >= res3.maxSum) {
        return res2;
    }
    return res3;
}



int main(){
    int n = 16;
    int A[] = {13,-3,-25,20,-3,-16,-23,18,20,-7,12,-5,-22,15,-4,7};

    Tuple res = maxSubarray(A,0,n-1);
    printf("%d %d %d\n",res.left,res.right,res.maxSum);

}