//1

#include <stdio.h>
#include <stdlib.h>

#define MAX_REQUESTS 100

// Function to calculate total head movements using FCFS
int calculateHeadMovements(int requests[], int n, int head_position) {
    int total_head_movements = 0;

    // Calculate head movements sequentially
    for (int i = 0; i < n; ++i) {
        total_head_movements += abs(requests[i] - head_position);
        head_position = requests[i];
    }

    return total_head_movements;
}

int main() {
    int num_blocks, head_position;
    int requests[MAX_REQUESTS];

    // Accept input from user
    printf("Enter the total number of disk blocks: ");
    scanf("%d", &num_blocks);

    printf("Enter the disk request string:\n");
    for (int i = 0; i < num_blocks; ++i) {
        scanf("%d", &requests[i]);
    }

    printf("Enter the current head position: ");
    scanf("%d", &head_position);

    // Calculate total head movements
    int total_head_movements = calculateHeadMovements(requests, num_blocks, head_position);

    // Display the ordered list of requests
    printf("Ordered list of requests: ");
    for (int i = 0; i < num_blocks; ++i) {
        printf("%d ", requests[i]);
    }
    printf("\n");

    // Display total number of head movements
    printf("Total number of head movements: %d\n", total_head_movements);

    return 0;
}


//2

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define ARRAY_SIZE 1000

int main(int argc, char *argv[]) {
    int rank, size;
    int numbers[ARRAY_SIZE];
    int local_min, global_min;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Seed random number generator with rank-specific seed
    srand(rank);

    // Generate random numbers
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        numbers[i] = rand() % 1000;
    }

    // Find local minimum
    local_min = numbers[0];
    for (int i = 1; i < ARRAY_SIZE; ++i) {
        if (numbers[i] < local_min) {
            local_min = numbers[i];
        }
    }

    // Reduce local minimums to find global minimum
    MPI_Reduce(&local_min, &global_min, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Global minimum number: %d\n", global_min);
    }

    MPI_Finalize();
    return 0;
}
