//1

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_BLOCKS 100

// Structure to represent a block
typedef struct Block {
    int index;
    struct Block *next;
} Block;

int n; // Total number of blocks on the disk
Block *freeBlocks = NULL; // List of free blocks

// Function to initialize the list of free blocks
void initializeFreeBlocks() {
    for (int i = n - 1; i >= 0; --i) {
        Block *newBlock = (Block *)malloc(sizeof(Block));
        if (!newBlock) {
            printf("Memory allocation failed.\n");
            exit(EXIT_FAILURE);
        }
        newBlock->index = i;
        newBlock->next = freeBlocks;
        freeBlocks = newBlock;
    }
}

// Function to randomly mark some blocks as allocated
void allocateRandomBlocks() {
    srand(time(NULL));
    int numAllocated = rand() % (n / 2); // Randomly allocate up to half of the blocks
    for (int i = 0; i < numAllocated; ++i) {
        int index = rand() % n;
        Block *prev = NULL;
        Block *curr = freeBlocks;
        while (curr && curr->index != index) {
            prev = curr;
            curr = curr->next;
        }
        if (curr) {
            if (prev)
                prev->next = curr->next;
            else
                freeBlocks = curr->next;
            free(curr);
        }
    }
}

// Function to display the bit vector
void showBitVector() {
    printf("Bit Vector (1 indicates allocated, 0 indicates free):\n");
    for (int i = 0; i < n; ++i) {
        if (freeBlocks && freeBlocks->index == i) {
            printf("0 ");
            freeBlocks = freeBlocks->next;
        } else {
            printf("1 ");
        }
    }
    printf("\n");
}

// Function to create a new file
void createNewFile() {
    if (!freeBlocks) {
        printf("Disk is full. Cannot create a new file.\n");
        return;
    }
    Block *newBlock = freeBlocks;
    freeBlocks = freeBlocks->next;
    printf("New file created at block %d.\n", newBlock->index);
    free(newBlock);
}

// Function to show directory (list of free blocks)
void showDirectory() {
    printf("Directory (List of free blocks):\n");
    Block *curr = freeBlocks;
    while (curr) {
        printf("%d ", curr->index);
        curr = curr->next;
    }
    printf("\n");
}

int main() {
    printf("Enter the total number of blocks on the disk: ");
    scanf("%d", &n);

    // Initialize the list of free blocks
    initializeFreeBlocks();

    // Randomly mark some blocks as allocated
    allocateRandomBlocks();

    int choice;
    do {
        printf("\nLinked File Allocation Menu:\n");
        printf("1. Show Bit Vector\n");
        printf("2. Create New File\n");
        printf("3. Show Directory\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                showBitVector();
                break;
            case 2:
                createNewFile();
                break;
            case 3:
                showDirectory();
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 4);

    return 0;
}


//2
#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 100

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

// Function to find the index of the first request greater than the current head position
int findFirstRequestGreaterThanHead(int requests[], int n, int head) {
    for (int i = 0; i < n; ++i) {
        if (requests[i] >= head) {
            return i;
        }
    }
    return -1;
}

// Function to perform C-SCAN algorithm
void cscan(int requests[], int n, int start, int direction) {
    int totalHeadMovement = 0;

    // Sort the request array
    sortRequests(requests, n);

    // Find the index of the first request greater than the current head position
    int firstRequestIndex = findFirstRequestGreaterThanHead(requests, n, start);
    if (firstRequestIndex == -1) {
        firstRequestIndex = 0;
    }

    if (direction == -1) {
        printf("Left\n");
        // Traverse from the start position to the end
        for (int i = firstRequestIndex; i < n; ++i) {
            printf("%d ", requests[i]);
            totalHeadMovement += abs(start - requests[i]);
            start = requests[i];
        }
        // Go to the beginning of the disk and continue to the start position
        printf("0 ");
        totalHeadMovement += start;
        for (int i = 0; i < firstRequestIndex; ++i) {
            printf("%d ", requests[i]);
            totalHeadMovement += abs(requests[i] - start);
            start = requests[i];
        }
    } else {
        printf("Right\n");
        // Traverse from the start position to the end
        for (int i = firstRequestIndex; i < n; ++i) {
            printf("%d ", requests[i]);
            totalHeadMovement += abs(start - requests[i]);
            start = requests[i];
        }
        // Go to the end of the disk and continue to the start position
        printf("%d ", MAX_BLOCKS - 1);
        totalHeadMovement += (MAX_BLOCKS - 1 - start);
        for (int i = 0; i < firstRequestIndex; ++i) {
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

    int requests[MAX_BLOCKS];
    printf("Enter the disk request string (terminate input with -1):\n");
    int numRequests = 0;
    int request;
    while (1) {
        scanf("%d", &request);
        if (request == -1 || numRequests >= MAX_BLOCKS) {
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

    // Simulate C-SCAN algorithm
    cscan(requests, numRequests, start, direction);

    return 0;
}
