//1
//La


#include <stdio.h>
#include<stdlib.h>

int bv[50],p,a;
int st, len, k, c, j;
char  fnm[20],f[20];

void rec(int bv[],int,int);



int main() {

    FILE *fp;
    int sb,len;
    int t;
    int op=1;



    printf("\n Enter Total Block : ");
    scanf("%d",&t);

    bv[t];

    for(int i=0; i<t; i++)
        bv[i]=1;

    printf("\n Bit Vector Before Allocation \n ");
    for(int i=0; i<t; i++)
        printf("%d",bv[i]);

    printf("\n");

    printf("\nEnter the number of blocks already allocated: ");
    scanf("%d", &p);
    printf("\nEnter the blocks already allocated: ");
    for (int i = 0; i < p; i++) {
        scanf("%d", &a);
        bv[a] = 0;
    }


    printf("\n ");
    while(op>=1 && op<=5)
    {


        printf("\n 1.Create File");
        printf("\n 2.Show bit Vector ");
        printf("\n 3.Delete File  ");
        printf("\n 4.Display  ");
        printf("\n 5.Exit");


        printf("\n Enter option :  ");
        scanf("%d",&op);

        switch(op)
        {
        case 1:
            printf("\nEnter File name : ");
            scanf("%s",fnm);

            fp = fopen(fnm, "w");

            if (fp == NULL) {
                printf("\nError opening the file.\n");
                return 1;
            }
            else
                printf("\n *** File is created *** \n ");


            printf("Enter the index of the starting block and its length: ");
            scanf("%d%d", &st, &len);
            rec(bv,st,len);
            //fclose(fp);
            break;

        case 2 :
            printf("\n Bit Vector After  Allocation \n ");
            for(int i=0; i<t; i++)
                printf("%d",bv[i]);

            printf("\n");
            break;

        case 3:
            printf("\nEnter File name to delete : ");
            scanf("%s",&f);
            if (remove(f) == 0)
                printf("\nDeleted successfully\n");

            else
                printf("\nUnable to delete the file\n");
            break;

        case 4 :
            printf("\n File Details Are : \n ");
            printf("\nF_NM\tIB\tLen\n");
            printf("%s\t%d\t%d",fnm,st,len);
            printf("\n");
            break;

        case 5 :
            exit(0);


        }
        if(op!=4 )
        {
            printf("\n File Details Are : \n ");
            printf("\nF_NM\tIB\tLen\n");
            printf("%s\t%d\t%d",fnm,st,len);
            printf("\n");

        }


    }



    fclose(fp);
    return 0;
}

void rec(int bv[],int st,int len) {


    k = len;
    printf("\nFNm\tIndesx\tAllocated\n\n");
    if (bv[st] == 1) {
        for (j = st; j < (st + k); j++) {
            if (bv[j] == 1) {
                bv[j] = 0;
                printf("%s\t%d------->%d\n", fnm,j, bv[j]);
            }
            else {
                printf("\nThe block %d is already allocated \n\n", j);
                k++;
            }
        }
    }
    else
        printf("\nThe block %d is already allocated \n\n", st);

}

//2
#include <stdio.h>
#include <stdlib.h>

#define MAX_REQUESTS 100

// Function to swap two integers
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to perform bubble sort
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n-1; ++i) {
        for (int j = 0; j < n-i-1; ++j) {
            if (arr[j] > arr[j+1]) {
                swap(&arr[j], &arr[j+1]);
            }
        }
    }
}

// Function to find the index of the element greater than or equal to head
int findNextIndex(int requests[], int n, int head) {
    int next_index = 0;
    for (int i = 0; i < n; ++i) {
        if (requests[i] >= head) {
            next_index = i;
            break;
        }
    }
    return next_index;
}

// Function to calculate total head movements using C-SCAN
int calculateHeadMovements(int requests[], int n, int head, int direction) {
    bubbleSort(requests, n);
    int total_head_movements = 0;
    int start_index = findNextIndex(requests, n, head);

    if (direction == 1) { // Right direction
        // Head moves from start to end
        for (int i = start_index; i < n; ++i) {
            total_head_movements += abs(requests[i] - head);
            head = requests[i];
        }
        // Head moves from end to start
        total_head_movements += abs(head - 199);
        head = 0;
        for (int i = 0; i < start_index; ++i) {
            total_head_movements += abs(requests[i] - head);
            head = requests[i];
        }
    } else { // Left direction
        // Head moves from start to end
        for (int i = start_index - 1; i >= 0; --i) {
            total_head_movements += abs(requests[i] - head);
            head = requests[i];
        }
        // Head moves from end to start
        total_head_movements += abs(head - 0);
        head = 199;
        for (int i = n - 1; i >= start_index; --i) {
            total_head_movements += abs(requests[i] - head);
            head = requests[i];
        }
    }

    return total_head_movements;
}

int main() {
    int num_blocks, head_position, direction;
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

    printf("Enter the direction (1 for Right, 0 for Left): ");
    scanf("%d", &direction);

    // Calculate total head movements
    int total_head_movements = calculateHeadMovements(requests, num_blocks, head_position, direction);

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
