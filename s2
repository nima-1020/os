//1
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_BLOCKS 100

// Node for representing a block in the disk
typedef struct Block {
    int blockNumber;
    struct Block *next;
} Block;

// Function prototypes
void initializeDisk(Block *disk[], int numBlocks);
void showBitVector(Block *disk[], int numBlocks);
void createNewFile(Block *disk[], int numBlocks);
void showDirectory(Block *disk[], int numBlocks);
void deallocate(Block *disk[], int numBlocks);

int main() {
    int numBlocks, choice;
    printf("Enter the number of blocks in the disk: ");
    scanf("%d", &numBlocks);

    Block *disk[MAX_BLOCKS];
    for (int i = 0; i < numBlocks; i++) {
        disk[i] = NULL; // Initialize all blocks as empty
    }

    initializeDisk(disk, numBlocks); // Randomly allocate some blocks as occupied

    while (1) {
        printf("\nMenu:\n");
        printf("1. Show Bit Vector\n");
        printf("2. Create New File\n");
        printf("3. Show Directory\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                showBitVector(disk, numBlocks);
                break;
            case 2:
                createNewFile(disk, numBlocks);
                break;
            case 3:
                showDirectory(disk, numBlocks);
                break;
            case 4:
                deallocate(disk, numBlocks);
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}

// Function to initialize the disk with random allocation of blocks
void initializeDisk(Block *disk[], int numBlocks) {
    srand(time(NULL));
    int numOccupiedBlocks = rand() % numBlocks; // Randomly choose number of occupied blocks

    for (int i = 0; i < numOccupiedBlocks; i++) {
        int blockNumber = rand() % numBlocks;
        if (disk[blockNumber] == NULL) {
            disk[blockNumber] = (Block *)malloc(sizeof(Block));
            disk[blockNumber]->blockNumber = blockNumber;
            disk[blockNumber]->next = NULL;
        }
    }
}

// Function to display the bit vector representing disk allocation status
void showBitVector(Block *disk[], int numBlocks) {
    printf("Bit Vector:\n");
    for (int i = 0; i < numBlocks; i++) {
        if (disk[i] != NULL) {
            printf("1 ");
        } else {
            printf("0 ");
        }
    }
    printf("\n");
}

// Function to create a new file and allocate blocks for it
void createNewFile(Block *disk[], int numBlocks) {
    int startBlock;
    printf("Enter the starting block number for the new file: ");
    scanf("%d", &startBlock);

    if (disk[startBlock] == NULL) {
        disk[startBlock] = (Block *)malloc(sizeof(Block));
        disk[startBlock]->blockNumber = startBlock;
        disk[startBlock]->next = NULL;
        printf("File created successfully.\n");
    } else {
        printf("Block is already allocated.\n");
    }
}

// Function to display the directory
void showDirectory(Block *disk[], int numBlocks) {
    printf("Directory:\n");
    for (int i = 0; i < numBlocks; i++) {
        if (disk[i] != NULL) {
            printf("Block %d: Allocated\n", i);
        } else {
            printf("Block %d: Free\n", i);
        }
    }
}

// Function to deallocate all allocated blocks
void deallocate(Block *disk[], int numBlocks) {
    for (int i = 0; i < numBlocks; i++) {
        if (disk[i] != NULL) {
            free(disk[i]);
            disk[i] = NULL;
        }
    }
    printf("Deallocated all blocks.\n");
}


//2
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define ARRAY_SIZE 1000

int main(int argc, char *argv[]) {
    int rank, size;
    int local_sum = 0, global_sum = 0;
    int array[ARRAY_SIZE];

    // Initialize MPI environment
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Generate random numbers
    srand(rank); // Seed based on rank to ensure different random numbers for each process
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = rand() % 1000; // Generate random numbers between 0 and 999
    }

    // Calculate local sum
    for (int i = 0; i < ARRAY_SIZE; i++) {
        local_sum += array[i];
    }

    // Sum all local sums to get global sum
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // Output result from root process
    if (rank == 0) {
        printf("Total sum: %d\n", global_sum);
    }

    // Finalize MPI environment
    MPI_Finalize();

    return 0;
}
