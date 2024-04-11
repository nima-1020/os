//1

#include <stdio.h>

#define PROCESSES 5 // Number of processes
#define RESOURCES 3 // Number of resources

int available[RESOURCES];
int max[PROCESSES][RESOURCES];
int allocation[PROCESSES][RESOURCES];
int need[PROCESSES][RESOURCES];
int finish[PROCESSES] = {0};

// Function to calculate the need matrix
void calculateNeed() {
    for (int i = 0; i < PROCESSES; ++i) {
        for (int j = 0; j < RESOURCES; ++j) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

// Function to check if the system is in a safe state
int isSafe() {
    int work[RESOURCES];
    for (int i = 0; i < RESOURCES; ++i) {
        work[i] = available[i];
    }

    int safeSeq[PROCESSES];
    int count = 0;

    while (count < PROCESSES) {
        int found = 0;
        for (int i = 0; i < PROCESSES; ++i) {
            if (!finish[i]) {
                int j;
                for (j = 0; j < RESOURCES; ++j) {
                    if (need[i][j] > work[j])
                        break;
                }

                if (j == RESOURCES) {
                    for (int k = 0; k < RESOURCES; ++k) {
                        work[k] += allocation[i][k];
                    }
                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if (!found)
            return 0; // System is not in a safe state
    }

    // System is in a safe state
    printf("Safe Sequence: ");
    for (int i = 0; i < PROCESSES; ++i) {
        printf("%d ", safeSeq[i]);
    }
    printf("\n");
    return 1;
}

int main() {
    // Initialize available resources
    printf("Enter the available resources:\n");
    for (int i = 0; i < RESOURCES; ++i) {
        scanf("%d", &available[i]);
    }

    // Initialize max matrix
    printf("Enter the maximum resources required for each process:\n");
    for (int i = 0; i < PROCESSES; ++i) {
        printf("For Process %d:\n", i);
        for (int j = 0; j < RESOURCES; ++j) {
            scanf("%d", &max[i][j]);
        }
    }

    // Initialize allocation matrix
    printf("Enter the currently allocated resources for each process:\n");
    for (int i = 0; i < PROCESSES; ++i) {
        printf("For Process %d:\n", i);
        for (int j = 0; j < RESOURCES; ++j) {
            scanf("%d", &allocation[i][j]);
        }
    }

    // Calculate need matrix
    calculateNeed();

    // Display the need matrix
    printf("Need Matrix:\n");
    for (int i = 0; i < PROCESSES; ++i) {
        for (int j = 0; j < RESOURCES; ++j) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    // Check if the system is in a safe state and display safe sequence if so
    if (isSafe()) {
        printf("The system is in a safe state.\n");
    } else {
        printf("The system is not in a safe state.\n");
    }

    return 0;
}


//2
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define ARRAY_SIZE 1000

int main(int argc, char *argv[]) {
    int rank, size;
    int *numbers = NULL;
    int local_sum = 0;
    int global_sum = 0;
    double average = 0.0;
    int i;
    
    // Initialize MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    // Allocate memory for numbers
    if (rank == 0) {
        numbers = (int *)malloc(ARRAY_SIZE * sizeof(int));
        if (numbers == NULL) {
            printf("Memory allocation failed.\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
        // Generate random numbers
        for (i = 0; i < ARRAY_SIZE; ++i) {
            numbers[i] = rand() % 100; // Random numbers between 0 and 99
        }
    }
    
    // Scatter the array to all processes
    MPI_Scatter(numbers, ARRAY_SIZE/size, MPI_INT, numbers, ARRAY_SIZE/size, MPI_INT, 0, MPI_COMM_WORLD);
    
    // Calculate local sum
    for (i = 0; i < ARRAY_SIZE/size; ++i) {
        local_sum += numbers[i];
    }
    
    // Reduce local sums to calculate global sum
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    
    // Calculate average
    if (rank == 0) {
        average = (double)global_sum / ARRAY_SIZE;
    }
    
    // Print results
    if (rank == 0) {
        printf("Total sum: %d\n", global_sum);
        printf("Average: %f\n", average);
    }
    
    // Free allocated memory
    if (rank == 0) {
        free(numbers);
    }
    
    // Finalize MPI
    MPI_Finalize();
    
    return 0;
}
