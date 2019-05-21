
/* 
 * File:   main.c
 * Author: surajupadhyay
 *
 * Created on September 17, 2018, 4:06 PM
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */
int main(int argc, char** argv)
 {
    FILE *filePtr = fopen("movie_metadata.csv", "r");
    char str[100];
    
    while(fscanf(filePtr, "%s", str) == 1)
    {
        printf("The string val is: %s\n", str);
    }
    
    fclose(filePtr);
        
    return (EXIT_SUCCESS);
}