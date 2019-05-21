#include <stdio.h>
#include <stdlib.h>


int* divide(int*, int);
int* merge(int*, int, int*, int, int*);

int main(void) 
{
    int *temp = (int*) calloc(5, sizeof(int));
    
    temp[0] = 10; temp[1] = 20; temp[2] = 30; temp[3] = 40; temp[4] = 50;
     
    int *temp1 = temp;
    
    printf("The vale of temp is %lu and *temp is %d\n", temp, *temp);
        
    printf("The vale of temp1 is %lu and *temp1 is %d\n", temp1, *temp1);
    
    for(int i = 0; i < 111; i++)
    {
        printf("The vale of i is %d and *temp1 is %d\n", i, *temp1);
        temp1++;
    }
    
    printf("The size of temp is: %d\n", (int)sizeof(temp));
    
    
    free(temp);
    return (EXIT_SUCCESS);
}

int* divide(int* temp, int size)
{
    if(size > 1)
    {   
        int *temp1 = temp + (size/2);
        
        temp = divide(temp, size/2);
                
        temp1 = divide(temp1, size - size/2);
                
        int * sorted = merge(temp, (size/2), temp1, (size-size/2), sorted);
        
        
        return sorted;
    }
    return temp;   
}


int* merge(int *n1, int sizeOFn1, int *n2, int sizeOFn2, int *sorted)
{
    
    int *temp;
    if (sizeOFn1 == 0) 
    {
        while (sizeOFn2 != 0) 
        {
            
            
            
            temp = n2->next;
            sorted = addLast(sorted, n2);
            n2 = temp;
        }
        return sorted;
    } 
    if (sizeOFn2 == 0) 
    {
        while (sizeOFn1 != 0) 
        {
            
            
            
            temp = n1->next;
            sorted = addLast(sorted, n1);
            n1 = temp;
        }
        return sorted;
    }
    else //n1 != null and n2 != null
    {
        if(*n1 <= *n2)
        {
            temp = n1->next;
            sorted = addLast(sorted, n1);
            return merge(temp, n2, sorted);
        } 
        else
        {
            temp = n2->next;
            sorted = addLast(sorted, n2);
            return merge(n1, temp, sorted);
        }
    }
    return sorted;
}



