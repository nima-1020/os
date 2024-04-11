//1
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
//2
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
