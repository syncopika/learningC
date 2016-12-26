/* K&R 1-13 */

#include <stdio.h>
#define MAX_LENGTH 16


int main(void){
	
	int arr[MAX_LENGTH];
	int i;
	
	for(i = 0; i < MAX_LENGTH; i++){
		arr[i] = 0;
	}
	
	char c;
	int length = 0;
	while((c = getchar()) != EOF){
		
		if(c != ' '){
			length = 0;
			while(c != ' ' && c != '\n'){ /* terminate inner loop when new line */
				++length;
				c = getchar();
			}
			/* at this point we've run into a blank! 
				index in array corresponds to word length
			*/
			++arr[length-1];
		}
	}
	
	/* after collecting words, print histogram */
	for(int i = 0; i < MAX_LENGTH; i++){
		int j;
		printf("word length %d: ", i+1); /* add 1 to offset the 0 index */
		for(int j = 0; j < arr[i]; j++){
			printf("*");
		}
		printf("\n");
	}

	return 0;

}
