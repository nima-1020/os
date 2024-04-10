//1

#include <stdio.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int available[MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int max[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];
int num_processes, num_resources;

void accept_available() {
    printf("Enter the number of resources: ");
    scanf("%d", &num_resources);

    printf("Enter the available resources:\n");
    for (int i = 0; i < num_resources; i++) {
        scanf("%d", &available[i]);
    }
}

void display_allocation_max() {
    printf("Allocation Matrix:\n");
    for (int i = 0; i < num_processes; i++) {
        for (int j = 0; j < num_resources; j++) {
            printf("%d ", allocation[i][j]);
        }
        printf("\n");
    }

    printf("Max Matrix:\n");
    for (int i = 0; i < num_processes; i++) {
        for (int j = 0; j < num_resources; j++) {
            printf("%d ", max[i][j]);
        }
        printf("\n");
    }
}

void display_need() {
    printf("Need Matrix:\n");
    for (int i = 0; i < num_processes; i++) {
        for (int j = 0; j < num_resources; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }
}

void display_available() {
    printf("Available resources:\n");
    for (int i = 0; i < num_resources; i++) {
        printf("%d ", available[i]);
    }
    printf("\n");
}

int main() {
    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);

    printf("Enter allocation matrix:\n");
    for (int i = 0; i < num_processes; i++) {
        for (int j = 0; j < num_resources; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("Enter max matrix:\n");
    for (int i = 0; i < num_processes; i++) {
        for (int j = 0; j < num_resources; j++) {
            scanf("%d", &max[i][j]);
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    char choice;
    do {
        printf("\nMenu:\n");
        printf("a) Accept Available\n");
        printf("b) Display Allocation, Max\n");
        printf("c) Display the contents of need matrix\n");
        printf("d) Display Available\n");
        printf("x) Exit\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);

        switch (choice) {
            case 'a':
                accept_available();
                break;
            case 'b':
                display_allocation_max();
                break;
            case 'c':
                display_need();
                break;
            case 'd':
                display_available();
                break;
            case 'x':
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice\n");
        }
    } while (choice != 'x');

    return 0;
}


//2

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

#define ARRAY_SIZE 1000

int main(int argc, char *argv[]) {
    int rank, size;
    int numbers[ARRAY_SIZE];
    int local_min, global_min;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Seed the random number generator with rank-specific seed
    srand(time(NULL) + rank);

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

    // Perform reduction to find global minimum
    MPI_Reduce(&local_min, &global_min, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Global minimum number: %d\n", global_min);
    }

    MPI_Finalize();
    return 0;
}
