#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "s2.h"


///////////////////////////////////////////

int readHeadings();
RECORD* readData();
void print(RECORD *);
Node* headingsHead; // Root Node for storing headings.

///////////////////////////////////////////


//Definitions from my code..
///////////////////////////////////////////
RECORD* addLast(RECORD*, RECORD*);
int getSize(RECORD*);
RECORD* merge(RECORD*, RECORD*, RECORD*);
RECORD* divide(RECORD*, int);
void printList(RECORD*);
char* trim(char*);
int isDigit(char*);
int compareTo(char*, char*);
RECORD* head;
int isItHere(char *, Node*);
void printHeadings(Node *);


void printtSome(RECORD*);

int key = 0; //needed as global.
///////////////////////////////////////////


int main(int argc, char *argv[])
{
    int size = readHeadings();
    key = isItHere(argv[2], headingsHead);
    if (key >= 0) 
    {
    	//Array to hold the headings in the CSV
    	RECORD *first = (RECORD *)malloc(sizeof(RECORD));
        
        //read data into first
        first = readData();
        int numNodes = getSize(first);
        first = divide(first, numNodes);
        printHeadings(headingsHead);
        print(first);
    }
    
    else
    {
	 printHeadings(headingsHead);
         printf("\n***************-----------------------****************\n");
         printf("**%s does not exist in the file! Please try another!**\n",argv[2]);
         printf("***************-----------------------****************\n");
    }

	return 0;
}

int readHeadings()
{
    int size = 0, i = 0;
    headingsHead = NULL;
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

        Node *newNode = (Node*) malloc(sizeof (Node));
        newNode->next = NULL;
        newNode->string = str;


        //adding it to the end of the headingLinkedList.
        if (headingsHead == NULL) 
        {
            headingsHead = newNode;
        } 
        else
        {
            Node* curr = headingsHead;
            while (curr->next != NULL) 
            {
                curr = curr->next;
            }
            curr->next = newNode;
        }
        if(buffer != '\n')
            status = read(STDIN,&buffer,1);            
    }
        
    return size;
}

RECORD * readData()
{
    RECORD *temp, *head;
    temp = head = NULL;
    int status = 1;
    //Read to the end of file
    while (status > 0) 
    {
        //Allocate space
        RECORD *current = (RECORD *)malloc(sizeof(RECORD));
        
        //Fill the current node with data
        int j = 0, i =1;
        char buffer = (char)0;
        char array[400];
        //Loop that reads the first row in the file
        // and store in an array
        
        for (;buffer != '\n' && i > 0;j++) 
        {
            i =0;
            status = read(STDIN, &buffer, 1);	//Read a character
            // Read the characters
            while (!(buffer == ',' || buffer == '\n') && status > 0) 
            {
                if (buffer != '\"') 
                {
                    array[i] = buffer;
                    i++;
                }
                else 
                {
                    int flag = 0;
                    while (!(flag == 1 && buffer ==',') && (buffer != '\n')) 
                    {
                        array[i] = buffer;
                        i++;
                        status = read(STDIN, &buffer, 1);
                        
                        if (buffer == '\"') 
                            flag = 1;
                    }
                    break;	// brake the loop 
                }
                status = read(STDIN, &buffer, 1);	//Read a character
            }//end inner loop
        
            if (i > 0) 
            {
                char* arr = (char*)malloc(i*sizeof(char));
                
                //Copy the characters in an array of i sized
                for (int k = 0;k < i;k++) 
                {
                    arr[k] = array[k];	//point arr to the character in array
                }
                
                // Allow space to be allocated in the heading array
                current->array[j] = (char *)malloc((i) * sizeof(char)+1);
                    
                //Copy the string in arr to heading array
                for(int z = 0; z <= i; z++)
                {
                    if (z == i) 
                    {
                        current->array[j][z] = '\0';
                        break;
                    }
                    current->array[j][z] = arr[z];
                }
            }
            else if (i == 0 && status != 0)
            {
                i = 1;
            }
        
        }//end row loop
        //set proper pointers
        if (temp != NULL) 
        {
            head-> next = current;
            head = current;
        }
        
        else
        {
            temp = head = current;
        }
    }//end file loop
    head = NULL;
    head = temp;
    return temp;
}

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

     
//////////////////////////////////////
//My code starts here bro...
//It is merge sort and string trimer. 
//I will need a key value [key]-- location in the array on what to sort.
//All methods are derectly or indirectly so no changes in any methods at any cost.
//////////////////////////////////////

//Dont change.

RECORD* divide(RECORD *temp, int size)
{
   
    if(size > 1)
    {
        
        RECORD *temp1 = temp;
        for(int i = 1; i < size/2; i++)
        {
            temp1 = temp1->next;
        }
        RECORD *x = temp1->next;
        temp1->next = NULL;
        temp1 = x;
        
        temp = divide(temp, size/2);
                
        temp1 = divide(temp1, size - size/2);
                
        RECORD * sorted = NULL;
            sorted = merge(temp, temp1, sorted);
        
        
        return sorted;
    }
    return temp;
    
}

//Dont change.
int getSize(RECORD *curr)
{
    int i = 0;
    
    while(curr != NULL)
    {
        i++;
        curr = curr->next;
    }
    
    return i;
}

//Dont change.
RECORD* merge(RECORD *n1, RECORD *n2, RECORD *sorted)
{
    
    RECORD *temp;
    if (n1 == NULL) 
    {
        while (n2 != NULL) 
        {
            temp = n2->next;
            sorted = addLast(sorted, n2);
            n2 = temp;
        }
        return sorted;
    } 
    if (n2 == NULL) 
    {
        while (n1 != NULL) 
        {
            temp = n1->next;
            sorted = addLast(sorted, n1);
            n1 = temp;
        }
        return sorted;
    }
    else //n1 != null and n2 != null
    {
        //if (n1->val <= n2->val)
        if(compareTo(n1->array[key],n2->array[key]) <= 0)
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

//Dont change.
RECORD* addLast(RECORD *temp, RECORD *n)
{    
    if (temp == NULL) 
    {
        n->next = NULL;
        return n;
    } 
    else 
    {
        RECORD *curr = temp;
        while (curr->next != NULL) 
        {
            curr = curr->next;
        }
        curr->next = n;
        n->next = NULL;
    }
    return temp;    
}

///STRING MANIPULATORS
///////////////////////////////////////////

//Dont change.
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

//Dont change.
int isDigit(char* str)
{
    int i = 0, len = strlen(str), isDigit = 1; //isDigit = true.
    char c;
    
    str[len-1] = '\0';
        
    while(i < (len-1) && isDigit == 1)
    {
        c = str[i++];
        if((c < '0' || c > '9') && c != '.')//true == not a digit.
        {
            isDigit = 0;
        }
    }
            
    return isDigit;
        
}

//Dont change.
int compareTo(char* str1, char* str2)
{
    if(str1 == NULL)
    {
        return -1;
    }
    if(str2 == NULL)
    {
        return 1;
    }
        
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
        return(atof(str1Cpy)-atof(str2Cpy));
    }
}

//////////////////////////////////////////



//checks if arg exists in the heading
int isItHere(char *arg, Node *x)
{
    Node *y = x;
    int flag = -1;
    int i;
    for(i = 0;y != NULL;i++) 
    {
        if (strcmp(y->string, arg)==0)
         {
            flag = i;
            return flag;
         }
        y = y->next;
    }
    
    return flag;
}
//////////////////////////////////////////

void printHeadings(Node *headings)
{
    Node *l = headings;
    if(l != NULL)
    {
        Node * curr = l;
        while (curr->next != NULL)
        {
            printf("%s,", curr->string);
            curr = curr->next;
        }
        printf("%s\n", curr->string);
    }
}
