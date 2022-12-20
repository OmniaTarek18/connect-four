#include<stdio.h>
#include<conio.h>
void header(int col)
    {
        for (int i=1;i<=col;i++)
        {
            printf("  %d ",i);
        }
         printf("\n");
    }
void bar (int col)
{
    for (int i=0;i<col;i++)
    {
        printf("|---");
    }
    printf("|\n");
}
int main()
{
    int rows , col;
    scanf("%d %d",&rows,&col);
    char scores[rows][col];
    for (int i = 1; i <= rows; i++)
    {
        for (int j = 1; j <= col; j++)
        {
            scores[i][j]=' ';
        }
    }
    header(col);
    bar(col);
    int i, j;
    for (i = 1; i <=rows; i++)
    {
        for (j = 1; j <= col; j++)
        {
            printf("| %c ", scores[i][j]);
        }
        printf("|\n");
        bar(col);
    }
   return 0;
}
