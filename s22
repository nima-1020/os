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

// sequential allocation 
#include <stdio.h>
#include<stdlib.h>
#include <dirent.h>

int main() {

    FILE *fp;
    char  fnm[50], f[50];;
    static  int sb,len;
    int t;
    int flag;
    int op=1;

    DIR *dp;
    struct dirent *entry;

    printf("\n Enter Total Block : ");
    scanf("%d",&t);
    int tb[t];

    for(int i=0; i<t; i++)
        tb[i]=1;

    printf("\n Bit Vector Before Allocation \n ");
    for(int i=0; i<t; i++)
        printf("%d",tb[i]);

    printf("\n ");
    while(op>=1 && op<=6)
    {


        printf("\n 1.Creat File ");
        printf("\n 2.Show bit Vector ");
        printf("\n 3.Delete File  ");
        printf("\n 4.Display  ");
        printf("\n 5.Show Directory : ");
        printf("\n 6.Exit");


        printf("\nEnter option :  ");
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
            {
     
                printf("\n **** File is Created *** \n ");

                printf("\nEnter Start block : ");
                scanf("%d",&sb);

                printf("\nEnter length  : ");
                scanf("%d",&len);
                int k=len;
                
                if(sb>t || len>t)
                {
                   printf("\n*WARNING*** Start block and length must be less than number if blocks on disk\n ");
                   break;
                }
               else if(sb<=t && len<=t)
               {
                int cnt=0;
 
                for(int i=sb; i<(sb+len); i++)
                {

                    if(tb[i]==1)
                    {
                        flag=0;
                        // len--;
                        cnt++;
                        // flag=1;
                        tb[i]=0;
                        if(cnt==len)
                        {

                            printf("\nAllocation is Successfully Done\n ");
                            break;

                        }
                  
                    }
                    else if(tb[i] == 0 )
                    {
                        printf("\nAllocation is not done (Already another file is at given start block : %d ) \n",sb);
                        printf("\n Blocks which are alredy occupied \n");
                        for(int i=sb;i<t;i++)
                        {
                            if(tb[i]==0)
                               printf("block : %d : allocated \n",i);
                            
                               
                    
                        }
                         printf("\n ----Please choose another start block---- \n");   
                        // flag=1;
                        break;
                    }


                }

            }
          }
            break;
        case 2 :
            printf("\n Bit Vector After  Allocation \n ");
            for(int i=0; i<t; i++)
                printf("%d",tb[i]);

            printf("\n");
            break;

        case 3:
            
            printf("\nEnter File name : ");
            scanf("%s",&f);
            if (remove(f) == 0) {
                printf("\nThe file is deleted successfully.\n");
            } else {
                printf("\nThe file is not deleted.\n");
            }
            break;

        case 4 :
             printf("\n File Details Are : \n ");
            printf("\nF_NM\tSB\tLen\n");
            printf("%s\t%d\t%d",fnm,sb,len);
            printf("\n");
            break;

        case 5 :
              dp = opendir(".");
              if(dp==NULL)
             {
                printf("Dir is not found.\n");
                
             }
             else
             {
                while(entry=readdir(dp))
               {
                     if(entry->d_type==DT_REG)
                     printf("%s\n",entry->d_name);
              }
                    
             }
             break;
        case 6:
             exit(0);


        }
        if(op!=4 )
        {
            printf("\n File Details Are : \n ");
            printf("\nF_NM\tSB\tLen\n");
            printf("%s\t%d\t%d",fnm,sb,len);
            printf("\n");

        }


    }

    fclose(fp); // Close the file
    return 0;
}
