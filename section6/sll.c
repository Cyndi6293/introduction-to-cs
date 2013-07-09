/*************************************************************************
 * sll.c
 *
 * Implements a simple singly-linked list structure for ints.
 ************************************************************************/

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// the size of our test list: feel free to adjust as you wish!
#define TEST_SIZE 10
#define UNINITIATED -1

typedef struct node
{
    // the value to store in this node
    int i;

    // the link to the next node in the list
    struct node* next;
}
node;

// declare the first node of our list (as a global variable)
node* first = NULL;

/**
 * Returns the length of the list.
 */
int length(void)
{
    int i = 1;
    node* current = first;
    if (current == NULL)
    {
        return 0;
    }
    else
    {
        while ( current->next != NULL)
        {
            current = current->next;
            i++;
        }
    }
    return i;
}

/**
 * Returns true if a node in the list contains the value i and false
 * otherwise.
 */
bool contains(int i)
{
    node* current = first;
    if (current != NULL)
    {
        while ( current->next != NULL)
        {
            if ( current->i == i )
            {
                return true;
            }            
            current = current->next;            
        }
    }
    return false;
}

/**
 * Puts a new node containing i at the front (head) of the list.
 */
void prepend(int i)
{
    if (first == NULL)
    {
        first = malloc(sizeof(node));
        first->next = NULL;
        first->i = i;        
    }
    else
    {
        node* current = malloc(sizeof(node));
        current->i = i;
        current->next = first;    
        first = current;
    }
}

/**
 * Puts a new node containing i at the end (tail) of the list.
 */
void append(int i)
{
    if (first == NULL)
    {
        first = malloc(sizeof(node));
        first->next = NULL;
        first->i = i ;
        return;
    }
    else
    {
        //pointer to a new node
        node* current = malloc(sizeof(node));
        current->i = i;
        current->next = NULL;
        //search pointer, with which we search for the end of the list        
        node* findlast;
        findlast = first;
        //search 
        while ( findlast->next != NULL)
        {                       
            findlast = findlast->next;            
        }
        //now append
        findlast->next = current; 
    }   
}

/**
 * Puts a new node containing i at the appropriate position in a list
 * sorted in ascending order.
 */
void insert_sorted(int i)
{
    if (first == NULL)
    {
        first = malloc(sizeof(node));
        first->next = NULL;
        first->i = i;        
    }
    else
    {
        //pointer to a new node
        node* current = malloc(sizeof(node));
        current->i = i;
        current->next = NULL;
        //seeker pointer
        node* seekplace;
        seekplace = first;
        //pointer to memorize prvevious data (in case we need to go back)
        node* prevseek = NULL;    
        while ( true )
        {
            if ( current->i > seekplace->i)
            {
                if(seekplace->next == NULL)
                {
                    seekplace->next = current;
                    return;
                }
                prevseek = seekplace;                       
                seekplace = seekplace->next ;     
            }
            else
            {
                if (prevseek != NULL)
                {                   
                    prevseek->next = current;
                    current->next = seekplace;
                    return;
                }
                else
                {
                    current->next = first;
                    first = current;
                    return;
                }
            }               
        }//end of while search loop
    }
}

/**
 * Implements some simple test code for our singly-linked list.
 */
int main(void)
{
    printf("Prepending ints 0-%d onto the list...", TEST_SIZE);
    for (int i = 0; i < TEST_SIZE; i++)
    {
        prepend(i);
    }
    printf("done!\n");

    printf("Making sure that the list length is indeed %d...", TEST_SIZE);
    assert(length() == TEST_SIZE);
    printf("good!\n");

    printf("Making sure that values are arranged in descending order...");
    node* n = first;
    for (int i = 0; i < TEST_SIZE; i++)
    {
        assert(n != NULL);
        assert(n->i == TEST_SIZE - i - 1);
        n = n->next;
    }
    printf("good!\n");

    printf("Freeing the list...");
    while (first != NULL)
    {
        node* next = first->next;
        free(first);
        first = next;
    }
    printf("done!\n");

    printf("Appending ints 0-%d to the list...", TEST_SIZE);
    for (int i = 0; i < TEST_SIZE; i++)
    {
        append(i);
    }
    printf("done!\n");

    printf("Making sure that the list length is indeed %d...", TEST_SIZE);    
    assert(length() == TEST_SIZE);
    printf("good!\n");

    printf("Making sure that values are arranged in ascending order...");
    n = first;
    for (int i = 0; i < TEST_SIZE; i++)
    {
        assert(n != NULL);
        assert(n->i == i);
        n = n->next;
    }
    printf("good!\n");

    printf("Freeing the list...");
    while (first != NULL)
    {
        node* next = first->next;
        free(first);
        first = next;
    }
    printf("done!\n");

    printf("Inserting %d random ints to the list...", TEST_SIZE);
    for (int i = 0; i < TEST_SIZE; i++)
    {
        insert_sorted(rand() % TEST_SIZE);
    }
    printf("done!\n");

    printf("Making sure that the list length is indeed %d...", TEST_SIZE);
    assert(length() == TEST_SIZE);
    printf("good!\n");

    printf("Making sure that values are arranged in sorted order...");
    n = first;
    int prev = 0;
    for (int i = 0; i < TEST_SIZE; i++)
    {
        assert(n != NULL);
        assert(n->i >= prev);
        prev = n->i;
        n = n->next;
    }
    printf("good!\n");

    printf("Freeing the list...");
    while (first != NULL)
    {
        node* next = first->next;
        free(first);
        first = next;
    }
    printf("done!\n");

    printf("\n********\nSuccess!\n********\n");

    return 0;
}
