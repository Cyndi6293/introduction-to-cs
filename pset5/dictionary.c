/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    //need to convert input word into dictionary standart, that is lovercase    
    char* inWord = malloc( LENGTH*sizeof(char) +1 );
    int j = 0;
    while ( word[j] != '\0' )
    {
        inWord[j] = tolower( word[j] );
        j++;
    }
    inWord[j] = '\0';
    //calculate index in htable for lovercased input word
    int hCode = hashCode(inWord, BUCKETS);
    node *np = hTable[hCode];
    //search for word in bucket of hTable, which is linked list
    while (np != NULL)
    {
        int res = strcmp(np->word, inWord);      
        if( res == 0 )
        {
            free(inWord);
            return true;
        }
        //Nodes in linked list end up reverse sorteed, because dictionary is always sorted
        //so if our word is "less" than word from linked list, then we passed all "bigger" ones
        // and will never find search item, because it isn't here, might as well return false
        else if( res < 0 )
        {
            free(inWord);
            return false;
        }       
        np = np->next;
    }
    free(inWord);
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    //initialize our word string
    char* word = malloc( LENGTH*sizeof(char) +1);
    //initialize hTable with NULL-pointers
    for (int i = 0; i < BUCKETS; i++)
    {
        hTable[i] = NULL;
    }
    //read word from dictionary, calculate it's hCode, append to apropriate bucket of hTable
    FILE* fp = fopen(dictionary, "r");
    int hCode;
    while ( fscanf(fp, "%s", word) != EOF )
    {
        hCode = hashCode(word, BUCKETS);
        append(hCode, word);
        word = malloc( LENGTH*sizeof(char)  +1);
    }
    free (word);
    if (ferror(fp))
    {
        fclose(fp);        
        return false;
    }
    fclose(fp);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    int count = 0;
    node * np;
    for (int i = 0; i < BUCKETS; i++)
    {
        np = hTable[i];
        while (np != NULL)
        {
            count++;
            np = np->next;
        }
    }
    return count;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    for(int i = 0; i < BUCKETS; i++)
    {
        node *prev = NULL, *current = hTable[i];        
        while( current != NULL)
        {
            if (prev != NULL)
            {
                free(prev);
            }
            free( current->word );
            prev = current;
            current = current->next;
        }
        free(prev);        
    }
    return true;
}

//Genrates hash-code for some word, that is index in array of size [buckets]
int hashCode(const char* word, int buckets)
{
    int hCode = 0, i = 0;
    while (word[i] != '\0')
    {
        hCode += word[i];
        i++;
    }
    return hCode % buckets;
}

//function that appends word to htable's bucket at the head of bucket
void append(int bucket, char* word)
{
    if (hTable[bucket] == NULL)
    {
        hTable[bucket] = malloc( sizeof(node) );        
        hTable[bucket]->word = word;
        hTable[bucket]->next = NULL;
    }
    else
    {
        node* newnode = malloc( sizeof(node) );        
        newnode->word = word;
        newnode->next = hTable[bucket];
        hTable[bucket] = newnode;
    }    
}
