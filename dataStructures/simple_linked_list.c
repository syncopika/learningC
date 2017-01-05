/* 
   simple linked list 2.
   for this one I have a list struct that will represent one linked list.
   then this list struct will have the node struct as a member.
   I think this should more closely resemble the way I've done it in Java
   and the object-oriented approach in general?
*/

#include <stdio.h>
#include <stdlib.h>

/* 
	set up types 
*/
typedef struct node
{
	int value;
	struct node *next;
} Node;

typedef struct linkedlist
{
	/* pointers to head and tail */
	Node *head;
	Node *tail;
	int length;

} LList;


/* 
	function prototypes 
*/
void initializeList(LList *list);
void addToHead(LList **list, int n);
void addToTail(LList **list, int n);
int getLength(LList *list);
int getHead(LList *list);
int getTail(LList *list);
void printList(LList *list);
void freeList(LList **list);
void removeNode(LList *list, int n);

/* 
	functions 
*/
void initializeList(LList *list){

	list->head = NULL;
	list->tail = NULL;
	list->length = 0;

}

void addToHead(LList **list, int n){

	/* allocate some memory for new node */
	Node *newNode = malloc(sizeof(Node));
	
	/* check it */
	if(newNode == NULL){
		fprintf(stderr, "error with malloc.\n");
		exit(1);
	}
	
	/* set up node */
	newNode->value = n;
	
	/* move the old head (only if there's a node there already) as the next for this node's next */
	if((*list)->head == NULL){
		/* initialize newNode next to NULL if it's the first node */
		(newNode->next) = NULL; 
		/* and make the tail pointer point to new node */
		(*list)->tail = newNode;
	}else{
		(newNode->next) = (*list)->head;
	}
	
	/* reassign list's head to this new node */
	(*list)->head = newNode;
	
	/* increment length */
	((*list)->length) = ((*list)->length) + 1;
}

void addToTail(LList **list, int n){
	
	Node *newNode = malloc(sizeof(Node));
	
	if(newNode == NULL){
		fprintf(stderr, "error with malloc!\n");
		exit(1);
	}
	
	newNode->value = n;
	
	if((*list)->tail == NULL){
		(*list)->head = newNode;
		(*list)->tail = newNode;
	}else{
		((*list)->tail)->next = newNode;
		(*list)->tail = newNode;
	}
	
	newNode->next = NULL;
	((*list)->length) = ((*list)->length) + 1;
}

/* removes only first occurrence of n */
void removeNode(LList *list, int n){
	
	Node *prev = NULL;
	Node *curr = list->head;
	
	if(curr != NULL){
		
		for(;curr != NULL; prev = curr, curr = curr->next){
			if(prev != NULL && (curr->value == n)){
				
				/* this is the condition to go to if the node to remove is at the tail */
				if(list->tail == curr){
					/* make prev the new tail */
					prev->next = NULL;
					list->tail = prev;
					free(curr);
				}else{
					prev->next = curr->next;	
					/* free the curr node */
					free(curr);
				}	
				
				list->length = (list->length) - 1;
				
				/* break out of loop */
				break;
			}else if(prev == NULL && (curr->value == n)){
				
				/* if this is the first node is the one to remove 
				   and only if there is one node!
				*/
				if(list->length == 1){
					free(curr);
					list->head = NULL;
					list->tail = NULL;
				}else{
					/*	this condition is for when the list is > 1 and the current head
						is to be removed
					*/
					list->head = curr->next;
					free(curr);
				}
				list->length = (list->length) - 1;
				break;
			}
		}
	}
}


void printList(LList *list){

	Node *n;
	int i = 0;
	
	for(n = list->head; n != NULL; n = n->next){
		printf("node %d is: %d \n", i, n->value);
		i++;
	}
}

int getHead(LList *list){
	return (list->head)->value;
}

int getTail(LList *list){
	return (list->tail)->value;
}

/* still having some issues with getLength 
   sometimes it returns the correct value, and sometimes the mem address??
*/
int getLength(LList *list){
	return (list->length);
}

void freeList(LList **list){

	Node *n;
	
	while(((*list)->head) != NULL){
		n = (*list)->head;
		(*list)->head = n->next;
		free(n);
	}
}


int main(void){
	
	/* initialize a new list */
	LList *newList = malloc(sizeof(newList));

	initializeList(newList);
	
	addToHead(&newList, 10);
	addToHead(&newList, 11);
	addToHead(&newList, 12);
	addToHead(&newList, 13);
	addToHead(&newList, 14);
	addToHead(&newList, 15);
	addToTail(&newList, 20);
	addToTail(&newList, 25);
	
	printList(newList);
	printf("the head is: %d\n", getHead(newList));
	printf("the tail is: %d\n", getTail(newList));
	printf("The length of the list is: %d\n", getLength(newList));
	
	printf("\n");
	
	/* remove tail */
	removeNode(newList, 25);
	printList(newList);
	printf("the head is now: %d\n", getHead(newList));
	printf("the tail is now: %d\n", getTail(newList));
	printf("The length of the list is now: %d\n", getLength(newList));
	
	freeList(&newList);

	return 0;

}

