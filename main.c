#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<conio.h>
#define MAX 1000
struct {
char player1;
char player2;
}color;
int choose_col(int m,char a[][m])
{
    // need to be player 1 please choose a col ,same to player 2
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
int score1_calculate(int i,int j,int rows,int col,char a[rows][col]){
    int score1 = 0 ;
    if (i+3<=rows && j+3<=col && a[i][j]=='X' && a[i+1][j+1]=='X' && a[i+2][j+2]=='X' && a[i+3][j+3]=='X')
        score1++ ;
    if (i+3<=rows && j-3>0 && a[i][j]=='X' && a[i+1][j-1]=='X' && a[i+2][j-2]=='X' && a[i+3][j-3]=='X')
        score1++ ;
    if (i+3<=rows && a[i][j]=='X' && a[i+1][j]=='X' && a[i+2][j]=='X' && a[i+3][j]=='X')
        score1++ ;
    if (j+3<=col && a[i][j]=='X' && a[i][j+1]=='X' && a[i][j+2]=='X' && a[i][j+3]=='X')
        score1++ ;
    return score1 ;
}
int score2_calculate(int i,int j,int rows,int col,char a[rows][col]){
    int score2 = 0 ;
    if (i+3<=rows && j+3<=col && a[i][j]=='O' && a[i+1][j+1]=='O' && a[i+2][j+2]=='O' && a[i+3][j+3]=='O')
        score2++ ;
    if (i+3<=rows && j-3>0 && a[i][j]=='O' && a[i+1][j-1]=='O' && a[i+2][j-2]=='O' && a[i+3][j-3]=='O')
        score2++ ;
    if (i+3<=rows && a[i][j]=='O' && a[i+1][j]=='O' && a[i+2][j]=='O' && a[i+3][j]=='O')
        score2++ ;
    if (j+3<=col && a[i][j]=='O' && a[i][j+1]=='O' && a[i][j+2]=='O' && a[i][j+3]=='O')
        score2++ ;
    return score2 ;
}
void score_calculation(int rows,int col,char a[rows][col]){
    int score1 = 0 , score2 = 0 ;
    for(int i=1 ;i<=rows ;i++){
        for (int j=1 ; j<=col;j++){
            score1 += score1_calculate(i,j,rows,col,a);
            score2 += score2_calculate(i,j,rows,col,a);
        }
    }
    printf("Player1 score is %d",score1);
    printf("\nPlayer2 score is %d\n",score2);
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
void header(int col)
{
    for (int i=1;i<=col;i++)
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
                if (a[i][j]=='X'){
                    printf("|");
                    printf("\033[0;31m");
                    printf(" %c ", a[i][j]);
                    printf("\033[0m");
                }
                else if (a[i][j]=='O'){
                    printf("|");
                    printf("\033[0;33m");
                    printf(" %c ", a[i][j]);
                    printf("\033[0m");
                }
                else {
                    printf("| %c ", a[i][j]);
                }
            }
            printf("|\n");
            bar(m);
        }
    }

void play(int rows,int col,char a[][col])
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
    while (check_gameover (col,a))
    {
        fill_grid(counter,choose_col(col,a),rows,col,a);
        grid(rows,col,a);
        score_calculation(rows,col,a);
        counter ++;
    }
}

int main()
{
    int rows, col;
    scanf("%d %d",&rows,&col);
    while(rows<4 && col<4){
        printf("INVALID BOARD SIZE!\n");
        scanf("%d %d",&rows,&col);
    }
    char scores[MAX][MAX];
    intial_arr(rows,col,scores);
    grid(rows,col,scores);
    play(rows,col,scores);

    return 0;
}
