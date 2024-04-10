//1

#include <stdio.h>
#include <stdlib.h>

#define RESOURCES 3 // Number of resources
#define PROCESSES 5 // Number of processes

int available[RESOURCES] = {7, 2, 6};
int allocation[PROCESSES][RESOURCES];
int max[PROCESSES][RESOURCES];
int need[PROCESSES][RESOURCES];

// Function to accept allocation matrix from the user
void acceptAllocation() {
    printf("Enter Allocation Matrix:\n");
    for (int i = 0; i < PROCESSES; ++i) {
        printf("For Process %d: ", i);
        for (int j = 0; j < RESOURCES; ++j) {
            scanf("%d", &allocation[i][j]);
        }
    }
}

// Function to accept maximum matrix from the user
void acceptMax() {
    printf("Enter Maximum Matrix:\n");
    for (int i = 0; i < PROCESSES; ++i) {
        printf("For Process %d: ", i);
        for (int j = 0; j < RESOURCES; ++j) {
            scanf("%d", &max[i][j]);
        }
    }
}

// Function to calculate need matrix
void calculateNeed() {
    for (int i = 0; i < PROCESSES; ++i) {
        for (int j = 0; j < RESOURCES; ++j) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

// Function to display matrices
void displayMatrices() {
    printf("Allocation Matrix:\n");
    for (int i = 0; i < PROCESSES; ++i) {
        for (int j = 0; j < RESOURCES; ++j) {
            printf("%d ", allocation[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    printf("Maximum Matrix:\n");
    for (int i = 0; i < PROCESSES; ++i) {
        for (int j = 0; j < RESOURCES; ++j) {
            printf("%d ", max[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    printf("Need Matrix:\n");
    for (int i = 0; i < PROCESSES; ++i) {
        for (int j = 0; j < RESOURCES; ++j) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    printf("Available Resources:\n");
    for (int i = 0; i < RESOURCES; ++i) {
        printf("%d ", available[i]);
    }
    printf("\n");
}

int main() {
    int choice;
    while (1) {
        printf("\nBanker's Algorithm Menu:\n");
        printf("1. Accept Allocation\n");
        printf("2. Accept Maximum\n");
        printf("3. Calculate and Display Need\n");
        printf("4. Display Available Resources\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                acceptAllocation();
                break;
            case 2:
                acceptMax();
                break;
            case 3:
                calculateNeed();
                printf("\nNeed matrix calculated.\n");
                displayMatrices();
                break;
            case 4:
                printf("\nAvailable Resources:\n");
                for (int i = 0; i < RESOURCES; ++i) {
                    printf("%d ", available[i]);
                }
                printf("\n");
                break;
            case 5:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}


//2

#include <stdio.h>
#include <stdlib.h>

// Function to swap two integers
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to sort the disk request array
void sortRequests(int arr[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

// Function to perform SCAN algorithm
void scan(int requests[], int n, int start, int direction) {
    int totalHeadMovement = 0;

    if (direction == -1) {
        printf("Left\n");
        for (int i = start; i >= 0; --i) {
            printf("%d ", requests[i]);
            totalHeadMovement += abs(start - requests[i]);
            start = requests[i];
        }
        printf("0 ");
        totalHeadMovement += start;
        for (int i = start + 1; i < n; ++i) {
            printf("%d ", requests[i]);
            totalHeadMovement += abs(requests[i] - start);
            start = requests[i];
        }
    } else {
        printf("Right\n");
        for (int i = start; i < n; ++i) {
            printf("%d ", requests[i]);
            totalHeadMovement += abs(start - requests[i]);
            start = requests[i];
        }
        printf("%d ", n - 1);
        totalHeadMovement += (n - 1 - start);
        for (int i = start - 1; i >= 0; --i) {
            printf("%d ", requests[i]);
            totalHeadMovement += abs(requests[i] - start);
            start = requests[i];
        }
    }

    printf("\nTotal head movements: %d\n", totalHeadMovement);
}

int main() {
    int n, start;
    printf("Enter total number of disk blocks: ");
    scanf("%d", &n);

    int requests[n];
    printf("Enter the disk request string: ");
    for (int i = 0; i < n; ++i) {
        scanf("%d", &requests[i]);
    }

    printf("Enter starting head position: ");
    scanf("%d", &start);

    int direction;
    printf("Enter direction (1 for Right, -1 for Left): ");
    scanf("%d", &direction);

    // Sort the request array
    sortRequests(requests, n);

    printf("Order of serving disk requests:\n");
    scan(requests, n, start, direction);

    return 0;
}
