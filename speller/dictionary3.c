// Implements a dictionary's functionality
#include <cs50.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 626;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int index = hash(word);
    node* cursor = table[index];

    for (node* tmp = cursor; tmp != NULL; tmp = tmp->next)
    {
        if (strcasecmp(tmp->word, word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    //stored in mario-more folder in jamie.c
    int s = strlen(word);
    int hashvalue = toupper(word[0]);
    int hashvalue2 = toupper(word[s-1]);
    int a = 1;
    int b = 1;
    int * aptr = &a;
    int * bptr = &b;

    if ((hashvalue < 123) && (hashvalue > 64))
    {
        *aptr = hashvalue - 'A';
    }

    if ((hashvalue2 < 123) && (hashvalue2 > 64))
    {
        *bptr = hashvalue2 - 'A';
    }
    //printf("%i\n",a);
    //printf("%i\n",b);
    int c = a * b;
    //printf("%i\n",c);

    return c;
}

int wordcount = 0;

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        fclose(file);
        return false;
    }

    char dictionaryword[LENGTH +1];

    while (fscanf(file, "%s", dictionaryword) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }

        //copy word from file to n->word
        //strcpy(destination, source);
        strcpy(n->word, dictionaryword);
        n->next = NULL;

        //add to hash table array using hash function
        int h = hash(n->word);

        node* head = table[h];
        // h must be 0 for a, 1 for b and so on
        if (head == NULL)
        {
            table[h] = n;
            wordcount++;

        }
        else
        {
            n->next = table[h];
            table[h] = n;
            wordcount++;
        }
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return wordcount;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    //free memory and return true if done
    for (int i = 0; i < N; i++)
    {
        node* cursor = table[i];
        while (cursor != NULL)
        {
            node* tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }

    return true;
}
