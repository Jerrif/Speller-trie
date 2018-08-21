#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct _trie
{
    struct _trie* paths[27];
    bool is_word;
} trie;

unsigned int get_index(char raw_letter);
void add_word(trie* paths, const char* word);
bool check_word(trie* head, const char* word);
unsigned long get_size(trie* head);
void free_trie(trie* head);
/* trie* add(trie* head, unsigned int pos, bool is_word); */
