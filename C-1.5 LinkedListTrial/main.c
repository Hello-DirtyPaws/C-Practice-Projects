/* 
 * File:   main.c
 * Author: surajupadhyay
 *
 * Created on September 21, 2018, 10:17 PM
 */

#include<stdio.h>
#include<stdlib.h>

typedef struct _Node
  {
    int val;
    struct _Node *next;
     
  }Node;
  
  

Node* addLast(Node*, Node*);
int getSize(Node*);
Node* merge(Node*, Node*, Node*);
Node* devide(Node*, int);
void printList(Node*);
char* trim(char*);
int isDigit(char*);
int compareTo(char*, char*);
Node* head;


///////
//int key = 0;
//////





int main(void)
{
    for (int i = 3; i >= 0; i--) 
    {
        Node *obj = (Node*) malloc(sizeof (Node));
        obj->val = i;
        obj->next = NULL;
        head = addLast(head, obj);
    } 
 
    for (int i = 4; i < 9; i++) 
    {
        Node *obj = (Node*) malloc(sizeof (Node));
        obj->val = i;
        obj->next = NULL;
        head = addLast(head, obj);
    } 
    
    for (int i = 30; i > 15; i--) 
    {
        Node *obj = (Node*) malloc(sizeof (Node));
        obj->val = i;
        obj->next = NULL;
        head = addLast(head, obj);
    }  
    
 printf("The size of the list is: %d\n", getSize(head));
 printf("The unsorted list is: \n");
 printList(head);
 
 Node *sortedList = (Node*)malloc(sizeof(Node));
  
 sortedList = devide(head, getSize(head));
 
 printf("The sorted list is: \n");
 printList(sortedList);

 return 0;
}

///MERGE SORTINGS
//////////////////////////////////////////////////

Node* devide(Node *temp, int size)
{
   
    if(size > 1)
    {
        
        Node *temp1 = temp;
        for(int i = 1; i < size/2; i++)
        {
            temp1 = temp1->next;
        }
        Node *x = temp1->next;
        temp1->next = NULL;
        temp1 = x;
        
        temp = devide(temp, size/2);
                
        temp1 = devide(temp1, size - size/2);
                
        Node * sorted = NULL;
            sorted = merge(temp, temp1, sorted);
        
        
        return sorted;
    }
    return temp;
    
}

int getSize(Node *curr)
{
    int i = 0;
    
    while(curr != NULL)
    {
        i++;
        curr = curr->next;
    }
    
    return i;
}

Node* merge(Node *n1, Node *n2, Node *sorted)
{
    
    Node *temp;
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
        if (n1->val <= n2->val)//if( compareTo(n1->arr[key],n2->arr[key]) <= 0)
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

Node* addLast(Node *temp, Node *n)
{    
    if (temp == NULL) 
    {
        n->next = NULL;
        return n;
    } 
    else 
    {
        Node *curr = temp;
        while (curr->next != NULL) 
        {
            curr = curr->next;
        }
        curr->next = n;
        n->next = NULL;
    }
    return temp;    
}

void printList(Node *temp)
{
   if(temp != NULL)
    {
        Node *curr = temp;
        while (curr != NULL) 
        {
            printf("%d==>", curr->val);
            curr = curr->next;
        }
    }
   printf("NULL.\n");
}


///STRING MANIPULATORS
///////////////////////////////////////////

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

//////////////////////////////////////////
