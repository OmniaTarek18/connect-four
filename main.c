#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<conio.h>
#include<ctype.h>
#include<time.h>
#define MAX 1000
FILE* f1;
FILE* f2;
FILE* f3;
FILE* k;
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
//to remove any unwanted input from user and overcome any error
int clean_stdin()
{
    while (getchar() != '\n');
    return 1;
}
//print number of each column above the grid
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
//intializing the 2D array
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
//to make sure that the input is number only
int check_scanf(int n)
{
    int check =0;
    check =scanf("%d",&n);
    while (check  != 1)
    {
        scanf("%*[^\n]");
        printf("please ,Enter valid number !\n");
        check =scanf("%d",&n);
    }
    return n;
}
//to make sure that the input is only one character
char check_char(char s)
{
    int first_time = 0;
    char c;
    do
    {
        if (first_time == 0)
            first_time++;
        else
            printf("please enter ONLY ONE letter !!\n");
    }
    while (((scanf("\n%c%c", &s, &c) != 2 || c != '\n')
            && clean_stdin()) || !isalpha(s));
    return s;
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
int main_menu()
{
    int n;
    printf("1     : start a new game\n");
    printf("2     : load a game \n");
    printf("3     : top players\n");
    printf("4     : Quit\n");
    do
    {
        n=check_scanf(n);
    }
    while (n>4 || n<1);
    return n;
}
// print option of the mini menu with th color of the player who should play
void mini_menu_print(int counter)
{
    if (counter %2==0)
        red();
    else
        yellow();
    printf("Please choose one of the following :\n");
    printf("X     : To reset the game\n");
    printf("U     : To undo last move\n");
    printf("R     : To redo last undo\n");
    printf("S     : To save the game\n");
    printf("E     : To go to main menu\n");
    printf("T     : To return to play\n");
    reset_color();
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
int n_file1()
{
    int num=1;
    k=fopen("num.bin","rb");
    fread(&num,sizeof(num),1,k);
    fclose(k);
    return num;
}
void n_file2(int num)
{
    num++;
    k=fopen("num.bin","wb");
    fwrite(&num,sizeof(num),1,k);
    fclose(k);
}
void file_write(FILE* f,int counter,int mode_of_game,int rows,int col,char a[rows][col])
{
    fwrite(&counter, sizeof(counter),1,f);
    fwrite(&mode_of_game, sizeof(mode_of_game),1,f);
    fwrite(&rows, sizeof(rows),1,f);
    fwrite(&col, sizeof(col),1,f);
    fwrite(a,sizeof(char),(rows+1)*(col+1),f);
}
// to save last state of the game in file
void save_m (int counter,int mode_of_game,int rows,int col,char a[rows][col])
{
    int n= n_file1();
    switch (n%3)
    {
    case 1:
        f1=fopen("f1.bin","wb");
        file_write(f1,counter,mode_of_game,rows,col,a);
        fclose(f1);
        break;
    case 2:
        f2=fopen("f2.bin","wb");
        file_write(f2,counter,mode_of_game,rows,col,a);
        fclose(f2);
        break;
    case 0:
        f3=fopen("f3.bin","wb");
        file_write(f3,counter,mode_of_game,rows,col,a);
        fclose(f3);
        break;
    }
    n_file2(n);
}
int choose_col(int mode_of_game,int m,char a[][m],int turn)
{
    int num_of_col ;
    // the input randomly from computer if the mode is comp VS hum

    if(mode_of_game == 1 && turn %2== 1)
        do
        {
            num_of_col= (rand ()% m) +1;
        }
        while (a[1][num_of_col]!=' ');
    //take the the number of col from player and make sure it between range of number of cols and that col is not full
    do
    {
        if (turn%2 == 0)
        {
            red();
            printf("Player 1 turn !\nPlease choose the number of column you want:\n");
            printf("Choose '0' to go to mini menu for redo,undo,reset,save,exit .\n");
            num_of_col=check_scanf(num_of_col);

        }
        else if (mode_of_game == 0 && turn %2== 1)
        {
            yellow();
            printf("Player 2 turn !\nPlease choose the number of column you want:\n");
            printf("Choose '0' to go to mini menu for redo,undo,reset,save,exit .\n");
            num_of_col=check_scanf(num_of_col);
        }
        reset_color();
        //when number of col equals zero that means the player needs to move tom mini menu
        if (num_of_col==0)
            return 0;
    }
    while (a[1][num_of_col]!=' ' || num_of_col<1 || num_of_col>m|| isalpha(num_of_col)==1 );
    return num_of_col;
}
void time_calculate(clock_t start,clock_t end)
{
    int tSec,nSec,tMin,nMin;
    tSec = ((double) (end - start)) / CLOCKS_PER_SEC ;
    nSec = tSec % 60 ;
    tMin = (tSec - nSec) / 60 ;
    nMin = tMin % 60 ;
    printf("Time passed = %d : %d \n",nMin,nSec);
}
void time_print(clock_t start,clock_t end,int turn)
{
    if (turn%2 == 0)
    {
        red();
        time_calculate(start,end);
        reset_color();
    }
    else if (turn%2 == 1)
    {
        yellow();
        time_calculate(start,end);
        reset_color();
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

void undo(int moves_seq[],int *turn,int rows,int col,char a[][col],int redo[],int *redo_count)
{
    if (*turn > 0)
    {
        *turn = *turn - 1 ;
        for (int i=1; i<=rows; i++)
        {
            if (a[i][moves_seq[*turn]]!=' ')
            {
                a[i][moves_seq[*turn]] = ' ' ;
                break ;
            }
        }
        *redo_count = *redo_count + 1 ;
        redo[*redo_count] = moves_seq[*turn] ;
        moves_seq[*turn] = 0 ;
    }
}
void redo(int moves_seq[],int *turn,int rows,int col,char a[][col],int redo_arr[],int *redo_count)
{
    if (*redo_count >= 0)
    {
        for (int i=rows; i>0; i--)
        {
            if (a[i][redo_arr[*redo_count]] == ' ')
            {
                fill_grid(*turn,redo_arr[*redo_count],rows,col,a);
                break ;
            }
        }
        moves_seq[*turn] = redo_arr[*redo_count] ;
        redo_arr[*redo_count] = 0 ;
        *turn = *turn + 1 ;
        *redo_count = *redo_count - 1 ;
    }
}
void moves_print(int moves1, int moves2)
{
    red();
    printf("Player 1 number of moves : %d",moves1);
    reset_color();
    printf("       |       ");
    yellow();
    printf("Player 2 number of moves : %d\n",moves2);
    reset_color();
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
int diagnal_score(int rows,int col,char a[][col],char y)
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
    sco+=diagnal_score( row, col, a,y);
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
void moves_counter(int counter)
{
    int moves1 = 0, moves2 = 0 ;
    moves1 = counter/2 + counter%2 ;
    moves2 = counter/2 ;
    moves_print(moves1,moves2);
}
void reset_game(int rows,int col,int counter,char a[][col])
{
    intial_arr(rows,col,a);
    counter = 0 ;
    grid(rows,col,a);
    moves_counter(counter);
    score_print(rows,col,a);
}
void main_menu_switch(int n,int col,int rows,char scores[][col]);

int play(int counter,int mode_of_game,int rows,int col,char a[rows][col],int moves_seq[])
{
    int redo_arr[rows*col], redo_count = -1 ;
    clock_t start, end ;
    char letter;
    start = clock();
    //check if the game is over or not as it should return 0 if it's over
    while (check_gameover (col,a))
    {
        int choice=choose_col(mode_of_game,col,a,counter);
        while (choice==0)
        {
            mini_menu_print(counter);
            letter =check_char (letter);
            switch (letter)
            {
            case'T':
            case't':
                choice=choose_col(mode_of_game,col,a,counter);
                break;
            case'U':
            case'u':
                undo(moves_seq,&counter,rows,col,a,redo_arr,&redo_count);
                if (mode_of_game==1)
                    undo(moves_seq,&counter,rows,col,a,redo_arr,&redo_count);
                grid(rows,col,a);
                if (counter == -1)
                    counter ++ ;
                end = clock() ;
                moves_counter(counter);
                score_print(rows,col,a);
                time_print(start,end,counter);
                break;
            case'R':
            case'r':
                redo(moves_seq,&counter,rows,col,a,redo_arr,&redo_count);
                if (mode_of_game==1)
                    redo(moves_seq,&counter,rows,col,a,redo_arr,&redo_count);
                grid(rows,col,a);
                end = clock() ;
                moves_counter(counter);
                score_print(rows,col,a);
                time_print(start,end,counter);
                break;
            case'S':
            case's':
                save_m(counter,mode_of_game,rows,col,a);
                break;
            case'E':
                case'e':
                        main_menu_switch(main_menu(),col,rows,a);
                break;
            case'X':
            case'x':
                reset_game(rows,col,counter,a);
                redo_count = -1 ;
                time_print(clock(),clock(),counter);
                break;
            default:
                printf("Please enter valid letter !\n");
                break;
            }
        }
        redo_count= -1;
        moves_seq[counter] = choice ;
        fill_grid(counter,choice,rows,col,a);
        counter ++;
        if ((mode_of_game == 1 && counter%2 ==0)||mode_of_game==0)
        {
            grid(rows,col,a);
            end = clock() ;
            moves_counter(counter);
            score_print(rows,col,a);
            time_print(start,end,counter);
        }
    }
    if (mode_of_game==1 && (rows*col %2)==1)
        grid(rows,col,a);
    return 0;
}
int mode_ofgame()
{
    int mode,first_time =0;
    //choose the mode as the user chooses new game
    printf("Choose the mode you want :\n");
    printf("0     : human VS human\n");
    printf("1     : human VS computer\n");
    //if the user put different number than needed or doesnot put a digit at all
    do
    {
        if (first_time != 0)
            printf("PLEASE ,ENTER 0 OR 1!!\n");
        first_time++;
        mode = check_scanf(mode);
    }
    while (mode != 0 && mode != 1);
    return mode;
}
int load_menu ()
{
    // to choose number of game user want to load
    int numofgame;
    printf("1     : To load first game\n");
    printf("2     : To load second game\n");
    printf("3     : To load third game\n");
    do
    {
        numofgame=check_scanf(numofgame);
    }
    while (numofgame <1 || numofgame >3);
    return numofgame ;
}
void no_game(FILE* f,int rows,int col,char scores[rows][col])
{
    if (f==NULL)
    {
        printf("NO Game Saved !!\n");
        main_menu_switch(main_menu(),col,rows,scores);
    }
}
void main_menu_switch(int n,int col,int rows,char scores[][col])
{
    int mode=0,numofgame=0,counter=0,moves_seq[rows*col];
    switch (n)
    {
    case 1:
        mode=mode_ofgame();
        intial_arr(rows,col,scores);
        grid(rows,col,scores);
        play(counter,mode,rows,col,scores,moves_seq);
        break;
    case 2:
        numofgame=load_menu();
        switch (numofgame)
        {
        case 1:
            f1=fopen("f1.bin","rb");
            no_game(f1,rows,col,scores);
            fread(&counter, sizeof(counter),1,f1);
            fread(&mode, sizeof(mode),1,f1);
            fread(&rows, sizeof(rows),1,f1);
            fread(&col, sizeof(col),1,f1);
            fread(scores,sizeof(char),(rows+1)*(col+1),f1);
            fclose(f1);
            break;
        case 2:
            f2=fopen("f2.bin","rb");
            no_game(f2,rows,col,scores);
            fread(&counter, sizeof(counter),1,f2);
            fread(&mode, sizeof(mode),1,f2);
            fread(&rows, sizeof(rows),1,f2);
            fread(&col, sizeof(col),1,f2);
            fread(scores,sizeof(char),(rows+1)*(col+1),f2);
            fclose(f2);
            break;
        case 3:
            f3=fopen("f3.bin","rb");
            no_game(f3,rows,col,scores);
            fread(&counter, sizeof(counter),1,f3);
            fread(&mode, sizeof(mode),1,f3);
            fread(&rows, sizeof(rows),1,f3);
            fread(&col, sizeof(col),1,f3);
            fread(scores,sizeof(char),(rows+1)*(col+1),f3);
            fclose(f3);
            break;
        }
        grid(rows,col,scores);
        moves_counter(counter);
        score_print(rows,col,scores);
        play(counter,mode,rows,col,scores,moves_seq);
        break;
    case 3:
        break;
    case 4:
        break;
    }
}
int main()
{
    int rows, col, check =0;
    char scores[MAX][MAX];
    int num_ofchoice=0;
    check =scanf("%d %d",&rows,&col);
    //need to be deleted as xml file will replace it
    while (check  != 2)
    {
        scanf("%*[^\n]");
        printf("please ,Enter valid numbers !\n");
        check =scanf("%d %d",&rows,&col);
    }
    //should be add to xml code when it read num if the value isnot correct ask for path
    while((rows<4 && col<4)|| rows<1 || col<1 )
    {
        printf("please ,Enter VALID BOARD SIZE!\n");
        scanf("%d %d",&rows,&col);
    }
    // main menu
    num_ofchoice=main_menu();
    main_menu_switch(num_ofchoice,col,rows,scores);
    return 0;
}
