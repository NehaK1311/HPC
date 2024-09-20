#include <stdio.h>
#include <omp.h>

int main() {
    int i, j, N;

    // Input size of the matrix (N x N) and vector (N)
    printf("Enter the size of the matrix (N x N) and vector (N): ");
    scanf("%d", &N);

    // Declare the matrix A, vector B, and result vector C
    double A[N][N], B[N], C[N];

    // Input elements of matrix A
    printf("Enter elements of matrix A:\n");
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf("A[%d][%d]: ", i, j);
            scanf("%lf", &A[i][j]);
        }
    }

    // Input elements of vector B
    printf("Enter elements of vector B:\n");
    for (i = 0; i < N; i++) {
        printf("B[%d]: ", i);
        scanf("%lf", &B[i]);
    }

    // Initialize result vector C to zero
    for (i = 0; i < N; i++) {
        C[i] = 0.0;
    }

    // Perform matrix-vector multiplication in parallel
    #pragma omp parallel for private(i, j) shared(A, B, C)
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            C[i] += A[i][j] * B[j];
        }
    }

    // Output the resulting vector C
    printf("Resultant vector C after multiplication:\n");
    for (i = 0; i < N; i++) {
        printf("%f ", C[i]);
    }
    printf("\n");

    return 0;
}
