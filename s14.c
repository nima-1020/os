//1

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


//2
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

// Function to perform bubble sort based on absolute difference
void sort(int arr[], int n, int head) {
    for (int i = 0; i < n-1; ++i) {
        for (int j = 0; j < n-i-1; ++j) {
            if (abs(arr[j] - head) > abs(arr[j+1] - head)) {
                swap(&arr[j], &arr[j+1]);
            }
        }
    }
}

// Function to calculate total head movements
int calculateHeadMovements(int requests[], int n, int head) {
    int total_head_movements = 0;
    for (int i = 0; i < n; ++i) {
        total_head_movements += abs(requests[i] - head);
        head = requests[i];
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

    // Sort the requests based on the shortest seek time
    sort(requests, num_blocks, head_position);

    // Display the ordered list of requests
    printf("Ordered list of requests: ");
    for (int i = 0; i < num_blocks; ++i) {
        printf("%d ", requests[i]);
    }
    printf("\n");

    // Calculate total head movements
    int total_head_movements = calculateHeadMovements(requests, num_blocks, head_position);
    printf("Total number of head movements: %d\n", total_head_movements);

    return 0;
}

