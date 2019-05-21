/*
 * Suraj Upadhyay
 * CSC 236-02
 * LAB 1 #1
 */

/* 
 * File:   main.c
 * Author: surajupadhyay
 *
 * Created on September 30, 2018, 3:58 PM
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */


int main(void)
{
    int size;
    printf("Please enter the value for size: "); 
    scanf("%d", &size);

    typedef struct _Node 
    {
        char** strArry;
        struct _Node* next;
    } Node;
    
    int i = 0;
    
     
   Node* n = (Node*) malloc(sizeof(Node));
   Node* n2 = (Node*) malloc(sizeof(Node));
   n2->next = n;
   n2->strArry = (char**)malloc(1);
          n2->strArry[0] = "This is it.";
          n2->strArry[1] = "This is NOT it.";
   
   n->strArry = (char**)malloc(size*sizeof(char*));
   char * str = NULL;
   for(i = 0; i < size; i++)
   {
       char * str = " ** ";
       n->strArry[i] = str;
   }
   free(str);
   
    str = "OHHH";
    
   for(i = 0; i < size; i++)
   {
       printf("The value stored at n.strArry[%d] is: %s\n", i, n->strArry[i]);
   }
   
   
   printf("The value at n2->string[0] is: %s\n", n2->strArry[0]);
   printf("The value at n2->string[1] is: %s\n", n2->strArry[1]);
   printf("The new str is: %s\n", str);
   
    return (EXIT_SUCCESS);
}

