#include<stdio.h>
#include<string.h>
//print number of each column
void header(int col)
{
    for (int i=1; i<=col; i++)
    {
        printf("  %d ",i);
    }
    printf("\n");
}
//print a fixed boarder between each row
void bar (int col)
{
    for (int i=0; i<col; i++)
    {
        printf("|---");
    }
    printf("|\n");
}
//intializing the array
void intial_arr (int n,int m,char a[][m])
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            a[i][j]=' ';
        }
    }
}
//print the whole grid of the game
 void grid (int n,int m,char a[][m])
    {
        header(m);
        bar(m);
        int i, j;
        for (i = 1; i <=n; i++)
        {
            for (j = 1; j <= m; j++)
            {
                printf("| %c ", a[i][j]);
            }
            printf("|\n");
            bar(m);
        }
    }
int main()
{
    int rows, col;
    scanf("%d %d",&rows,&col);
    char scores[rows][col];
    intial_arr(rows,col,scores);
    grid(rows,col,scores);
    return 0;
}
