//1

// scan

#include<stdio.h>
#include<stdlib.h>


void main()
{
    int i,j,k,n,head,move,tm=0,size;

    printf("\n Enter the no of requests : ");
    scanf("%d",&n);

    int rq[n];
    printf("\n Enter the requests : ");
    for (i=0;i<n;i++)
        scanf("%d",&rq[i]);

    printf("\n Enter the initial head position : ");
    scanf("%d",&head);

    printf("\n Enter the size of the disk : ");
    scanf("%d",&size);

    printf("\n Enter the move (0)left /(1) Right :  ");
    scanf("%d",&move);

    //sort the requests firstly
    for (i=0;i<n;i++)
        for (j=0;j<n-i-1;j++)
           if (rq[j]>rq[j+1])
           {
              int temp=rq[j];
              rq[j]=rq[j+1];
              rq[j+1]=temp;
           }

    // the sorted requests are 
    printf("\n The sorted requests are : ");
    for (i=0;i<n;i++)
        printf(" %d ",rq[i]);       


    // find the index position
    int index;

    for (i=0;i<n;i++)
    {
        if (rq[i] > head)
        {
            index=i;
            break;
        }
    }

    printf(" \n Index   :%d",index);

    if (move==1) // move towards a greater value...
    {
        printf("\n The requests are serviced : ");
        for (i=index;i<n;i++)
        {
            printf(" %d->",rq[i]);
            tm=tm+abs(head-rq[i]);
            head=rq[i];
            //  printf("\n %d \n",tm);
        }

        printf(" %d-> ",size-1);
        tm=tm+abs(size-1-head);
        // printf("\n %d \n",tm);
        head=size-1;



        for (i=index-1;i>=0;i--)
        {
            printf(" %d->",rq[i]);
            tm=tm+abs(head-rq[i]);
            head=rq[i];
            // printf("\n %d \n",tm);

        }

    }
    else    // if the move is towards the smaller value 1stly
    {
         printf("\n The requests are serviced : ");

         for (i=index-1;i>=0;i--)
        {
            printf(" %d->",rq[i]);
            tm=tm+abs(head-rq[i]);
            head=rq[i];
            // printf("\n %d \n",tm);

        }


        printf(" %d-> ",0);
        tm=tm+abs(0-1-head);
        // printf("\n %d \n",tm);
        head=0;


       
        for (i=index;i<n;i++)
        {
            printf(" %d->",rq[i]);
            tm=tm+abs(head-rq[i]);
            head=rq[i];
             printf("\n %d \n",tm);
        }

    }

    printf("\n Total head movements :  %d",tm);




}
//2
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define ARRAY_SIZE 1000

int main(int argc, char *argv[]) {
    int rank, size;
    int numbers[ARRAY_SIZE];
    int local_min, global_min;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Seed random number generator with rank-specific seed
    srand(rank);

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

    // Reduce local minimums to find global minimum
    MPI_Reduce(&local_min, &global_min, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Global minimum number: %d\n", global_min);
    }

    MPI_Finalize();
    return 0;
}
