//1
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
