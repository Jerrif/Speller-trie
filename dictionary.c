// Implements a dictionary's functionality

#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "dictionary.h"
#include "trie.h"

trie* table;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    return check_word(table, word);
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE* dic = fopen(dictionary, "r");
    if(!dic)
    {
        printf("Could not open dictionary.\n");
        return false;
    }

    char raw_word[LENGTH + 1];

    table = calloc(1, sizeof(trie));
    /* table = malloc(sizeof(trie*)); */

    while(fgets(raw_word, LENGTH + 1, dic))
    {
        raw_word[strcspn(raw_word, "\n")] = 0; // Strip newline char off the word
        if(raw_word[0] != 0)
        {
            add_word(table, raw_word);
        }
    }

    fclose(dic);

    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    unsigned long w = get_size(table);

    return w;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    free_trie(table);

    return true;
}
