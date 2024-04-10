//1

#include <stdio.h>

#define PROCESSES 5
#define RESOURCES 4

int available[RESOURCES] = {2, 3, 0, 2};
int allocation[PROCESSES][RESOURCES] = {
    {2, 0, 0, 1},
    {3, 1, 2, 1},
    {2, 1, 0, 3},
    {1, 3, 1, 2},
    {1, 4, 3, 2}
};
int max[PROCESSES][RESOURCES] = {
    {4, 2, 1, 2},
    {5, 2, 5, 2},
    {2, 3, 1, 6},
    {1, 4, 2, 4},
    {3, 6, 6, 5}
};
int need[PROCESSES][RESOURCES];

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
    int finish[PROCESSES] = {0};

    // Initialize work to available
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
                    // Process can complete, add its resources to work
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
        printf("P%d ", safeSeq[i]);
    }
    printf("\n");
    return 1;
}

int main() {
    // Calculate the need matrix
    calculateNeed();

    // Check if the system is in a safe state
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

// Function to find the index of the first request greater than or equal to the current head position
int findFirstRequestGreaterThanOrEqual(int requests[], int n, int head) {
    for (int i = 0; i < n; ++i) {
        if (requests[i] >= head) {
            return i;
        }
    }
    return -1;
}

// Function to perform SCAN algorithm
void scan(int requests[], int n, int start, int direction) {
    int totalHeadMovement = 0;

    // Sort the request array
    sortRequests(requests, n);

    // Find the index of the first request greater than or equal to the current head position
    int firstRequestIndex = findFirstRequestGreaterThanOrEqual(requests, n, start);
    if (firstRequestIndex == -1) {
        firstRequestIndex = 0;
    }

    if (direction == -1) {
        printf("Left\n");
        // Traverse from the start position to the beginning of the disk
        for (int i = firstRequestIndex; i >= 0; --i) {
            printf("%d ", requests[i]);
            totalHeadMovement += abs(start - requests[i]);
            start = requests[i];
        }
        // Traverse from the beginning of the disk to the end
        printf("0 ");
        totalHeadMovement += start;
        for (int i = firstRequestIndex + 1; i < n; ++i) {
            printf("%d ", requests[i]);
            totalHeadMovement += abs(requests[i] - start);
            start = requests[i];
        }
    } else {
        printf("Right\n");
        // Traverse from the start position to the end of the disk
        for (int i = firstRequestIndex; i < n; ++i) {
            printf("%d ", requests[i]);
            totalHeadMovement += abs(start - requests[i]);
            start = requests[i];
        }
        // Traverse from the end of the disk to the beginning
        printf("%d ", 199); // Assuming total disk blocks are 200
        totalHeadMovement += (199 - start);
        for (int i = firstRequestIndex - 1; i >= 0; --i) {
            printf("%d ", requests[i]);
            totalHeadMovement += abs(requests[i] - start);
            start = requests[i];
        }
    }

    printf("\nTotal head movements: %d\n", totalHeadMovement);
}

int main() {
    int n;
    printf("Enter total number of disk blocks: ");
    scanf("%d", &n);

    int requests[n];
    printf("Enter the disk request string (terminate input with -1):\n");
    int numRequests = 0;
    int request;
    while (1) {
        scanf("%d", &request);
        if (request == -1 || numRequests >= n) {
            break;
        }
        requests[numRequests++] = request;
    }

    int start;
    printf("Enter starting head position: ");
    scanf("%d", &start);

    int direction;
    printf("Enter direction (1 for Right, -1 for Left): ");
    scanf("%d", &direction);

    // Simulate SCAN algorithm
    scan(requests, numRequests, start, direction);

    return 0;
}
