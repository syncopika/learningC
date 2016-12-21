/* this program takes command-line arguments */

#include <stdio.h>
#include <stdlib.h>

/*defining a macro to get the length of an array
    x = an int array
    sizeof(x) = the size, in BYTES, of the array
    sizeof(x)[0] = size of type int, which is 4 bytes
    note this only works in the same scope where the
    array is initialized
*/
#define LENGTH(x) (sizeof(x) / sizeof((x)[0]))

/* don't accept an array of numbers with more than 32 numbers!!! this means argc <= 33! */
#define MAX_LENGTH 33

/* this is not needed since the sorting can be done within the main method */
void sorter(int array[], int length){
    /*the macro LENGTH will not work here since the array is passed as a parameter
      the parameter is treated as a pointer, so sizeof gets the pointer's size

      you can get the length of the array before you pass it, and pass that length as
      another parameter to the function
    */
    int i;
    for(i = 0; i < length - 1; i++){
        int minIndex = i;
        int j;
        for(j = i+1; j < length; j++){
            if(array[j] < array[minIndex]){
                minIndex = j;
            }
        }
        /* swap the elements after finding the smallest element to the right */
        int temp = array[i];
        array[i] = array[minIndex];
        array[minIndex] = temp;
    }
}


int main(int argc, char *argv[])
{
	int i;
	
	if(argc > MAX_LENGTH){
		fprintf(stderr, "Too many numbers!! \n");
	}else if(argc == 1){
		fprintf(stderr, "There are no numbers to sort! \n");
	}else{
		/* set i to 1 to ignore argv[0], which is just the program's name */
		/* argc is the number of elements in argv */
		
		/* first change all elements in argv to be ints - this didn't work out so well when sorting negative numbers 
		for(i = 1; i < argc; i++){
			argv[i] = atoi(argv[i]); atoi converts string to integer 
		}
		*/
		
		/* selection sort */
		for(i = 1; i < argc-1; i++){
			int minIndex = i;
			int j;
			for(j = i+1; j < argc; j++){
				if(atoi(argv[j]) < atoi(argv[minIndex])){  /* atoi converts string to integer */
					minIndex = j;
				}
			}
			/* swap the elements after finding the smallest element to the right */
			char *temp = argv[i]; /* use a pointer to record the element to swap */
			argv[i] = argv[minIndex];
			argv[minIndex] = temp;
		}

		/* print out sorted numbers */
		for(i = 1; i < argc; i++){
			printf("element %d: %d \n", i, atoi(argv[i]));
		}
		
	}	
    return 0;
}
