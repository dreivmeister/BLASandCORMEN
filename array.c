#include <stdio.h>
#include <stdlib.h>


struct dtype {
    int type;
};
typedef struct dtype dtype;






struct ituple {
    int* tuple;
    int dim;
};
typedef struct ituple ituple;

void print_tuple(ituple* tup) {
    for(int i = 0; i < tup->dim; i++) {
        printf("%d ",tup->tuple[i]);
    }
}

ituple* new_int_tuple(int dim) {
    ituple* ptr = malloc(sizeof(ituple));
    ptr->tuple = malloc(dim*sizeof(int));
    ptr->dim = dim;
    return ptr;
}

int num_elements(ituple* tup) {
    int num_elements = 1;
    for (int i = 0; i < tup->dim; i++) {
        num_elements *= tup->tuple[i];
    }
    return num_elements;
}

void construct_shape(ituple* sh, int* vals) {
    for (int i = 0; i < sh->dim; i++) {
        sh->tuple[i] = vals[i];
    }
}

ituple* construct_strides(ituple* sh) {
    ituple* strides = malloc(sh->dim*sizeof(int));

    if (sh->dim == 1) {
        strides->tuple[0] = sizeof(double);
    }
    else if(sh->dim == 2) {
        //i dont know what to do so for now only 2D
        strides->tuple[0] = sh->tuple[1]*sizeof(double);
        strides->tuple[1] = sizeof(double);
    }
    else if (sh->dim == 3) {
        strides->tuple[0] = sh->tuple[1]*sizeof(double);
        strides->tuple[1] = sizeof(double);
        strides->tuple[2] = (sh->tuple[0]*sh->tuple[1])*sizeof(double);
    }
    strides->dim = sh->dim;

    return strides;
}

// only double arrays
// type = double
struct array
{
    double* data;
    dtype* data_type;
    ituple* shape;
    ituple* strides;
};
typedef struct array array;

array* new_array(ituple* shape) {
    array* ptr = malloc(sizeof(array));
    ptr->data = malloc(num_elements(shape) * sizeof(double));
    ptr->shape = shape;
    ptr->strides = construct_strides(shape);
    ptr->data_type = malloc(sizeof(dtype));
    return ptr;
}

double get_value_2d(array* arr, int r, int c) {
    return arr->data[r*arr->shape->tuple[1]+c];
}





int main() {
    printf("%f\n",1);
    int dim = 3;
    ituple* sh1 = new_int_tuple(dim);
    int vals[] = {2,2,2}; // shape
    construct_shape(sh1, vals);
    //print_tuple(sh1);
    array* arr1 = new_array(sh1);

    for(int i = 0; i < 6; i++) {
        arr1->data[i] = i;
    }
    print_tuple(arr1->shape);
    print_tuple(arr1->strides);
    printf("\n");

    //int v1[][] = {{4,4},{4,4}};

    for(int k = 0; k < 2; k++) {
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            printf("%f ", get_value_2d(arr1,i,j));
        }
        printf("\n");
    }
    }

    // for(int i = 0; i < 4*4; i++) {
    //     printf("%f ", arr1->data[i]);
    // }


    // int r = 2;
    // int c = 2;
    // array* arr = new_array(sh);
    // /* Putting 1 to (r*c) in the 1D array in a sequence */
    // for (int i = 0; i < r * c; i++)
    //     arr->data[i] = i + 1;

    // printf("%f\n", get_value_2d(arr,0,0));
    // printf("%f\n", get_value_2d(arr,1,0));

    // /* Accessing the array values as if it was a 2D array */
    // for (int i = 0; i < r; i++) {
    //     for (int j = 0; j < c; j++)
    //         printf("%f ", get_value_2d(arr,i,j));
    //     printf("\n");
    // }

    free(arr1);
    free(sh1);
    return 0;
}