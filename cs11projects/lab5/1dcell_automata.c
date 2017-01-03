/* lab 5 - cs11 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* defined what should represent full or empty cells */
/* when adding '0' to make a character, it's the same as adding 48 in decimal. 48 + -6 = 42, which is the asterisk char. */ 
#define FULL (-6 + '0')
#define EMPTY (-2 + '0')


/* function prototypes */
void print(char *array); /* print a char array */
void update(char *arr1, char *arr2, int length); /* take contents of arr2 and update arr1 */
void setArray(char *array, int length); /* set up array with 0s and 1s */
int changeCell(char cell, char left, char right);


/* set up array */
void setArray(char *array, int length){
	
	array[0] = EMPTY;
	array[length - 1] = '\0'; /* null terminate */
	
	/* random number generator */
	srand(time(0));
	
	int i;
	int random;
	for(i = 1; i < length-1; i++){
		
		/* randomly set indices to either 0 or 1 */
		random = (rand()%10) + 1; /* pick a number from 1 to 10 */
		if(random > 5){
			array[i] = FULL;
		}else{
			array[i] = EMPTY;
		}
	}
}


/* determine if current cell should be changed */
int changeCell(char cell, char left, char right)
{	
	int neighborsFull = (left == FULL && right == FULL);
	int oneNeighborFull = (left == FULL || right == FULL);
	
	if(cell == EMPTY && neighborsFull){
		return 0;
	}else if(cell == EMPTY && oneNeighborFull){
		return 1; /* this is the condition to change currernt cell */
	}else{
		return 0;
	}
}

/* update array */
void update(char *arr1, char *arr2, int length)
{
	int i;
	
	/* figure out what next generation will look like. put it in arr2 */
	for(i = 1; i < length-1; i++){
		if(changeCell(arr1[i], arr1[i-1], arr1[i+1]) == 1){
			arr2[i] = FULL;
		}else{
			arr2[i] = EMPTY;
		}
	}
	
	/* then take all the entries in arr2 and put them in arr1 */
	for(i = 0; i < length-1; i++){
		arr1[i] = arr2[i];
	}
}

/* print an array */
void print(char *array){
	printf("%s\n", array);
}


int main(int argc, char *argv[])
{
	/* argc includes the name of the program */
	if(argc < 3 || argc > 3){
		fprintf(stderr, "Needs 2 (two) arguments!!\n");
		exit(1);
	}
	
	int numberOfCells = atoi(argv[1]);
	int numberOfGenerations = atoi(argv[2]);

	/* initialize two arrays based on # of cells given */
	char *arr1 = calloc(numberOfCells, sizeof(char));
	
	if(arr1 == NULL){
		fprintf(stderr, "Memory allocation failed.\n");
		exit(1);
	}
	
	char *arr2 = calloc(numberOfCells, sizeof(char));
	
	if(arr2 == NULL){
		fprintf(stderr, "Memory allocation failed.\n");
		exit(1);
	}
	
	/* set arr1 to be random 0s and 1s */
	setArray(arr1, numberOfCells);
	
	/* initialize array 2's indices to 0 */
	int j;
	for(j = 0; j < numberOfCells; j++){
		arr2[j] = 0 + '0';
	}

	
	/* print it first */
	print(arr1);
	
	/* then keep generating generations until reached number of specified generations */
	int counter = 0;
	while(counter < numberOfGenerations){

		/* update arr1 */
		update(arr1, arr2, numberOfCells);
		
		/* print it */
		print(arr1);
		
		counter++;
	}

	/* done. free memory */
	free(arr1);
	free(arr2);
	
	return 0;

}
