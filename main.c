#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#define MAX 300
FILE* fb;
int num_to_try=0;
char path[MAX]= {"file.xml"};
char string1[MAX],string2[MAX],string3[MAX],string4[MAX];
typedef struct
{
    int score ;
    char name[300] ;
}player ;
int new_path();
typedef struct
{
    int height;
    int width;
    int high;
} inform;
inform  inf;
int str_cmp(player p,FILE *high)
{
    int rank_p = 0,i=0,j=0,k=0,m=0 ;
    player p_cmp ;
    char n1[MAX] ,n2[MAX] ;
    while (fscanf(high,"%d ",&p_cmp.score) == 1)
    {
        fgets(p_cmp.name,298,high);
        rank_p ++ ;
        for (int i=0; p.name[i] != '\0'; i++)
        {
            if (isspace(p.name[i])==0)
                n1[j++]=tolower(p.name[i]);
        }
        for (int k=0; p_cmp.name[k] != '\0'; k++)
        {
            if (isspace(p_cmp.name[k])==0)
                n2[m++]=tolower(p_cmp.name[k]);
        }
        if(strcmp(n1,n2) == 0)
        {
            break ;
        }
    }
    return rank_p ;
}
//to add players above the new player in rank
int big_to_equal(FILE *high,FILE *cpy,player p)
{
    int flag = 0 , rank = 0 , rank_p ;
    player p_comp ;
    rank_p = str_cmp(p,high) ;
    while (fscanf(high,"%d ",&p_comp.score) == 1)
    {
        fgets(p_comp.name,298,high);
        if (p.score < p_comp.score)
        {
            rank++ ;
            //if (rank == rank_p)
              //  continue ;
            fprintf(cpy,"%d %s",p_comp.score,p_comp.name);
        }
        else
        {
            rank ++ ;
            fprintf(cpy,"%d %s",p.score,p.name);
            fprintf(cpy,"%d %s",p_comp.score,p_comp.name);
            flag = 1 ;
            break ;
        }
    }
    if (flag == 0)
        fprintf(cpy,"%d %s",p.score,p.name);
    return rank ;
}
// to add players less than the new player in rank
void equal_to_small(FILE *high,FILE *cpy)
{
    player p_comp ;
    while (fscanf(high,"%d ",&p_comp.score) == 1)
    {
        fgets(p_comp.name,298,high);
        fprintf(cpy,"%d %s",p_comp.score,p_comp.name);
    }
}
int read_num(char s3[])
{
    char c ;
    int i=0;
    while ((c=fgetc(fb))!= EOF ) //instead \n put EOF
    {
        if (c == '<')
        {
            s3[i] = '\0' ;
            return 1;
        }
        else if (isalpha(c) || ispunct(c))
        {
            break ;
        }
        else
            s3[i++] = c ;
    }
    return 0;
}
int  search_for(char s[],int num,inform *in)
{
    if (strcmp(s,"height")==0)
        in->height =num ;
    else if (strcmp(s,"width")==0)
        in->width =num ;
    else if (strcmp(s,"highscores")==0)
        in->high=num ;
    else
        return 0;
    return 1;
}

void lower_case(char s[])
{
    int j=0;
    for (int i=0; s[i] != '\0'; i++)
    {
        if (isspace(s[i])==0)
            s[j++]=tolower(s[i]);
    }
    s[j]='\0';
}
void copy_file(FILE *source,FILE *destination)
{
    char ch ;
    while((ch = fgetc(source)) != EOF)
    {
        fputc(ch,destination);
    }
}
int to_open_tag()
{
    char c;
    while ((c=fgetc(fb)) != EOF )
    {
        if (c=='<')
        {
            return 1;
        }
        else if (isspace(c)==0)
            break;
    }
    return 0;
}
// to store string inside the tags
int between_tags(char s[])
{
    char c;
    int i=0;
    while ((c=fgetc(fb)) != EOF )
    {
        if (c=='>'&& i !=0 )
        {
            s[i]='\0';
            return 1;
        }
        else if (c != '<')
            s[i++]=c;
    }
    return 0;
}
inform each_time()
{
    char s[MAX];

    for (int k=0; k<3; k++)
    {
        int n=0;
        if (to_open_tag())
        {
            if (between_tags(string1))
            {
                if (read_num(s))
                {
                    n= atoi(s);
                    if (fgetc(fb)=='/')
                    {
                        if (between_tags(string2))
                        {
                            if (strcmp(string1,string2)==0)
                            {
                                lower_case (string1);
                                if (search_for (string1,n,&inf)==0)
                                {
                                    new_path();
                                }
                            }
                            else
                                new_path();
                        }
                        else
                            new_path();
                    }
                    else
                        new_path();;
                }
                else
                    new_path();
            }
            else
                new_path();
        }
        else
            new_path();
    }
    return inf;
}
void read_xml()
{
    if (to_open_tag())
    {
        if (between_tags(string3))
        {
            each_time(string1,string2);
            if (to_open_tag()&& fgetc(fb)=='/')
            {
                if (between_tags(string4))
                {
                    if (strcmp(string4,string3)!=0)
                        new_path();
                }
                else
                    new_path();
            }
            else
                new_path();
        }
        else
            new_path();
    }
    else
        new_path();
}
int new_path()
{
    if (num_to_try==2)
    {
        inf.height =7 ;
        inf.width =9 ;
        inf.high =10 ;
        return 0;
    }
    printf("please,enter the path of file\n");
    num_to_try++;
    gets(path);
    fb=fopen(path,"r");
    read_xml();
    return 0;
}
void highscore_print(int n,FILE *high)
{
    player p ;
    for (int i=1;i<=n;i++)
    {
        if (fscanf(high,"%d ",&p.score) == 1)
        {
            fgets(p.name,298,high);
            printf("\n\nName  : %sScore : %d\nRank  : %d",p.name,p.score,i);
        }
        else
            break;
    }
}
void highscore(player p,int n)
{
    int rank_p ;
    FILE *high , *cpy ;
    high = fopen("highscores.txt","r+");
    cpy = fopen("copy_highscores.txt","r+");
    rank_p = big_to_equal(high,cpy,p);
    equal_to_small(high,cpy);
    rewind(high);
    rewind(cpy);
    copy_file(cpy,high);
    rewind(high);
    rewind(cpy);
    highscore_print(n,high);
    fclose(cpy);
    fclose(high);
}
int main()
{
    fb = fopen(path,"r");
    if (fb == NULL)
        new_path();
    read_xml();
    fclose(fb);
    int n ;
    printf("%d\n%d\n%d\n",inf.height,inf.width,inf.high);    //to be removed
    player p;
    n = inf.high ;
    p.score = 5 ;                      //to be removed later(end of game higher score)
    fgets(p.name,298,stdin);           //Name of winner
    highscore(p,n);
    return 0;
}
