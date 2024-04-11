//1
#include <stdio.h>
#include <stdbool.h>

#define MAX_RESOURCES 10
#define MAX_PROCESSES 10

// Function to calculate the need matrix
void calculateNeedMatrix(int need[MAX_PROCESSES][MAX_RESOURCES], int max[MAX_PROCESSES][MAX_RESOURCES], int allocation[MAX_PROCESSES][MAX_RESOURCES], int m, int n) {
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

// Function to check if the request can be granted immediately
bool isSafeState(int need[MAX_PROCESSES][MAX_RESOURCES], int available[MAX_RESOURCES], int allocation[MAX_PROCESSES][MAX_RESOURCES], int m, int n, int process, int request[MAX_RESOURCES]) {
    // Check if the request is less than or equal to need
    for (int i = 0; i < n; ++i) {
        if (request[i] > need[process][i]) {
            return false;
        }
    }

    // Check if the request is less than or equal to available
    for (int i = 0; i < n; ++i) {
        if (request[i] > available[i]) {
            return false;
        }
    }

    // Try to allocate the resources temporarily
    for (int i = 0; i < n; ++i) {
        available[i] -= request[i];
        allocation[process][i] += request[i];
        need[process][i] -= request[i];
    }

    // Check if the system is still in a safe state after the allocation
    bool finish[MAX_PROCESSES] = {false};
    int work[MAX_RESOURCES];
    for (int i = 0; i < n; ++i) {
        work[i] = available[i];
    }

    int count = 0;
    while (count < m) {
        bool found = false;
        for (int i = 0; i < m; ++i) {
            if (!finish[i]) {
                int j;
                for (j = 0; j < n; ++j) {
                    if (need[i][j] > work[j]) {
                        break;
                    }
                }
                if (j == n) {
                    for (int k = 0; k < n; ++k) {
                        work[k] += allocation[i][k];
                    }
                    finish[i] = true;
                    found = true;
                    count++;
                }
            }
        }
        if (!found) {
            break;
        }
    }

    // Restore the previous state
    for (int i = 0; i < n; ++i) {
        available[i] += request[i];
        allocation[process][i] -= request[i];
        need[process][i] += request[i];
    }

    return count == m;
}

int main() {
    int m, n;
    int available[MAX_RESOURCES];
    int allocation[MAX_PROCESSES][MAX_RESOURCES];
    int max[MAX_PROCESSES][MAX_RESOURCES];
    int need[MAX_PROCESSES][MAX_RESOURCES];
    int request[MAX_RESOURCES];

    // Accept input from the user
    printf("Enter the number of processes: ");
    scanf("%d", &m);
    printf("Enter the number of resource types: ");
    scanf("%d", &n);

    printf("Enter the number of instances for each resource type:\n");
    for (int i = 0; i < n; ++i) {
        scanf("%d", &available[i]);
    }

    printf("Enter the allocation matrix:\n");
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("Enter the maximum requirement matrix:\n");
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter the process number for which you want to request resources: ");
    int process;
    scanf("%d", &process);
    printf("Enter the resource request vector for process %d:\n", process);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &request[i]);
    }

    // Calculate the need matrix
    calculateNeedMatrix(need, max, allocation, m, n);

    // Display the contents of the need matrix
    printf("Need matrix:\n");
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    // Check if the request can be granted immediately
    if (isSafeState(need, available, allocation, m, n, process, request)) {
        printf("Request can be granted immediately.\n");
    } else {
        printf("Request cannot be granted immediately.\n");
    }

    return 0;
}
//2
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_REQUESTS 100

// Function to find the absolute difference between two numbers
int absDiff(int a, int b) {
    return abs(a - b);
}

// Function to find the index of the nearest request
int findNearestIndex(int requests[], int n, int head) {
    int minDiff = INT_MAX;
    int nearestIndex = -1;

    for (int i = 0; i < n; ++i) {
        int diff = absDiff(requests[i], head);
        if (diff < minDiff) {
            minDiff = diff;
            nearestIndex = i;
        }
    }

    return nearestIndex;
}

// Function to calculate total head movements using SSTF
int calculateHeadMovements(int requests[], int n, int head_position) {
    int total_head_movements = 0;

    // Copy the request array to avoid modifying the original array
    int sorted_requests[MAX_REQUESTS];
    for (int i = 0; i < n; ++i) {
        sorted_requests[i] = requests[i];
    }

    // Serve requests in SSTF order
    for (int i = 0; i < n; ++i) {
        int nearestIndex = findNearestIndex(sorted_requests, n - i, head_position);
        total_head_movements += absDiff(sorted_requests[nearestIndex], head_position);
        head_position = sorted_requests[nearestIndex];
        // Remove the served request from the list
        sorted_requests[nearestIndex] = sorted_requests[n - i - 1];
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
