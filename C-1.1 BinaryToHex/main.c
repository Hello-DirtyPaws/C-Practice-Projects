/* 
 * File:   main.c
 * Author: surajupadhyay
 *
 * Created on September 14, 2018, 11:15 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
 * 
 */
char decToHex(int);
int binToDec(char []);
int hexToDec(char);
char* decToBin(int);


int main(int argc, char** argv) 
{
    char s[4]; //an arry storing binary 0s and 1s as int upto the size of 4

    printf("Please enter a 4-bit binary number: ");
    fgets(s, 5, stdin);
      
    int decNum = binToDec(s);
    printf("The number in decimal is: %d\n", decNum);
    
    char hexNum = decToHex(decNum);
    printf("The number in hexadecimal is: %c\n", hexNum);
    
    int decNum2 = hexToDec(hexNum);
    printf("The hexnumber converted back in decimal is: %d\n", decNum2);
    
   // char *s2 = (char*)decToBin(decNum2);
    printf("The decimal number converted back to binary is: %s\n", decToBin(decNum2));
    
    return (EXIT_SUCCESS);
}

int binToDec(char binNum[])
{
    int a = 0;
    
    for(int i = 0; i < 4; i++)
    {
        if(binNum[i] == '1')
        {
            a = a + pow(2, 3 - i);
        }
    }
    
    return a;
}

char decToHex(int decNum)
{
    char hexNum = '0' + decNum; 
    
    switch(decNum)
    {
        case 10:
            hexNum = 'A';
            break;
        case 11:
            hexNum = 'B';
            break;
        case 12:
            hexNum = 'C';
            break;
        case 13:
            hexNum = 'D';
            break;
        case 14:
            hexNum = 'E';
            break;
        case 15:
            hexNum = 'F';
            break;
    }
    
    return hexNum;
}

int hexToDec(char hexNum)
{
    int decNum = hexNum - '0'; 
    
    switch(hexNum)
    {
        case 'A':
            decNum = 10;
            break;
        case 'B':
            decNum = 11;
            break;
        case 'C':
            decNum = 12;
            break;
        case 'D':
            decNum = 13;
            break;
        case 'E':
            decNum = 14;
            break;
        case 'F':
            decNum = 15;
            break;
    }
    
    return decNum;

}

char* decToBin(int decNum)
{
    char * binNum = (char*) malloc(4*sizeof(char));
    for(int i = 3; i >= 0; i--)
    {
        binNum[i] = '0' + decNum % 2;
        decNum = decNum / 2;
    }
    free(binNum);
    return binNum;
}



