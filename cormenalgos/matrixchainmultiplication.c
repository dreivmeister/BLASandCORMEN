#include <stdio.h>
#include <stdlib.h>

// Function for printing the optimal
// parenthesization of a matrix chain product
void printParenthesis(int i, int j, int n, int* bracket)
{
	// If only one matrix left in current segment
	if (i == j) {
		printf("A%d",i);
		return;
	}

	printf("(");
	// Recursively put brackets around subexpression
	// from i to bracket[i][j].
	// Note that "*((bracket+i*n)+j)" is similar to
	// bracket[i][j]
	printParenthesis(i, *((bracket + i * n) + j), n,
					bracket);

	// Recursively put brackets around subexpression
	// from bracket[i][j] + 1 to j.
	printParenthesis(*((bracket + i * n) + j) + 1, j, n,
					bracket);
	printf(")");
}

void matrixChainOrder(int p[], int n)
{
	/* For simplicity of the program, one extra
	row and one extra column are allocated in
		m[][]. 0th row and 0th column of m[][]
		are not used */
	int m[n][n];

	// bracket[i][j] stores optimal break point in
	// subexpression from i to j.
	int bracket[n][n];

	/* m[i,j] = Minimum number of scalar multiplications
	needed to compute the matrix A[i]A[i+1]...A[j] =
	A[i..j] where dimension of A[i] is p[i-1] x p[i] */

	// cost is zero when multiplying one matrix.
	for (int i = 1; i < n; i++)
		m[i][i] = 0;

	// L is chain length.
	for (int L = 2; L < n; L++)
	{
		for (int i = 1; i < n - L + 1; i++)
		{
			int j = i + L - 1;
			m[i][j] = INT_MAX;
			for (int k = i; k <= j - 1; k++)
			{
				// q = cost/scalar multiplications
				int q = m[i][k] + m[k + 1][j]
						+ p[i - 1] * p[k] * p[j];
				if (q < m[i][j])
				{
					m[i][j] = q;

					// Each entry bracket[i,j]=k shows
					// where to split the product arr
					// i,i+1....j for the minimum cost.
					bracket[i][j] = k;
				}
			}
		}
	}

	printf("Optimal Parenthesization is: ");
	printParenthesis(1, n - 1, n, (int*)bracket);
	printf("\nOptimal Cost is: %d\n",m[1][n - 1]);
}

int* matrix_multiply(int* A, int ar, int ac, int* B, int br, int bc) {
	if(ac != br) {
		printf("incompatible dimensions");
		return NULL;
	}
	// new matrix
	int* C = (int*)malloc(sizeof(int) * ar * bc);

	for(int i = 0; i < ar; i++) {
		for(int j = 0; j < bc; j++) {
			int cij = 0;
			for(int k = 0; k < ac; k++) {
				cij += A[i * ac + k] * B[k * bc + j];
			}
			C[i * bc + j] = cij;
		}
	}
	return C;
}

void print_matrix(int* A, int ar, int ac) {
	for(int i = 0; i < ar; i++) {
		for(int j = 0; j < ac; j++) {
			printf("%d ", A[i * ac + j]);
		}
		printf("\n");
	}
}


// Driver code
int main()
{
	int arr[] = {2,3,2,2};
	int n = sizeof(arr) / sizeof(arr[0]);
	matrixChainOrder(arr, n);

	int A[2][3] = {{1,2,5},
				   {3,4,7}};
	int B[3][2] = {{3,4},
				   {5,6},
				   {5,6}};
	int C[2][2] = {{3,4},
				   {5,6}};
	

	int* D1 = matrix_multiply(matrix_multiply((int*)A,2,3,(int*)B,3,2),2,2,(int*)C,2,2);
	int* D2 = matrix_multiply((int*)A,2,3,matrix_multiply((int*)B,3,2,(int*)C,2,2),3,2);

	print_matrix(D1,2,2);
	print_matrix(D2,2,2);
}
