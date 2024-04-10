//1

#include <stdio.h>

#define MAX_RESOURCES 10
#define MAX_PROCESSES 10

int available[MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int max[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];
int num_processes;
int num_resources;

// Function prototypes
void acceptAvailable();
void displayAllocationMax();
void displayNeed();
void displayAvailable();

int main() {
    int choice;

    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);

    printf("Enter the number of resources: ");
    scanf("%d", &num_resources);

    printf("Enter available resources:\n");
    acceptAvailable();

    printf("Enter allocation matrix:\n");
    displayAllocationMax();

    printf("Enter max matrix:\n");
    displayAllocationMax();

    // Calculate need matrix
    for (int i = 0; i < num_processes; i++) {
        for (int j = 0; j < num_resources; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    while (1) {
        printf("\nMenu:\n");
        printf("1. Display Allocation and Max\n");
        printf("2. Display Need Matrix\n");
        printf("3. Display Available Resources\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayAllocationMax();
                break;
            case 2:
                displayNeed();
                break;
            case 3:
                displayAvailable();
                break;
            case 4:
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}

void acceptAvailable() {
    for (int i = 0; i < num_resources; i++) {
        scanf("%d", &available[i]);
    }
}

void displayAllocationMax() {
    printf("Process\tAllocation\tMax\n");
    for (int i = 0; i < num_processes; i++) {
        printf("%d\t", i);
        for (int j = 0; j < num_resources; j++) {
            printf("%d ", allocation[i][j]);
        }
        printf("\t\t");
        for (int j = 0; j < num_resources; j++) {
            printf("%d ", max[i][j]);
        }
        printf("\n");
    }
}

void displayNeed() {
    printf("Process\tNeed\n");
    for (int i = 0; i < num_processes; i++) {
        printf("%d\t", i);
        for (int j = 0; j < num_resources; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }
}

void displayAvailable() {
    printf("Available Resources: ");
    for (int i = 0; i < num_resources; i++) {
        printf("%d ", available[i]);
    }
    printf("\n");
}
//2

#include <stdio.h>
#include <stdlib.h>

// Function to calculate total head movements
int calculateTotalHeadMovements(int *requests, int size, int start) {
    int totalHeadMovements = abs(requests[0] - start);
    
    for (int i = 1; i < size; i++) {
        totalHeadMovements += abs(requests[i] - requests[i - 1]);
    }
    
    return totalHeadMovements;
}

int main() {
    int numRequests, startHead, totalHeadMovements = 0;
    
    // Accepting inputs from the user
    printf("Enter the total number of disk requests: ");
    scanf("%d", &numRequests);
    
    int *requests = (int *)malloc(numRequests * sizeof(int));
    
    printf("Enter the disk request string:\n");
    for (int i = 0; i < numRequests; i++) {
        scanf("%d", &requests[i]);
    }
    
    printf("Enter the start head position: ");
    scanf("%d", &startHead);
    
    // Calculating total head movements
    totalHeadMovements = calculateTotalHeadMovements(requests, numRequests, startHead);
    
    // Displaying the list of requests in the order they are served
    printf("Order of service: ");
    for (int i = 0; i < numRequests; i++) {
        printf("%d ", requests[i]);
    }
    
    printf("\nTotal number of head movements: %d\n", totalHeadMovements);
    
    free(requests);
    return 0;
}
