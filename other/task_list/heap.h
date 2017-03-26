/* heap.c header file */

/* type definitions */
typedef struct hash_map{

	char *key;
	int value;

} HashMap;


typedef struct min_heap{

	/* make an array of hashmap pointers 
	
	   for now, it should be a size of 100 indices
	   only one slot for one priority number, no duplicates
	   remember: heap is an array of hashmap pointers 
	   
	*/
	HashMap **theHeap; 
	int size;

} Heap;


/* function prototypes */
void init(Heap **a_heap);
HashMap *createNewHashMap(char *string, int priority);
Heap *newHeap(void);
void swap(HashMap **heap, int index1, int index2);
void addToHeap(Heap *aHeap, HashMap *aHashMap);
char *getSmallest(Heap *aHeap);
void removeSmallest(Heap *aHeap);
void freeHeap(Heap *h);
void printHeap(Heap *h);
