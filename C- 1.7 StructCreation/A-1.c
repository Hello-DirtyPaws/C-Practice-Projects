#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "s.h"

int HEADING_SIZE = 9;

//Prototypes
void readHeadings(char*[]);
RECORD* readData();
void print(RECORD *);

//main
int main(int argc, char *argv[])
{
	//Array to hold the headings in the CSV
	char *heading[HEADING_SIZE];
	RECORD *first = (RECORD *)malloc(sizeof(RECORD));
	/*
	Node *headings;
	int size = readHeadings(headings);	
	
	printf("The number of cols are: %d\n", size);
	*/
	readHeadings(heading);
	first = readData();
	if (first == NULL)  
	{
			printf("first is NULL!");
	}
	else
	{
	print(first);
	}

	return 0;
}
/*
//Read the headings 

int readHeadings(Node* head)
{
	int size = 0, i = 0;
	head = NULL;
	char buffer;
	int status = read(STDIN, &buffer, 1);
	while(status > 0 && buffer != '\n')
	{
		char* str = (char*)malloc(1);
		size++;
		while(buffer != ',' && buffer != '\n')
		{
			str[i++] = buffer;
			status = read(STDIN, &buffer, 1);
		}
		i = 0;
		if(buffer == ',')
		{
			Node *newNode = (Node*)malloc(sizeof(Node));
			newNode->next = NULL;
			newNode->string = str;
						
			
			//adding it to the end of the headingLinkedList.
			if(head == NULL)
			{
				head = newNode;
			}
			else 
			{
				Node* curr = head;
				while (curr->next != NULL)
				{
					curr = curr->next;
				}
				curr->next = newNode;

			}
			status = read(STDIN,&buffer,1);
		}
	}
	
	
	
	return size;
}
*/


void readHeadings(char *heading[HEADING_SIZE])
{
	// Declaration of local vars
	
	int status = 1;
	int j = 0;
	int i =1;
	//int num_of_heads=0;
	char incoming = (char)0;
	
	//Loop that reads the first row in the file
	// and store in an array
	for (char array[100];incoming != '\n' && i > 0;j++) 
	{
		incoming = (char)0;
		i =0;
		// Read the character
		while (status != 0) 
		{
			status = read(STDIN, &incoming, 1);	//Read a character
			//As long as the read char isn't a ',' or '\n' do this
			if (incoming != ',' && incoming != '\n') 
			{
				//printf("%s\n", array);
				array[i] = incoming;
				i++;
			}
			
			//Or else break!!
			else if (incoming == ',' || incoming == '\n') 
			{
				
				break;	// Break out the loop
			}
		}//end inner loop
		char* arr = (char*)malloc(i*sizeof(char));
		
		//Copy the characters in an array of i sized
		int k=0;
		for (k = 0;k < i;k++) 
		{
			arr[k] = array[k];	//point arr to the character in array
		}
		
		// Allow space to be allocated in the heading array
		heading[j] = (char *)malloc(k*sizeof(char));
		
		//Copy the string in arr to heading array
		for(int z = 0; z < i; z++)
		{
			heading[j][z] = arr[z];
		}
	}//end outer loop
	/*
	for (int i = 0;i < HEADING_SIZE;i++) 
	{
		if (i < (HEADING_SIZE-1)) {
			printf("%s,",heading[i]);
		}
		else {
			printf("%s\n",heading[i]);
		}
	}*/
}

////////////

/*
void print(RECORD *ptr)
{
	RECORD *y = ptr;
	
		while (y != NULL)
		{
			for(int i = 0; i < HEADING_SIZE; i++)
			{
				if (y->array[i] != NULL)
				{
					if (i < (HEADING_SIZE-1)) 
					{
						printf("%s,", y->array[i]);
					}
					else 
					{
						printf("%s\n",y->array[i]);
					}
				}
				else
				{
					if(i == (HEADING_SIZE-1))
							printf("\n");
					else
						printf(",");
				}
			}
			
			y= y->next;
		}
}
*/
void print(RECORD *ptr)
{
	RECORD *current = ptr;
	for (int i =0;i < 4869;i++) 
	{
		current = current->next;
	}
	printf("%s\n",current->array[2]);
}