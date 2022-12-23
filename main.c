#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<conio.h>
#include<ctype.h>
#define MAX 1000
void red ()
{
    system(" ");
    printf("\033[0;31m");
}
void yellow ()
{
    system(" ");
    printf("\033[0;33m");
}
void reset_color ()
{
    system(" ");
    printf("\033[0m");
}
int choose_col(int m,char a[][m],int turn)
{
    // need to be player 1 please choose a coln ,same to player 2
    int num_of_col ;
    if (turn%2 == 0)
    {
        do
        {
            red();
            printf("Player 1 turn !\nPlease choose the number of column you want:\n");
            scanf ("%d",&num_of_col);
            reset_color();
        }
        while (a[1][num_of_col]!=' ' || num_of_col<1 || num_of_col>m );
    }
    else if (turn%2 == 1)
    {
        do
        {
            yellow();
            printf("Player 2 turn !\nPlease choose the number of column you want:\n");
            scanf ("%d",&num_of_col);
            reset_color();
        }
        while (a[1][num_of_col]!=' ' || num_of_col<1 || num_of_col>m );
    }
    return num_of_col;
}
int check_gameover (int m,char a[][m])
{
    for (int ii =1; ii<=m; ii++)
    {
        if (a[1][ii]==' ')
        {
            return 1 ;
        }
    }
    return 0;
}
void fill_grid(int turn,int num_of_col,int n,int m,char a[][m])
{
    for (int jj=n; jj>0; jj--)
    {
        if (a[jj][num_of_col]==' ')
        {
            if (turn%2==0)
            {
                a[jj][num_of_col]='X';
            }
            else
            {
                a[jj][num_of_col]='O';
            }
            break;
        }
    }
}
int col_score(int rows,int col,char a[][col],char y)
{
    int score1=0;
    for(int i=1 ; i<=rows ; i++)
    {
        for (int j=1 ; j<=col; j++)
        {
            if (j+3<=col && a[i][j]==y && a[i][j+1]==y && a[i][j+2]==y && a[i][j+3]==y)
                score1++ ;
        }
    }
    return score1;
}
int row_score(int rows,int col,char a[][col],char y)
{
    int score1=0;
    for(int i=1 ; i<=rows ; i++)
    {
        for (int j=1 ; j<=col; j++)
        {
            if (i+3<=rows && a[i][j]==y && a[i+1][j]==y && a[i+2][j]==y && a[i+3][j]==y)
                score1++ ;
        }
    }
    return score1;
}
int diagonal_score(int rows,int col,char a[][col],char y)
{
    int score1 =0;
    for(int i=1 ; i<=rows ; i++)
    {
        for (int j=1 ; j<=col; j++)
        {
            if (i+3<=rows && j+3<=col && a[i][j]==y && a[i+1][j+1]==y && a[i+2][j+2]==y && a[i+3][j+3]==y)
                score1++ ;
            if (i+3<=rows && j-3>0 && a[i][j]==y && a[i+1][j-1]==y && a[i+2][j-2]==y && a[i+3][j-3]==y)
                score1++ ;
        }
    }
    return score1;
}
int score (int row,int col,char a[][col],char y)
{
    int sco =0;
    sco =row_score( row, col, a,y);
    sco+=col_score( row, col, a,y);
    sco+=diagonal_score( row, col, a,y);
    return sco;
}
void score_color(int score1,int score2)
{
    red();
    printf("Player 1 score is %d",score1);
    reset_color();
    printf("       |       ");
    yellow();
    printf("Player 2 score is %d\n",score2);
    reset_color();
}
void score_print(int rows,int col,char a[rows][col])
{
    int score1, score2;
    score1 = score(rows,col,a,'X');
    score2 = score(rows,col,a,'O');
    score_color(score1,score2);
}
//print number of each column
void header(int col)
{
    for (int i=1; i<=col; i++)
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
    for (int i=0; i<col; i++)
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
            if (a[i][j]=='X')
            {
                printf("|");
                red();
                printf(" %c ", a[i][j]);
                reset_color();
            }
            else if (a[i][j]=='O')
            {
                printf("|");
                yellow();
                printf(" %c ", a[i][j]);
                reset_color();
            }
            else
            {
                printf("| %c ", a[i][j]);
            }
        }
        printf("|\n");
        bar(m);
    }
}
void play(int rows,int col,char a[][col])
{
    //check if the game is over or not as it should return 0 if it's over
    int counter =0;
    while (check_gameover (col,a))
    {
        fill_grid(counter,choose_col(col,a,counter),rows,col,a);
        grid(rows,col,a);
        score_print(rows,col,a);
        counter ++;
    }
}

int main()
{
    int rows, col;
    scanf("%d %d",&rows,&col);
    while(rows<4 && col<4)
    {
        printf("INVALID BOARD SIZE!\n");
        scanf("%d %d",&rows,&col);
    }
    char scores[MAX][MAX];
    intial_arr(rows,col,scores);
    grid(rows,col,scores);
    play(rows,col,scores);

    return 0;
}
