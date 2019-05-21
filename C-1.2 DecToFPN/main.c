/* 
 * File:   main.c
 * Author: surajupadhyay
 *
 * Created on September 15, 2018, 10:45 PM
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */

int* decToBin(int);

int max;

int main(void) 
{
    char finalStr[34]; finalStr[0] = '0'; finalStr[1] = ' '; finalStr[10] = ' ';
    int decNum;
    printf("Please enter a decimal number: ");
    scanf("%d", &decNum);
    
    if(decNum < 0) finalStr[0] = '1';
    
    int* revBinArry = decToBin(decNum);
    
    
    int* significand = calloc(23, sizeof(int)); 
    for(int i = 0; i < max; i++)
    {
        significand[i] = revBinArry[max - 1 - i];
    }
    
    for(int i = 11; i < 34; i++)
    {
        finalStr[i] = '0' + significand[i - 11];
    }
    
    int* exponent = decToBin(127 + max);
    for(int i = 2; i < 10; i++)
    {
        finalStr[i] = '0' + exponent[max + 2 - i];
    }
    
    printf("The final string is: ");
    for(int i = 0; i < 34; i++)
    {
        printf("%c", finalStr[i]);
    }
    
    
    free(exponent);
    free(revBinArry);
    free(significand);
    return (EXIT_SUCCESS);
}

int* decToBin(int decNum)
{
    int* temp = calloc(8, sizeof(int));
    
    for(int i = 0; decNum > 0; i++)
    {
        temp[i] = decNum % 2;
        decNum = decNum / 2;
        max = i;
    }    

    return temp;
}



