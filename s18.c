//1

// index file



#include <stdio.h>
#include<stdlib.h>
#include <dirent.h>

int files[10], indexBlock[50], indBlock, n,cnt=0,t;
char  fnm[20],f[20];

int recurse2 ();

int recurse1() {
    printf("Enter the index block: ");
    scanf("%d", &indBlock);
    if(indBlock >=t )
    {
       printf("\n*WARNING*** Index block must be less than number if blocks on disk\n ");
        
    }
    if (files[indBlock] != 0) {
        files[indBlock]=0;
        printf("\nEnter the number of blocks  needed for the index %d on the disk: ", indBlock);
        scanf("%d", &n);
    }
    else if(files[indBlock] == 0){
    
         printf("\n Blocks which are alredy occupied \n");
          for(int i=indBlock;i<t;i++)
         {
                if(files[i]==0)
                     printf("block : %d : allocated \n",i);
         }
       printf("\n ----Please choose another Index block---- \n");  
       // printf("%d is already allocated\n", indBlock);
       recurse1();
    }
    else
        return 1;
    recurse2();
}

int recurse2() {
    int ch;
    int flag = 0;
    cnt=0;
    //int cnt=0;
    printf("\nEnter block occupied by given %s File : \n ",fnm);
    for (int i=0; i<n; i++) {
        scanf("%d", &indexBlock[i]);
        cnt++;
        if (files[indexBlock[i]] == 1)
            flag++;
    }
    if (flag == n) {
        for (int j=0; j<n; j++) {
            files[indexBlock[j]] = 0;
        }
        printf("\n**Allocated*\n");
        printf("\nFNm\tIB\tIndex\tAlloctated\n");
        for (int k=0; k<n; k++) {
            printf("%s\t%d ----> %d\t%d\n", fnm,indBlock, indexBlock[k], files[indexBlock[k]]);

        }
        /*printf("\n Bit Vector \n");
        for (int k=0; k<10; k++)
             printf("%d",files[k]);*/
    }
    else {
        printf("\nblock in the index is already allocated\n");
        printf("Enter another block\n");
        recurse2();
    }

}



int main() {

    FILE *fp;
    static  int sb,len;

    int op=1;

    

    printf("\n Enter Total Block : ");
    scanf("%d",&t);

    files[t];

    for(int i=0; i<10; i++)
        files[i]=1;
   
    DIR *dp;
    struct dirent *entry;


    printf("\n Bit Vector Before Allocation \n ");
    for(int i=0; i<t; i++)
        printf("%d",files[i]);

    printf("\n ");
    while(op>=1 && op<=6)
    {


        printf("\n 1.Create File");
        printf("\n 2.Show bit Vector ");
        printf("\n 3.Delete File  ");
        printf("\n 4.Display  ");
        printf("\n 5.Show Directory : ");
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
                
           recurse1();

            //fclose(fp);
            break;

        case 2 :
            printf("\n Bit Vector After  Allocation \n ");
            for(int i=0; i<t; i++)
                printf("%d",files[i]);

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
            printf("%s\t%d\t%d",fnm,indBlock,cnt);
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
            printf("\nF_NM\tIB\tLen\n");
            printf("%s\t%d\t%d",fnm,indBlock,cnt);
            printf("\n");

        }


    }



    fclose(fp);
    return 0;
}

//2
