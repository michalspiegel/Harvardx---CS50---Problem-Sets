//The dictionary.c file from the speller problem

// Implements a dictionary's functionality

//For problem this I came up with a special data structure of mine - a kind of tree - more of a branch really
//this data structure stores data in a linked list, where each node has two next pointers,
//and while one always links to a bigger value(*next_max), the other points always to a smaller value(*next_min), 
//as is normal with classic binary trees, but this time the *next_max pointer then does not point to anything else bigger or smaller-

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next_min;
    struct node *next_max;
}
node;

// Number of buckets in hash table
const unsigned int N = 100000;

// Hash tables
node *table[N];

//size counter
int words_in_dict = 0;


// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int cmp_value;
    int hash_value = hash(word);
    for (node *tmp = table[hash_value]; tmp != NULL; tmp = tmp->next_min)
    {
        //Based on the return value of the strcasecmo we decide if the word we are checking
        //is alphabetically bigger, smaller, or equal(we found it!!) 
        cmp_value = strcasecmp(word, tmp->word);
        if (cmp_value == 0)
        {
            return true;
        }
        //If the compare value is bigger than 0, then it must be a bigger value you are searching for than the value of the word in the current node
        else if (cmp_value > 0)
        {
            //Check if there is a bigger value
            if (tmp->next_max != NULL)
            {   
                //Compare the bigger value with your word
                if (strcasecmp(word, tmp->next_max->word) == 0)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            return false;
        }
    }
    return false;
}

//Hashes word to a number - Here I implemented a djb2 hashing algorithm I found on the internet(http://www.cse.yorku.ca/~oz/hash.html)
unsigned int hash(const char *str)
{
    //Basically outputs random output - random hash table bucket - but with english words -it distributes the words into the hash buckets very equally 
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
    {
        hash = ((hash << 5) + hash) + tolower(c);   /* hash * 33 + c */
    }    
    return hash % (100000);
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    //NULL the hashtable
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }
    //Open file, check for error
    FILE *f_dictionary = fopen(dictionary, "r");
    if (f_dictionary == NULL)
    {
        printf("could not open dict!");
        return 1;
    }
    
    char word[LENGTH + 1];
    //Scan each time for a string on each line
    for (int i = fscanf(f_dictionary, "%s", word); i != EOF; i = fscanf(f_dictionary, "%s", word))
    {
        //Hash the word
        int hash_value = hash(word);
        words_in_dict++;
        //Malloc memory for the node, that is gonna contain the word
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            printf("not enough memory");
            return 1;
        }
        //Copy the word into the node itself
        strcpy(n->word, word);
        
        
        //If there is not a node in the hash bucket
        if (table[hash_value] == NULL)
        {
            n->next_min = NULL;
            n->next_max = NULL;
            table[hash_value] = n;
        }
        //If there is only one node in the bucket
        else if (table[hash_value]->next_min == NULL)
        {
            n->next_min = table[hash_value];
            n->next_max  = NULL;
            table[hash_value] = n;
        }
        //If there is no next_max (bigger) value
        else if (table[hash_value]->next_max == NULL)
        {
            n->next_min = NULL;
            n->next_max = NULL;
            table[hash_value]->next_max = n;

        }
        //If there is a next_max value
        else
        {
            n->next_min = table[hash_value];
            n->next_max  = NULL;
            table[hash_value] = n;
        }


    }
    fclose(f_dictionary);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return words_in_dict;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    //unloads separately for each bucket in the hashtable
    for (int i = 0; i < N; i++)
    {
        //while there is not one node in the bucket
        while (table[i] != NULL)
        {
            //set a temporary pointer - so when we free the memory
            node *tmp = table[i]->next_min;
            if (table[i]->next_max != NULL)
            {
                //free the memory here
                free(table[i]->next_max);
            }
            //and free the memory her
            free(table[i]);
            //we don't lose the thread to the other nodes in the linked array
            table[i] = tmp;
            //after freeing, connect (now the shorter array) it back to the bucket
        }
    }
    return true;
}
