//1

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


//2
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Function to swap two integers
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to calculate absolute difference
int absDiff(int a, int b) {
    return abs(a - b);
}

// Function to sort the disk request array based on distance from the head
void sortRequests(int requests[], int n, int head) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (absDiff(requests[j], head) > absDiff(requests[j + 1], head)) {
                swap(&requests[j], &requests[j + 1]);
            }
        }
    }
}

// Function to perform SSTF algorithm
void sstf(int requests[], int n, int start) {
    int totalHeadMovement = 0;
    int head = start;

    printf("SSTF Order:\n");

    // Process requests one by one
    for (int i = 0; i < n; ++i) {
        printf("%d ", requests[i]);
        totalHeadMovement += absDiff(head, requests[i]);
        head = requests[i];
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

    // Simulate SSTF algorithm
    sstf(requests, numRequests, start);

    return 0;
}

