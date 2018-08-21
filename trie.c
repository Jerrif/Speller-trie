#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "dictionary.h"
#include "trie.h"

unsigned long w_count = 0;

void free_trie(trie* head)
{
    trie* cursor = head;

    for(unsigned short i=0; i<27; i++)
    {
        if(cursor->paths[i] != NULL)
        {
            free_trie(cursor->paths[i]);
        }
    }

    free(cursor);

}

unsigned long get_size(trie* head)
{
    trie* cursor = head;

    if(cursor->is_word == true)
    {
        w_count++;
    }

    for(unsigned short i=0; i<27; i++)
    {
        if(cursor->paths[i] != NULL)
        {
            get_size(cursor->paths[i]);
        }
    }

    return w_count;
}

bool check_word(trie* head, const char* word)
{
    trie* cursor = head;
    unsigned int letter = 0, i = 0;
    char l;

    while(word[i]!=0)
    {
        l = tolower(word[i]);
        letter = get_index(l);

        if(cursor->paths[letter] == NULL)
        {
            return false;
        }
        else
        {
            cursor = cursor->paths[letter];
        }

        i++;
    }

    return cursor->is_word;
}

unsigned int get_index(char raw_letter)
{
    if(raw_letter != '\'')
    {
        raw_letter = raw_letter - 97;
    }
    else
    {
        raw_letter = 26;
    }

    return raw_letter;
}

void add_word(trie* head, const char* word)
{
    /* trie* new_node = malloc(sizeof(trie*)); */
    trie* cursor = head;

    unsigned int i = 0;
    unsigned int letter = 0;
    /* unsigned int n = 0, o = 0; */
    /* printf("Word: %s\n", word); */

    while(word[i]!=0)
    {
        letter = get_index(word[i]);

        /* printf("Letter to check: %c\n", letter); */
        /* printf("cursor->paths[%i]: %i\n", index, cursor->paths[index]); */

        if(cursor->paths[letter] == NULL)
        {
            /* printf("No node: %c found. Mallocing.\n", letter); */

            /* new_path[n] = letter; */
            /* n++; */

            cursor->paths[letter] = calloc(1, sizeof(trie));

            if(cursor->paths[letter] == NULL)
            {
                printf("Failed to allocate memory for new node\n");
                exit(0);
            }

            cursor = cursor->paths[letter];
        }
        else
        {
            /* printf("Node: %c found. Index: %i\n", letter, index); */
            /* old_path[o] = letter; */
            /* o++; */
            cursor = cursor->paths[letter];
        }
        i++;
    }

    /* new_path[n] = 0; */
    /* old_path[o] = 0; */

    /* if(o > 0) */
    /*     printf("Old Path: %s\n", old_path); */
    /* printf("New Path: %s\n", new_path); */

    cursor->is_word = true;

}
