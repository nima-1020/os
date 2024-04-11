//1
#include <stdio.h>
#include <stdlib.h>

int max[10][10];
int alloc[10][10];
int need[10][10];
int avail[10];
int n,r;
int sq[10];
int work[10];

014
void input()
{
     int i,j;
     printf("\n Enter number of processes :");
     scanf("%d",&n);
     printf("\n Enter number of recources :");
     scanf("%d",&r);
     printf("\n Enter Max Req :\n");
     for (i=0;i<n;i++)
        for (j=0;j<r;j++)
             scanf("%d",&max[i][j]);
     printf("\n Enter Allocations :\n");
     for (i=0;i<n;i++)
        for (j=0;j<r;j++)
             scanf("%d",&alloc[i][j]);
     printf("\n Enter Avialable recources :\n");
     for (j=0;j<r;j++)
     {
          printf("\nFor R[%d] : ",j +1);
         
          scanf("%d",&avail[j]);
     }
     printf("\n");
     
}

void display()
{
     int i,j;
     printf("\npro\tAlloc\tMAx\tNeed :\n");
     for (i=0;i<n;i++)
     {
         printf("\np[%d]\t",i);
         for (j=0;j<r;j++)
             printf("%d ",alloc[i][j]);
         printf("\t");
         for (j=0;j<r;j++)
             printf("%d ",max[i][j]);
         printf("\t");
         for (j=0;j<r;j++)
         {
             need[i][j]=max[i][j]-alloc[i][j];
             printf("%d ",need[i][j]);
         }
         printf("\t");
     }
     printf("\n");
}


void safety()
{
     int i,j;
     int finish[10];
     //copy avail Rec into work 
     for (i=0;i<r;i++)
     {
         work[i]=avail[i];
          //printf("%d\n",work[i]);
    }
     //initialise finish array to zero 
     for (j=0;j<n;j++)
     {
          finish[j]=0;
           // printf("%d\n",finish[i]);
        }
     int proc=1;
     int k=0;
     while (proc) 
     {
           proc=0;
           for (i=0;i<n;i++)
           {
               int flag=1;
               if (finish[i]==0)
               {
                   for (j=0;j<r;j++)
                   {
                       if(need[i][j]<=work[j])
                       {
                          continue;
                       }
                       else
                       {
                           flag=0;
                           
                           break;
                           
                       }
                   }
                   if(flag==0)
                   {
                      continue;
                   }
                  for (j=0;j<r;j++)
                      work[j]=work[j]+alloc[i][j];
                  finish[i]=1;
                  sq[k++]=i;
                  proc=1;
               }
           }
     }
     for (i=0;i<n && finish[i]==1;i++)
     {
         continue;
     }
     if(i==n)
     {
        printf("\n**** System is in Safe Seq **** :\n");
        printf("\n**** Safe Seq is **** :\n");
        for (i=0;i<n;i++)
            printf("p-->%d",sq[i]);
        printf("\n");
        printf("\n**** Total Rec  **** :\n");
        for (j=0;j<r;j++)
        {
            printf("\nFor R[%d] : ",j+1);
            printf("%d\n",work[j]);
        }
     }
     else
     {
         printf("\n**** System is in UnSafe Seq **** :\n");
         printf("\n**** Deadlock **** :\n");
     }   
     
}

void req()
{
     int pid ,j,rq[10],c;
     printf("\n**** Recourse Req Algo **** :\n");
     printf("\n Do yiu want to make an Additional Req press Y/N Y=1 and N=0 :\n");
     scanf("%d",&c);
     if(c==1)
     {
         printf("\n Enter processe num :");
         scanf("%d",&pid);
         printf("\n Enter  pro Req :\n");
         for (j=0;j<r;j++)
        {
          printf("\nFor R[%d] : ",j +1);
         
          scanf("%d",&rq[j]);
        }
        printf("\n");
        
        printf("\n**** New Updated Alloc and Need Mat is  **** :\n");
        for (j=0;j<r;j++)
        {
            if(rq[j]<=need[pid][j] && rq[j]<=avail[j])
            {
               avail[j]-=rq[j];
               alloc[pid][j]+=rq[j];
               need[pid][j]-=rq[j];
            }
            else
            {
                printf("\n**** Errorr **** :\n");
                exit(0); 
            }
        }
        display();
        safety();
        
         
     }
     else
         exit(0);
     
}


void main()
{
     input();
     display();
     safety();
     req();
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
