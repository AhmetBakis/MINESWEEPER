#include <stdio.h>
#include <stdlib.h>
#include <time.h>
# define SIZE 10
void rastgele(int **p,int *total)
{
    srand(time(0));
    for(int i=0;i<SIZE;i++)
    {
        for(int j=0;j<SIZE;j++)
        {
            int g;
            g=rand()%10;
            if(g)
            {
                p[i][j]=0;
            }
            else
            {
                p[i][j]=-1;
                (*total)++;
            }
        }
    }
}
void sayilar(int **p)
{
    for(int i=0;i<SIZE;i++)
    {
        for(int j=0;j<SIZE;j++)
        {

           if(p[i][j]==-1);
           else
            {
                int bs=0;
                for(int n=-1;n<2;n++)
                {
                    for(int m=-1;m<2;m++)
                    {
                        if(i+n>=0&&i+n<SIZE&&j+m>=0&&j+m<SIZE&&p[i+n][j+m]==-1)
                        {
                            bs++;
                        }
                    }
                }
                p[i][j]=bs;
            }
        }
    }
}
void acici(int **p,int sa,int su,double *A,int *id,int *t)
{
    if(sa>=0&&sa<SIZE&&su>=0&&su<SIZE)
        {
        int key=1;
        unsigned long y;
        y=(unsigned long)&p[sa][su];
        if(p[sa][su]==-1)
        {
            printf("YOU DETONATED A MINE\n");
                printf("       ");
                for(int i=0;i<SIZE;i++)
                {
                    printf("%3d",i+1);
                }
                printf("\n");
                printf("       ");
                 for(int i=0;i<SIZE;i++)
                {
                    printf("___");
                }
                printf("\n");
                for(int i=0;i<SIZE;i++)
                {
                    printf("%3d   |",i+1);
                    for(int j=0;j<SIZE;j++)
                    {
                        if(p[i][j]==-1)
                        {
                            if("i==sa&&j==su")
                                {
                                   printf("  B");
                                }
                            else
                            //   printf("  #");
                                    printf("  B");
                        }
                        else
                          //  printf("  #");
                            printf("%3d",p[i][j]);
                    }
                    printf("\n");
                }
            exit(1);
        }
        for(int i=0;i<(*id)+1;i++)
        {
            if(A[i]==y)
            {
                key=0;
                break;
            }
        }
        if(key!=0)
        {
            A[*id]=(double)y;
            (*id)++;
            (*t)++;
            for(int i=-1;i<2;i++)
            {
                for(int j=-1;j<2;j++)
                {
                    if(p[sa][su]==0)
                    {
                        if(sa+i>=0&&sa+i<SIZE&&su+j>=0&&su+j<SIZE)
                        {
                            acici(p,sa+i,su+j,A,id,t);
                        }
                    }
                    else
                    {
                        if(sa+i>=0&&sa+i<SIZE&&su+j>=0&&su+j<SIZE&&p[sa+i][su+j]==0)
                        {
                           acici(p,sa+i,su+j,A,id,t);
                        }
                    }
                }
            }
        }
    }
return;
}
void yazdir(int **p,double *A,double *B,int total)
{
    int kontrol=0;

    printf("       ");
    for(int i=0;i<SIZE;i++)
    {
        printf("%3d",i+1);
    }
    printf("\n");
    printf("        ");
     for(int i=0;i<SIZE;i++)
    {
        printf("___");
    }
    printf("\n");
    for(int i=0;i<SIZE;i++)
    {
        printf("%3d   |",i+1);
        for(int j=0;j<SIZE;j++)
        {
            int b=0;
            int key=1;
                while(A[b])
            {
                if((unsigned long)A[b]==(unsigned long)&p[i][j])
                {
                    key=0;
                    printf("%3d",p[i][j]);
                    break;
                }
                b++;
            }
             b=0;
             if(key)
                {
                while(B[b])
            {
                if((unsigned long)B[b]==(unsigned long)&p[i][j])
                {
                    key=0;
                    printf("  F");
                    kontrol++;
                    break;
                }
                b++;
            }
             }
            if(key){
                 printf("  #");
                 kontrol++;
                // printf("%3d",p[i][j]);
            }
        }
        printf("\n");
    }
    if(kontrol==total)
    {
        printf("------------------YOU HAVE WON THE GAME------------------------\n");
        exit(1);
    }
}

int main()
{
    printf("-------------------INFORMATION SCREEN----------------------\n");
    printf("--------------THE LETTER F STANDS FOR FLAGGÝNG-------------\n");
    printf("--------------THE LETTER F STANDS FOR DIGGING--------------\n");
    int **p;
    p=(int **)calloc(SIZE,sizeof(int*));
    for(int i=0;i<SIZE;i++)
    {
        p[i]=(int *)calloc(SIZE,sizeof(int));
    }
    int total=0;
    if(p==NULL)
    {
        printf("Memory could not be allocated successfully");
        exit(1);
    }
    else
    {
     rastgele(p,&total);
     sayilar(p);
    }
    double *A = (double *)calloc(SIZE * SIZE, sizeof(double));
    double *B = (double *)calloc(SIZE * SIZE, sizeof(double));
    int id=0;
    printf("TOTAL NUMBER OF BOMBS: %d\n",total);
    printf("       ");
    for(int i=0;i<SIZE;i++)
    {
        printf("%3d",i+1);
    }
    printf("\n");
    printf("       ");
     for(int i=0;i<SIZE;i++)
    {
        printf("___");
    }
    printf("\n");
    for(int i=0;i<SIZE;i++)
    {
        printf("%3d   |",i+1);
        for(int j=0;j<SIZE;j++)
        {
            if(p[i][j]==-1)
                 printf("  #");
              // printf(" B");
            else
                printf("  #");
               // printf("%3d",p[i][j]);
        }
        printf("\n");
    }
    int t=0;
    int u=0;
    while(1)
    {
        char op;
        int sa,su;
        printf("ENTER THE LETTER VALUES FIRST, THEN THE ROW AND COLUMN VALUES.\n");
        scanf(" %c",&op);
      if('E'==op)
          {
            scanf("%d %d",&sa,&su);
            if(sa<1||sa>SIZE||su<1||su>SIZE)
            {
                printf("FIELD BOUNDARIES EXCEEDED!!!!\n");
                printf("PLEASE ENTER ROWS AND COLUMNS WITHIN LIMITS!!!!\n");
            }
            sa--;
            su--;
            acici(p,sa,su,A,&id,&t);
            yazdir(p,A,B,total);
          }
        else if(op=='F')
            {
            scanf("%d %d",&sa,&su);
             if(sa<1||sa>SIZE||su<1||su>SIZE)
            {
                printf("FIELD BOUNDARIES EXCEEDED!!!!\n");
                printf("PLEASE ENTER ROWS AND COLUMNS WITHIN LIMITS!!!!\n");
            }
            sa--;
            su--;
            unsigned long h;
            h=(unsigned long)&p[sa][su];
            B[u]=(double)h;
            u++;
            yazdir(p,A,B,total);
            }
            else
            {
                printf("PLEASE ENTER A VALID CHARACTER.(E-F)\n");
            }
    }
    for(int i=0;i<SIZE;i++)
    {
        free(p[i]);
    }
    free(p);
    free(A);
    free(B);



    return 0;
}
