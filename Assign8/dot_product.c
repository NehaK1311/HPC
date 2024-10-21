#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int rank, size, n = 8;
    int A[8] = {1, 2, 3, 4, 5, 6, 7, 8}; // Example array of size 8
    int local_sum = 0, total_sum = 0;
    
    MPI_Init(&argc, &argv);                  // Initialize MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);    // Get the rank of the process
    MPI_Comm_size(MPI_COMM_WORLD, &size);    // Get the total number of processes
    
    // Ensure there are exactly two processes (P0 and P1)
    if (size != 2) {
        if (rank == 0) {
            printf("This program requires exactly two processes.\n");
        }
        MPI_Finalize();
        return -1;
    }
    
    // Each process computes the sum of half of the array
    if (rank == 0) {
        for (int i = 0; i < n / 2; i++) {
            local_sum += A[i];
        }
    } else if (rank == 1) {
        for (int i = n / 2; i < n; i++) {
            local_sum += A[i];
        }
    }
    
    // Gather the local sums to process 0
    MPI_Reduce(&local_sum, &total_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    
    if (rank == 0) {
        printf("Total sum of array elements is: %d\n", total_sum);
    }
    
    MPI_Finalize();  // Finalize MPI
    return 0;
}
