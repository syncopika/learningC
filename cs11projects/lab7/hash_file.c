/*
 * CS 11, C Track, lab 7
 *
 * FILE: hash_table.c
 *
 *       Implementation of the hash table functionality.
 *
 */

/*
 * Include the declaration of the hash table data structures
 * and the function prototypes.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"
#include "memcheck.h"


/*** Hash function. ***/

int hash(char *s)
{
	int sum = 0;
	int i = 0;
	while(s[i] != '\0'){
		sum += (int)s[i];
		i++;
	}
	return sum % NSLOTS;
}


/*** Linked list utilities. ***/

/* Create a single node. */
node *create_node(char *key, int value)
{
	node *newNode = malloc(sizeof(node));
	
	newNode->key = key;
	newNode->value = value;
	newNode->next = NULL;
	
	return newNode;
}


/* Free all the nodes of a linked list. */
void free_list(node *list)
{
	node *n;
	while(list != NULL){
		n = list;
		list = n->next;
		free(n->key);
		free(n);
	}
}


/*** Hash table utilities. ***/

/* Create a new hash table. */
hash_table *create_hash_table()
{
	hash_table *newHash = malloc(sizeof(hash_table));
	
	/* make slots a length of 128, each index the size of a node */
	newHash->slot = calloc(NSLOTS, sizeof(node));
	
	return newHash;
}


/* Free a hash table. */
void free_hash_table(hash_table *ht)
{
	/* free the linked lists inside the table first - we know that the length of slot in ht is 128*/
	int i;
	node *n;
	for(i = 0; i < NSLOTS; i++){
		n = (ht->slot)[i]; /* get a linked list in slot */
		free_list(n);
	}
	
	/*free ht's slot */
	free(ht->slot);
	
	/* then free the table struct */
	free(ht);
}


/*
 * Look for a key in the hash table.  Return 0 if not found.
 * If it is found return the associated value.
 */
int get_value(hash_table *ht, char *key)
{
	/* find which bucket key should be in */
	int bucket = hash(key);
	node *n = (ht->slot)[bucket];
	
	while(n != NULL){
		if(strcmp((n->key), key) == 0){
			return n->value;
		}
		n = n->next;
	}
	return 0;
}


/*
 * Set the value stored at a key.  If the key is not in the table,
 * create a new node and set the value to 'value'.  Note that this
 * function alters the hash table that was passed to it.
 */
void set_value(hash_table *ht, char *key, int value)
{
	/* find which bucket to check */
	int bucket = hash(key);
	node *n = (ht->slot)[bucket];
	
	if(n == NULL){
		n = create_node(key, value); /* allocating memory here */
		(ht->slot)[bucket] = n;
		return;
	}else{
		
		/* case for single node with a match */
		if(n->next == NULL && strcmp((n->key), key) == 0){
			n->value = value;
			free(key);
			return;
		}
		
		/* look through list. */
		while(n->next != NULL){
			if(strcmp((n->key), key) == 0){
				n->value = value;
				/* since the key is already present, this one that's passed in can go away */
				free(key);
				return;
			}
			n = n->next;
		}
		
		/* key was not found - create a new node and add it to list */
		n->next = create_node(key, value);
		return;
	}
}


/* Print out the contents of the hash table as key/value pairs. */
void print_hash_table(hash_table *ht)
{
	int i;
	node *n;
	for(i = 0; i < NSLOTS; i++){
		n = (ht->slot)[i];
		while(n != NULL){
			printf("key: %s, value: %d, bucket: %d\n", n->key, n->value, i);
			n = n->next;
		}
	}
}

