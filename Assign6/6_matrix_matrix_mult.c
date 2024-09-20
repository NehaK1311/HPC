#include <stdio.h>
#include <omp.h>

int main() {
    int i, j, k, N;

    // Input size of the matrices
    printf("Enter the size of the matrices (N x N): ");
    scanf("%d", &N);

    // Declare matrices A, B, and C
    double A[N][N], B[N][N], C[N][N];

    // Input elements of matrix A
    printf("Enter elements of matrix A:\n");
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf("A[%d][%d]: ", i, j);
            scanf("%lf", &A[i][j]);
        }
    }

    // Input elements of matrix B
    printf("Enter elements of matrix B:\n");
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf("B[%d][%d]: ", i, j);
            scanf("%lf", &B[i][j]);
        }
    }

    // Initialize matrix C to zero
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            C[i][j] = 0.0;
        }
    }

    // Perform matrix-matrix multiplication in parallel
    #pragma omp parallel for private(i, j, k) shared(A, B, C)
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            for (k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    // Output the resulting matrix C
    printf("Resultant matrix C after multiplication:\n");
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf("%f ", C[i][j]);
        }
        printf("\n");
    }

    return 0;
}
