/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "dictionary.h"
int const HASHTABLE_SIZE = 524309;// Nearest prime to 524288; //2**19

int hash_it(char* needs_hashing);

typedef struct node
{
    char word[LENGTH + 1];
    struct node* next;
}
node;

node* hashtable[HASHTABLE_SIZE] = {NULL};
unsigned long words = 0; 

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    char* tempWord = malloc(strlen(word));
    for (int i = 0; word[i]; i++) {
        tempWord[i] = tolower(word[i]);
    }
    tempWord[strlen(word)] = '\0';
    int position = hash_it(tempWord);
    node* finder = hashtable[position];
    if (finder) {
        node* cursor = finder;
        while (cursor->next != NULL) {
            if (strcmp(cursor->word, tempWord) == 0) {
                free(tempWord);
                return true;
            }
            cursor = cursor->next;
        }
        if (strcmp(cursor->word, tempWord) == 0) {
            free(tempWord);
            return true;
        }
    }
    free(tempWord);
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // open the input dictionary file
    FILE* fp = fopen(dictionary, "r");
    char buffer[LENGTH + 2];
    while (fgets(buffer, sizeof(buffer), fp)) {
        buffer[strlen(buffer) - 1] = '\0';
        
    	node* temp = malloc(sizeof(node));
    	strncpy(temp->word, buffer, LENGTH + 1);
    	temp->next = NULL;

    	int index = hash_it(buffer);

    	if (hashtable[index] == NULL) {
    		hashtable[index] = temp;
    	} else {
    		node* cursor = hashtable[index];
            temp->next = cursor;
            hashtable[index] = temp;
    	}
        words++;
    }
    fclose(fp);
    return true;
}


/**
 * Almost used this hash-function, found here: https://www.reddit.com/r/cs50/comments/1x6vc8/pset6_trie_vs_hashtable/cf9nlkn
 * Actually used DJB2 sourced from: http://www.cse.yorku.ca/~oz/hash.html
 */
 
int hash_it(char* needs_hashing)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *needs_hashing++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash % HASHTABLE_SIZE;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return words;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    node* cursor = NULL;
    node* temp = NULL;
    for (int i = 0; i < HASHTABLE_SIZE; i++) {
         cursor = hashtable[i];
         while (cursor != NULL) {
             temp = cursor;
             cursor = cursor->next;
             free(temp);
         }
         hashtable[i] = NULL;
    }
    return true;
    //Valgrind progress
    //15,103,210->15,016,624->8,013,096->0
}

