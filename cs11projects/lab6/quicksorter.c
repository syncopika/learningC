/* 
	cs11 lab 6 
	implementing quicksort with a linked list
*/

#include <stdio.h>
#include <stdlib.h>
#include "memcheck.h"
#include "linked_list.h"


/* function prototype */
node *quicksort(node *n);

node *quicksort(node *n){

	if(n == NULL || n->next == NULL){
		return copy_list(n);
	}
	
	node *firstNode = malloc(sizeof(node));
	if(firstNode == NULL){
		fprintf(stderr, "error! with malloc.\n");
		exit(1);
	}
	
	firstNode->data = (n->data); /* copy first node data */
	firstNode->next = NULL; /* separate firstNode from rest of list */
	
	/* go through list after first node and separate them into diff lists accordingly */
	node *nextNode = n->next;
	
	node *lowerList = NULL;
	node *higherList = NULL;
	int counter1 = 0;
	int counter2 = 0;
	
	while(nextNode != NULL){
		if((nextNode->data) < (firstNode->data)){
			if(counter1 == 0){
				
				/* 
					this condition will fill in the first node of lowerList 
				*/
				lowerList = malloc(sizeof(node));
				if(lowerList == NULL){
					fprintf(stderr, "error with malloc!\n");
					exit(1);
				}
				lowerList->next = NULL;
				lowerList->data = (nextNode->data);
				++counter1;
				
			}else{
				lowerList = create_node(nextNode->data, lowerList);
			}
		}else if((nextNode->data) >= (firstNode->data)){
			if(counter2 == 0){
				
				higherList = malloc(sizeof(node));
				if(higherList == NULL){
					fprintf(stderr, "error with malloc!\n");
					exit(1);
				}
				higherList->next = NULL;
				higherList->data = (nextNode->data);
				++counter2;
				
			}else{
				higherList = create_node(nextNode->data, higherList);
			}
		}
		nextNode = (nextNode->next);
	}
	
	/* recursive call for each upper/lower list */
	node *sortedLeft = quicksort(lowerList);
	
	if(lowerList != NULL){
		free_list(lowerList);
	}
	
	node *sortedRight = quicksort(higherList);
	
	if(higherList != NULL){
		free_list(higherList);
	}
	
	node *newLeftHalf = append_lists(sortedLeft, firstNode);
	free_list(sortedLeft);
	free(firstNode);
	
	node *newList = append_lists(newLeftHalf, sortedRight);
	free_list(newLeftHalf);
	free_list(sortedRight);
	
	return newList;
}


int main(int argc, char **argv){

	if(argc == 1){
		fprintf(stderr, "Not enough arguments! Please enter like so: quicksorter 1 3 4 5 -10 ...\n");
		exit(1);
	}
	
	/* get all the numbers from the command line input and put them in a linked list */
	
	/* but first make a node to start */
	node *list = malloc(sizeof(node));
	list->data = atoi(argv[1]); 
	list->next = NULL;
	
	if(list == NULL){
		fprintf(stderr, "error with malloc.\n");
		exit(1);
	}
	
	int i;
	for(i = 2; i < argc; i++){
		list = create_node(atoi(argv[i]), list);
	}

	/* list is now assembled! do quicksort on it now */
	node *sortedList = quicksort(list);
	
	print_list(sortedList);

	/* free memory */
	free_list(list);
	free_list(sortedList);
	
	print_memory_leaks();
	
	return 0;
	
}
