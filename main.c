#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<conio.h>
#include<ctype.h>
#define MAX 1000
#define BOLD "\x1B[1m"
#define RESET_BOLD "\x1B[0m"
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
    printf("Player 1 score : %d",score1);
    reset_color();
    printf("                 |       ");
    yellow();
    printf("Player 2 score : %d\n",score2);
    reset_color();
}
void score_print(int rows,int col,char a[rows][col])
{
    int score1, score2;
    score1 = score(rows,col,a,'X');
    score2 = score(rows,col,a,'O');
    score_color(score1,score2);
}
void moves_print(int moves1 , int moves2)
{
    red();
    printf("Player 1 number of moves : %d",moves1);
    reset_color();
    printf("       |       ");
    yellow();
    printf("Player 2 number of moves : %d\n",moves2);
    reset_color();
}
void moves_counter(int counter)
{
    int moves1 = 0 , moves2 = 0 ;
    moves1 = counter/2 + counter%2 ;
    moves2 = counter/2 ;
    moves_print(moves1,moves2);
}
void mini_menu(int col)
{
    printf("Please choose one of the following :\n");
    printf("X     : To reset the game\n");
    printf("U     : To undo last move\n");
    printf("R     : To redo last undo\n");
    printf("S     : To save the game\n");
    printf("E     : To exit the game\n");
    printf("1->%d : To choose a column\n",col);

}
void eachtime_print(int rows,int col,char a[][col],int turn)
{
    if (turn%2 == 0){
        red();
        printf("Player 1 turn !\n");
        mini_menu(col);
        printf("Your Choice : ");
        reset_color();
    }
    else if (turn%2 == 1){
        yellow();
        printf("Player 2 turn !\n");
        mini_menu(col);
        printf("Your Choice : ");
        reset_color();
    }
}
//this function is used to check if the string has a number or a string or neither
int num_str_check(char choice[])
{
    int flag = -1 ;
    for (int i=0;i<strlen(choice);i++){
        if (isdigit(choice[i])){
            flag = 1 ;
        }
        else if (isalpha(choice[i])){
            flag = 0 ;
        }
    }
    return flag ;
}
//this function extract a number from a string
int num_extract(char choice[])
{
    int no_of_col = 0 , p = 0;
    for (int i=0;i<strlen(choice);i++){
        if (isspace(choice[i])){
            continue ;
        }
        else if (isdigit(choice[i])){
            no_of_col = (choice[i]-'0')*pow(10,p) + no_of_col ;
            p++ ;
        }
    }
    return no_of_col ;
}
//this function extract a char from a string
char ch_extract(char choice[])
{
    char ch ;
    for (int i=0;i<strlen(choice);i++){
        if (isspace(choice[i])){
            continue ;
        }
        else if(isalpha(choice[i])){
            ch = choice[i] ;
        }
    }
    return ch ;
}
int options(int rows,int col,char a[][col],int turn,int moves_seq[])
{
    char choice[30] ;
    score_print(rows,col,a);
    moves_counter(turn);
    while ( 1 ){
        eachtime_print(rows,col,a,turn);
        fgets(choice,28,stdin);
        if (num_str_check(choice)==1)
        {
            int no_of_col = 0 ;
            no_of_col = num_extract(choice);
            if (no_of_col>0 && no_of_col<=col && a[1][no_of_col]==' '){
                moves_seq[turn] = no_of_col ;
                return no_of_col ;
            }
        }
        else if (num_str_check(choice)==0)
        {
            switch (toupper(ch_extract(choice))){
                case 'X' :  //reset
                    break ;
                case 'U' :  //undo
                    break ;
                case 'R' :  //redo
                    break ;
                case 'S' :  //save
                    break ;
                case 'E' :  //exit
                    break ;
            }
            return -1;
        }
    }
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
void fill_grid(int turns,int num_of_col,int n,int m,char a[][m])
{
    for (int jj=n; jj>0; jj--)
    {
        if (a[jj][num_of_col]==' ')
        {
            if (turns%2==0)
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
void play(int rows,int col,char a[][col],int moves_seq[])
{
    //check if the game is over or not as it should return 0 if it's over
    int counter = 0 ;
    while (check_gameover (col,a))
    {
        options(rows,col,a,counter,moves_seq);
        fill_grid(counter,moves_seq[counter],rows,col,a);
        grid(rows,col,a);
        counter++;
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
    int moves_seq[rows*col] ;
    intial_arr(rows,col,scores);
    grid(rows,col,scores);
    play(rows,col,scores,moves_seq);

    return 0;
}
