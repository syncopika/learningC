/*
	priority queue (min heap)
	
	hashmaps will be put in the queue based on value
	key - a char* array (string) indicating a certain activity (i.e. "do homework")
	value - a number from 1-100, 1 = highest priority, 100 = lowest priority
	
	queue only has two methods - add and getSmallest

*/


#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

/*
	creates a new hashmap with the given string and priority number
	priority must be either 1 - 100;
	
*/
HashMap *createNewHashMap(char *string, int priority){

	HashMap *newHash = calloc(1, sizeof(HashMap));
	
	newHash->key = string;
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
	newHeap->currIndex = 0;
	
	return newHeap;
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
	heapPointer[aHeap->currIndex] = aHashMap;
	
	/* 
		bubble-up procedure for newly added hashmap as needed. 
		important formulas:
		
		parent index: (i-1) / 2
		left child index: 2i + 1
		right child index: 2i + 2
		
		check if parent of latest node is smaller than latest node
		keep doing that process if not
	*/
	
	int curIndex = aHeap->currIndex;
	int parentIndex = (aHeap->currIndex - 1) / 2;
	
	while(heapPointer[parentIndex]->value > heapPointer[curIndex]->value){
	
		swap(heapPointer, parentIndex, curIndex);
		
		/* update curIndex and parentIndex */
		curIndex = parentIndex;
		parentIndex = (curIndex-1) / 2;
	
	}
	
	/* increment size and currIndex for the next hash map */
	aHeap->size++;
	aHeap->currIndex++;
}

/*
	gets the key from the smallest value hash map from heap.
	doesn't change the heap.
*/
void getSmallest(Heap *aHeap){
	printf("The current task is: %s\n", aHeap->theHeap[0]->key);
}

/*
	removes the smallest hashmap from the heap (i.e. heap[0])
*/
void removeSmallest(Heap *aHeap){
	/* remove the smallest - free memory from first hashmap in heap */
	free((aHeap->theHeap)[0]);

	/* reassign 0 index to be the last hashmap in the heap */
	(aHeap->theHeap)[0] = (aHeap->theHeap)[aHeap->currIndex - 1];
	(aHeap->theHeap)[aHeap->currIndex - 1] = NULL;
	
	/* then bubble-down so the hashmap at index 0 will go to the right place*/ 
	int i;
	for(i = 0; ((2*i)+2) < aHeap->currIndex - 1; i++){
		HashMap *smallestChild = NULL;
		int smallestChildIndex = 2*i + 1;
		
		if((aHeap->theHeap)[i*2 + 1]->value > (aHeap->theHeap)[i*2 + 2]->value){
			smallestChild = (aHeap->theHeap)[2*i + 2];
			smallestChildIndex = 2*i + 2;
		}else{
			smallestChild = (aHeap->theHeap)[2*i + 1];
			smallestChildIndex = 2*i + 1;
		}
		
		if((aHeap->theHeap)[i]->value > smallestChild->value){
			swap(aHeap->theHeap, i, smallestChildIndex);
		} 
	}
	/* decrease currIndex */
	(aHeap->currIndex)--;
	/* decrease size */
	(aHeap->size)--;
}


void freeHeap(Heap *h){
	
	int i;
	for(i = 0; i < h->currIndex; i++){
		free((h->theHeap)[i]);
	}
	free(h->theHeap);
	free(h);
}

void printHeap(Heap *h){
	
	int i = 0;
	for(i = 0; i < h->currIndex; i++){
		printf("to do: %s, priority number: %d\n", (h->theHeap)[i]->key, (h->theHeap)[i]->value);
	}
	
}





