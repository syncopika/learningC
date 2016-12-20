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

/* C is pass-by-value! so I can pass a function an array, modify it, and the array will stay modified. */
/* this function will sort an array of numbers. I will use selection sort. */

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

int main()
{
    int test[] = {1, 7, 10, 23, -6, 8};
    int length = LENGTH(test);

    printf("The length of the array is %d \n", length);

    sorter(test, length);

    int i;
    for(i = 0; i < length; i++){
        printf("%d \n", test[i]);
    }
    return 0;
}
