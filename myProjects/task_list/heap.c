/*
	trying to implement a priority queue (min heap)
	
	hashmaps will be put in the queue based on value
	key - a char* array (string) indicating a certain activity (i.e. "do homework")
	value - a number from 1-100, 1 = highest priority, 100 = lowest priority

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "heap.h"

/*
	creates a new hashmap with the given string and priority number
	priority must be either 1 - 100;
	
*/
HashMap *createNewHashMap(char *string, int priority){

	assert(priority >= 1 && priority <= 100);

	HashMap *newHash = calloc(1, sizeof(HashMap));
	
	if(newHash == NULL){
		fprintf(stderr, "hash map could not be created.\n");
		exit(1);
	}
	
	newHash->key = malloc(strlen(string) + 1);
	
	if(newHash->key == NULL){
		fprintf(stderr, "hash map could not be created.\n");
		exit(1);
	}
	
	strcpy(newHash->key, string);
	newHash->value = priority;
	
	return newHash;
}


/*
	initialize a new heap - returns a pointer to the new heap
*/
Heap *newHeap(void){

	Heap *newHeap = calloc(1, sizeof(Heap));
	newHeap->theHeap = calloc(100, sizeof(HashMap *)); /* array of hashmap pointers */
	newHeap->size = 0;
	
	return newHeap;
}

/* set up a min-heap for adding new tasks */
/* create heap here */
void init(Heap **a_heap){
	*a_heap = newHeap();
	fprintf(stdout, "initializing heap...\n");
}


/*
	swap hashmaps in a heap
*/
void swap(HashMap **heap, int index1, int index2){
	HashMap *temp = heap[index1];
	heap[index1] = heap[index2];
	heap[index2] = temp;
}


/*
	adds a new hash map to the heap BASED ON VALUE
	larger value goes towards the bottom (end of array)
*/
void addToHeap(Heap *aHeap, HashMap *aHashMap){
	
	if(aHeap->size == 100){
		fprintf(stderr, "heap has reached maxed size! please remove the smallest element first before adding.\n");
		return;
	}
	
	/* access the heap */
	HashMap **heapPointer = aHeap->theHeap;
	heapPointer[aHeap->size] = aHashMap;
	
	/* 
		bubble-up procedure for newly added hashmap as needed. 
		important formulas:
		
		parent index: floor((i-1) / 2)
		left child index: 2i + 1
		right child index: 2i + 2
		
		check if parent of latest node is smaller than latest node
		keep doing that process if not
	*/
	
	int curIndex = aHeap->size;
	int parentIndex = (aHeap->size - 1) / 2;
	
	while(heapPointer[parentIndex]->value > heapPointer[curIndex]->value){
	
		swap(heapPointer, parentIndex, curIndex);
		
		/* update curIndex and parentIndex */
		curIndex = parentIndex;
		parentIndex = (curIndex-1) / 2;
	
	}
	
	/* increment size for the next hash map */
	(aHeap->size)++;
}

/*
	gets the key from the smallest value hash map from heap.
	doesn't change the heap.
*/
char *getSmallest(Heap *aHeap){
	
	if(aHeap->size == 0){
		return NULL;
	}
	
	return aHeap->theHeap[0]->key;
}

/*
	removes the smallest hashmap from the heap (i.e. heap[0])
*/
void removeSmallest(Heap *aHeap){
	
	if(aHeap->size == 0){
		return;
	}
	
	/* remove the smallest - free memory from first hashmap in heap */
	free((aHeap->theHeap)[0]->key);
	free((aHeap->theHeap)[0]);

	/* reassign 0 index to be the last hashmap in the heap */
	(aHeap->theHeap)[0] = (aHeap->theHeap)[aHeap->size - 1];
	(aHeap->theHeap)[aHeap->size - 1] = NULL;
	
	(aHeap->size)--;
	
	/* then bubble-down so the hashmap at index 0 will go to the right place*/ 
	int i;
	
	/* check to see if at least the left child exists */
	for(i = 0; ((2*i)+1) < aHeap->size; i++){
		HashMap *smallestChild;
		int smallestChildIndex = 2*i + 1;
		
		/* then check to see if the right child exists (it might not) */
		if((2*i)+2 < aHeap->size){
			/* if the index of the right child is still in range, compare it! */
			if((aHeap->theHeap)[i*2 + 1]->value > (aHeap->theHeap)[i*2 + 2]->value){
				smallestChild = (aHeap->theHeap)[2*i + 2];
				smallestChildIndex = 2*i + 2;
			}else{
				smallestChild = (aHeap->theHeap)[2*i + 1];
			}
		}else{
			smallestChild = (aHeap->theHeap)[2*i + 1];
		}
		
		if((aHeap->theHeap)[i]->value > smallestChild->value){
			swap(aHeap->theHeap, i, smallestChildIndex);
		} 
	}

}

void freeHeap(Heap *h){
	
	int i;
	for(i = 0; i < h->size; i++){
		free((h->theHeap)[i]->key);
		free((h->theHeap)[i]);
	}
	free(h->theHeap);
	free(h);
}

void printHeap(Heap *h){
	
	int i = 0;
	for(i = 0; i < h->size; i++){
		printf("to do: %s, priority number: %d\n", (h->theHeap)[i]->key, (h->theHeap)[i]->value);
	}
}


int main(void){
	
	Heap *heap1 = newHeap();
	
	HashMap *hm1 = createNewHashMap("do homework", 3);
	HashMap *hm2 = createNewHashMap("eat food", 6);
	HashMap *hm3 = createNewHashMap("go to sleep", 2);
	HashMap *hm4 = createNewHashMap("play with cats", 7);
	HashMap *hm5 = createNewHashMap("stare into space", 8);
	HashMap *hm6 = createNewHashMap("make music", 1);
	//HashMap *hm7 = createNewHashMap("make music again", 4);
	
	addToHeap(heap1, hm1);
	addToHeap(heap1, hm2);
	addToHeap(heap1, hm3);
	addToHeap(heap1, hm4);
	addToHeap(heap1, hm5);
	addToHeap(heap1, hm6);
	//addToHeap(heap1, hm7);
	
	printHeap(heap1);
	
	printf("the next task is: %s\n", getSmallest(heap1));
	removeSmallest(heap1);
	printf("the next task is: %s\n", getSmallest(heap1));
	removeSmallest(heap1);
	printf("the next task is: %s\n", getSmallest(heap1));
	removeSmallest(heap1);
	printf("the next task is: %s\n", getSmallest(heap1));
	removeSmallest(heap1);
	printf("the next task is: %s\n", getSmallest(heap1));
	removeSmallest(heap1);
	printf("the next task is: %s\n", getSmallest(heap1));
	removeSmallest(heap1);
	//printf("the next task is: %s\n", getSmallest(heap1));
	//removeSmallest(heap1);
	
	//printHeap(heap1);
	//printf("the size of the heap is now: %d\n", heap1->size);
	
	freeHeap(heap1);
	
	//print_memory_leaks();
	
	return 0;
}






