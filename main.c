#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#define MAX 200
FILE* fb;
int num_to_try=0;
char path[MAX]= {"file.xml"};
char string1[MAX],string2[MAX],string3[MAX],string4[MAX];
int new_path();
typedef struct
{
    int height;
    int width;
    int high;
} inform;
inform  inf;
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
int main()
{
    fb = fopen(path,"r");
    if (fb == NULL)
        new_path();
    read_xml();
    fclose(fb);
    printf("%d\n%d\n%d\n",inf.height,inf.high,inf.width);
    return 0;
}
