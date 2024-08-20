#include <stdio.h>
#include <omp.h>

// Recursive function to compute Fibonacci numbers
int fib(int n) {
    int x, y;
    if (n <= 1)
        return n;
    else {
        #pragma omp task shared(x) // Creating a parallel task
        x = fib(n-1);
        
        #pragma omp task shared(y) // Creating another parallel task
        y = fib(n-2);
        
        #pragma omp taskwait // Ensuring both tasks are completed before summing up
        return x + y;
    }
}

int main() {
    int n = 10;
    int result;
    
    #pragma omp parallel // Start a parallel region
    {
        #pragma omp single // Ensure only one thread executes the fib function initially
        result = fib(n);
    }
    
    printf("Fibonacci number for %d is %d\n", n, result);
    return 0;
}
