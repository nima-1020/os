//1
#include <stdio.h>
#include <stdlib.h>

#define MAX_RESOURCES 10
#define MAX_PROCESSES 10

int available[MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int max[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];

int m, n; // Number of processes and resource types

// Function to calculate the need matrix
void calculateNeed() {
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

// Function to display the contents of the need matrix
void displayNeedMatrix() {
    printf("Need Matrix:\n");
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }
}

// Function to check if the request can be granted immediately
int checkRequest(int process, int request[]) {
    for (int i = 0; i < n; ++i) {
        if (request[i] > need[process][i] || request[i] > available[i]) {
            return 0; // Request cannot be granted immediately
        }
    }
    return 1; // Request can be granted immediately
}

int main() {
    // Accept the number of instances for each resource type
    printf("Enter the number of resource types (n): ");
    scanf("%d", &n);
    printf("Enter the number of processes (m): ");
    scanf("%d", &m);

    printf("Enter the number of instances for each resource type:\n");
    for (int i = 0; i < n; ++i) {
        printf("Resource type %d: ", i);
        scanf("%d", &available[i]);
    }

    // Accept allocation matrix
    printf("Enter the allocation matrix:\n");
    for (int i = 0; i < m; ++i) {
        printf("For Process %d:\n", i);
        for (int j = 0; j < n; ++j) {
            scanf("%d", &allocation[i][j]);
        }
    }

    // Accept maximum requirement matrix
    printf("Enter the maximum requirement matrix:\n");
    for (int i = 0; i < m; ++i) {
        printf("For Process %d:\n", i);
        for (int j = 0; j < n; ++j) {
            scanf("%d", &max[i][j]);
        }
    }

    // Calculate the need matrix
    calculateNeed();

    // Display the contents of the need matrix
    displayNeedMatrix();

    // Check if a given request can be granted immediately or not
    int process;
    printf("Enter the process number making the request: ");
    scanf("%d", &process);

    int request[MAX_RESOURCES];
    printf("Enter the request for process %d: ", process);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &request[i]);
    }

    if (checkRequest(process, request)) {
        printf("Request can be granted immediately.\n");
    } else {
        printf("Request cannot be granted immediately.\n");
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
    int local_array[ARRAY_SIZE];
    int max_local, max_global;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Initialize random seed
    srand(rank);

    // Generate local random numbers
    for (int i = 0; i < ARRAY_SIZE; i++) {
        local_array[i] = rand() % 1000; // Generate random numbers between 0 and 999
    }

    // Find local max
    max_local = local_array[0];
    for (int i = 1; i < ARRAY_SIZE; i++) {
        if (local_array[i] > max_local) {
            max_local = local_array[i];
        }
    }

    // Find global max using MPI_Reduce
    MPI_Reduce(&max_local, &max_global, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Maximum number: %d\n", max_global);
    }

    MPI_Finalize();

    return 0;
}
