/* 
 * File:   main.c
 * Author: surajupadhyay
 *
 * Created on September 16, 2018, 2:34 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
 * 
 */
int binToDec(char[]);
char* giveMantis(char[]);
double finalFunc(char, int, char[]);

int main(int argc, char** argv) 
{
    char* fpn = (char*) malloc(32*sizeof(char));
    
    fpn = "11000001000100000000000000000000";//-9.0
    
    int expoVal = binToDec(fpn);
    
    printf("The fpn value entered is: %s\n", fpn);
    
    char* mantiss = giveMantis(fpn);
     
    
    printf("The decimal answer is answer is: %f", finalFunc(fpn[0], expoVal, mantiss));
    
    
    return (EXIT_SUCCESS);
}

int binToDec(char exp[])
{
    int decNum = 0;
    for(int i = 8; i >= 1; i--)
    {
        if(exp[i] == '1')
        {
            decNum = decNum + pow(2, 8 - i);
        }
    }
    decNum = decNum - 127;
    
    return decNum;
}

char *giveMantis(char mant[])
{
    int numOfBits = 0;
    for(int i = 9; i < 32; i++)
    {
        if(mant[i] == '1')
        {
            numOfBits = i - 8;
        }
    }
    
    if(numOfBits <= 0)
    {
        return "0";
    }
    else
    {
        char* mantiss = (char*) malloc(numOfBits * sizeof (char));
        if (mantiss == NULL) exit(1);

        for (int i = 0; i < numOfBits; i++)
        {
            mantiss[i] = mant[i + 9];
        }

        return mantiss;
    }
    
}

double finalFunc(char sign, int exp, char mant[])
{
    int decNum = 0;
    
    for(int i = 0; i < exp; i++)
    {
        if(mant[i] == '1')
        {
            decNum += pow(2, exp - 1 - i);
        }
    }
    
    decNum += pow(2, exp);
    
    if(sign == '1') decNum = (-1) * decNum;
    
    return decNum;
}
