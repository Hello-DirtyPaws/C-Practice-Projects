#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* funcPtr(void*);
int counter;

int main(int argc, char** argv) 
{
    counter = 0;
    pthread_t thread;
    pthread_create(&thread, NULL, funcPtr, (void*)2);
    
    int retval = 0;
    
    pthread_join(thread, &retval);
    printf("The counter after thread joined is %d\n", retval);
    
    return (EXIT_SUCCESS);
}

void* funcPtr(void* n)
{
    counter++;
    printf("The value of the counter is %d\n", counter);
    pthread_exit(++n);
}

