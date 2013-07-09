/****************************************************************************
 * dictionary.h
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Declares a dictionary's functionality.
 ***************************************************************************/

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

//number of buckets in hash table
#define BUCKETS 1024

// maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45
//Global variables

//Node of hash table's bucket
typedef struct node
{
    char* word;
    struct node* next;
}node;

//hash table
node* hTable[BUCKETS];
/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word);

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary);

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void);

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void);

//Genrates hash-code for some word, that is index in array of size [buckets]
//array will contain linked lists, thus creating hash-table
int hashCode(const char* word, int buckets);

//function that appends word to htable's bucket
void append(int bucket, char* word);
#endif // DICTIONARY_H
