#include<stdio.h>
#include<string.h>
#define MAX 1000
struct {
char player1;
char player2;
}color;
int choose_col(int m,char a[][m])
{
   int num_of_col;
   do {
   printf("please choose the number of column you want\n");
   scanf ("%d",&num_of_col);
   }
   while (a[1][num_of_col]!=' ' || num_of_col<1 || num_of_col>m);
   return num_of_col;
}
int check_gameover (int m,char a[][m])
{
    for (int ii =1; ii<=m; ii++)
    {
        if (a[1][ii]==' '){
        return 1 ;
        }
    }
return 0;
}
void fill_grid(int turn,int num_of_col,int n,int m,char a[][m])
{
    for (int jj=n; jj>0;jj--)
    {
        if (a[jj][num_of_col]==' ')
        {
            if (turn%2==0){
                a[jj][num_of_col]='X';}
            else{
                a[jj][num_of_col]='O';}
        break;
        }
    }
}
void _incolor (char x)
{
    if (x=='y')
        printf("\033[1;33m");
    else if (x=='r')
        printf("\033[1;31m");
    else
        printf("\033[0m");
}
//print number of each column
void header(int m)
    {
        for (int i=1;i<=m;i++)
        {
            if (i<10)
                printf("  %d ",i);
            else
                printf(" %d ",i);
        }
         printf("\n");
    }
//print a fixed boarder between each row
void bar (int col)
{
    for (int i=0;i<col;i++)
    {
        printf("|---");
    }
    printf("|\n");
}
//intializing the array
void intial_arr (int rows,int col,char a[][col])
{
    for (int i = 1; i <= rows; i++)
    {
        for (int j = 1; j <= col; j++)
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

void play(int n,int m,char a[][m])
{
    // using a counter to know who's player should play and to be helpful when using undo or redo
    /*printf("please,choose your color \nyellow -> y\nred   -> r\n");
    scanf ("\n%c",&color.player1);
    if (color.player1=='y')
        color.player2='r' ;
    else
        color.player2='y' ;*/
   //check if the game is over or not as it should return 0 if it's over
    int counter =0;
    while (check_gameover (m,a))
    {
        fill_grid(counter,choose_col(m,a),n,m,a);
        grid(n,m,a);
        counter ++;
    }
}
int main()
{
    int rows, col;
    scanf("%d %d",&rows,&col);
    char scores[MAX][MAX];
    intial_arr(rows,col,scores);
    grid(rows,col,scores);
    play(rows,col,scores);

    return 0;
}
