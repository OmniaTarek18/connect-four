#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#define MAX 100
FILE* fp;
void lower_case(char s[])
{
    int j=0;
    for (int i=0; s[i] != '\0'; i++)
    {
        if (isspace(s[i])==0)
            s[j++]=tolower(s[i]);
    }
}
typedef struct
{
    int height;
    int width;
    int high;
} inform;
void corruption ()
{
    int n;
    printf("FILE CORRUPTED..!!Please,enter the path\n");
    scanf("%d",&n);
}
int num_extract(char choice[])
{
    int no_of_col = 0, p = 0;
    for (int i=0; i<strlen(choice); i++)
    {
        if (isspace(choice[i]))
        {
            continue ;
        }
        else if (isdigit(choice[i]))
        {
            no_of_col = (choice[i]-'0')*pow(10,p) + no_of_col ;
            p++ ;
        }
    }
    return no_of_col ;
}
inform search_for(char s[],int num)
{
    inform in;
    if (strcmp(s,"height")==0)
        in.height =num ;
    else if (strcmp(s,"width")==0)
        in.width =num ;
    else if (strcmp(s,"highscores")==0)
        in.high=num ;
    else
    {
        corruption();

    }
    return in;
}
//ignore anything until find open tag else just corruption
int clean_to_open()
{
    char c ;
    while ((c=fgetc(fp))!= EOF) //instead \n put EOF
    {
        if (c == '<')
            return 1;
    }
    corruption();
    return 0;
}
//store a string to find the number in each row
int clean_to_open2(char s3[])
{
    char c ;
    int i=0;
    while ((c=fgetc(fp))!= EOF) //instead \n put EOF
    {
        if (c == '<')
            return 1;
        else
            s3[i]=fgetc(fp);
    }
    corruption();
    return 0;
}
//read the whole string between tags
int read_to_close(char s[])
{
    char c;
    int i=0;
    while ((c=fgetc(fp)) != EOF)  //instead \n put EOF
    {
        if (c != '>')
        {
            s[i]= c;
            i++;
        }
        else
        {
            s[i]='\0';
            return 1;
        }
    }
    corruption();
    return 0;
}
void intialize(char s[],char k[])
{
    for (int i=0; s[i] !='\0'; i++)
    {
        s[i]='\0';
    }
    for (int i=0; s[i] !='\0'; i++)
    {
        k[i]='\0';
    }

}

inform eachtime (char s[],char s2[])
{
    char s3[MAX];
    inform inform_m ;
    int num=0;
    clean_to_open();
    read_to_close(s);
    clean_to_open2(s3);
    num=num_extract(s3);
    clean_to_open();
    if (fgetc(fp)=='/')
    {
        read_to_close(s2);
        if (strcmp(s,s2)==0)
        {
            lower_case(s);
            inform_m=search_for (s,num);
        }
        else
            corruption();
    }
    else
        corruption();
    return inform_m;
}

int main()
{
    fp =fopen("D:\assignments\fdafds\file.xml","r");
    if (fp == NULL)
        corruption();
    inform i ;
    char string1[MAX];
    char string2[MAX];
    char string3[MAX];
    char string4[MAX];
    clean_to_open();
    read_to_close(string3);
    for (int ii=0;ii<3;ii++){
        i=eachtime(string1,string2);
        intialize(string1,string2);
    }
    clean_to_open();
    read_to_close(string4);
    if (strcmp(string3,string4)!=0)
    corruption();
    fclose(fp);
    printf("%d\n%d\n%d",i.height,i.width,i.high);

}
