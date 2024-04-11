//1

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define ARRAY_SIZE 1000

int main(int argc, char *argv[]) {
    int rank, size;
    int i, sum = 0, local_sum = 0;
    double average, local_average;
    int array[ARRAY_SIZE];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Initialize random number generator differently for each process
    srand(rank);

    // Generate random numbers and calculate local sum
    for (i = 0; i < ARRAY_SIZE; i++) {
        array[i] = rand() % 100; // Generate random number between 0 and 99
        local_sum += array[i];
    }

    // Reduce local sum to get global sum
    MPI_Reduce(&local_sum, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // Calculate average
    average = (double)sum / (double)(ARRAY_SIZE * size);

    // Calculate local sum and gather them for average calculation
    MPI_Reduce(&local_sum, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // Calculate local average
    local_average = (double)local_sum / (double)ARRAY_SIZE;

    if (rank == 0) {
        printf("Global sum: %d\n", sum);
        printf("Global average: %.2f\n", average);
        printf("Local average (for process 0): %.2f\n", local_average);
    }

    MPI_Finalize();

    return 0;
}


//2

#include <stdio.h>
#include <stdlib.h>

// Function to sort an array
void sortArray(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

// Function to perform C-SCAN disk scheduling algorithm
void cScan(int arr[], int n, int head, char direction) {
    int total_head_movements = 0;
    int current_pos = head;
    int i, j;

    // Sort the request array
    sortArray(arr, n);

    // Find the index of the head position in the sorted array
    for (i = 0; i < n; i++) {
        if (arr[i] >= head) {
            current_pos = i;
            break;
        }
    }

    // Print the initial position of the head
    printf("Initial Head Position: %d\n", head);

    // Print the requests in the order they are served
    printf("Requests Served:\n");

    // Handle left direction
    if (direction == 'L' || direction == 'l') {
        // Move left until reaching the beginning of the disk
        for (i = current_pos; i >= 0; i--) {
            printf("%d ", arr[i]);
            total_head_movements += abs(current_pos - i);
            current_pos = i;
        }
        // Move to the end of the disk
        printf("0 ");

        // Move right from the end of the disk to the last request
        for (i = n-1; i > current_pos; i--) {
            printf("%d ", arr[i]);
            total_head_movements += abs(current_pos - i);
            current_pos = i;
        }
    }
    // Handle right direction
    else {
        // Move right until reaching the end of the disk
        for (i = current_pos; i < n; i++) {
            printf("%d ", arr[i]);
            total_head_movements += abs(current_pos - i);
            current_pos = i;
        }
        // Move to the beginning of the disk
        printf("199 ");

        // Move left from the beginning of the disk to the first request
        for (i = 0; i < current_pos; i++) {
            printf("%d ", arr[i]);
            total_head_movements += abs(current_pos - i);
            current_pos = i;
        }
    }

    // Print total head movements
    printf("\nTotal Head Movements: %d\n", total_head_movements);
}

int main() {
    int n, head;
    char direction;
    printf("Enter total number of disk blocks: ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter disk request string:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Enter current head position: ");
    scanf("%d", &head);

    printf("Enter direction (L for left, R for right): ");
    scanf(" %c", &direction);

    cScan(arr, n, head, direction);

    return 0;
}
