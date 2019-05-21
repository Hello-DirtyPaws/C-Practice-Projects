/*
 * Suraj Upadhyay
 * CSC 236-02
 * LAB 1 #1
 */

/* 
 * File:   main.c
 * Author: surajupadhyay
 *
 * Created on September 28, 2018, 1:45 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * 
 */

char* trim(char*);
int isDigit(char*);
int compareTo(char*, char*);

int main(void) 
{
    char* str1 = (char*)malloc(sizeof(char));
    char* str2 = (char*)malloc(sizeof(char));
    
    printf("str1: "); scanf("%s", str1); 
    printf("str2: "); scanf("%s", str2); 

    
    printf("The trimmed str1 is: *%s*\n", trim(str1));
    printf("The trimmed str2 is: *%s*\n", trim(str2));

    printf("The comparison of str1 and str 2 is: %d\n", compareTo(str1, str2));
    
    return (EXIT_SUCCESS);
}

char* trim(char* str)
{
    char* temp  = (char*)malloc(sizeof(char));
    char* finalStr = (char*)malloc(sizeof(char));
    int i = 0, j = 0, len = strlen(str);
    
    
    if(len == 0)
    {
        return "";
    }
    
    else
    {
        char c = str[0];
        while(i < len && (c == ' ' || c == '\"'))
        {
            c = str[++i];
            
            /* This code will include the begining quotes in comparing two strings,
             * if they already had quotes in them.
             */ 
            
            /* if(c == '\"')
             * {
             *   temp[j++] = c;
             * }
             */
        }
        
        int trailSpace = 0;
        while(i < len && c != '\"')
        {
            if(c == ' ')
            {
                trailSpace++;
            }
            else
            {
                trailSpace = 0;
            }
            temp[j++] = c;
            c = str[++i];
        }

        /* This code will include the ending quotes in comparing two strings,
         * if they already had quotes in them.
         */

        /* if(c == '\"')
         * {
         *   temp[j++] = c;
         * }
         */
        
        
        /* if including quotes, use (j - trailSpace - 1) in the loop
         * and after the loop add the last char using
         * finalStr[i] = temp[j - 1];
         * j is the length of the temp string.
         */ 
        for(i = 0; i < (j - trailSpace); i++)
        {
            finalStr[i] = temp[i];
        }
                
       /* This is weird..there is a randon char added in the end
        * so have to manually add any arbitary char and replace
        * it by NULL char.
        */
        finalStr[i] = 'F';
        finalStr[i] = '\0';
       
    }
    free(temp);
    return finalStr;
}

int isDigit(char* str)
{
    int i = 0, len = strlen(str), isDigit = 1; //isDigit = true.
    char c;
    
    while(i < len && isDigit == 1)
    {
        c = str[i++];
        if(c < '0' || c > '9')
        {
            isDigit = 0;
        }
    }
    return isDigit;
        
}

int compareTo(char* str1, char* str2)
{
    char* str1Cpy = trim(str1);
    char* str2Cpy = trim(str2);
    
  
    int flag1 = isDigit(str1Cpy);
    int flag2 = isDigit(str2Cpy);
    
    if(flag1 != flag2)
    {
        //One of the str is not an int value
        //thus performing the strcmp
        return strcmp(str1Cpy, str2Cpy);
    }
    else if(flag1 == 0)
    {
        return (strcmp(str1Cpy, str2Cpy));
    }
    else
    {
        return(atoi(str1Cpy)-atoi(str2Cpy));
    }
}
