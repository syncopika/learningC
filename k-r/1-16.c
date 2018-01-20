/* k&r 1-16 */
#include <stdio.h>
/* 50 is arbitrary */
#define MAX_STRING_LENGTH 50 

int main(void){

	int currentMaxLength = 0;
	
	char currentMaxString[MAX_STRING_LENGTH]; /* longest string length capped at 50 */
	char currentString[MAX_STRING_LENGTH]; /* this holds the current string being looked at */
	
	int currLength = 0; /* this keeps track of how long the current string being evaluated is */
	int currStringMarker = 0;
	char c; /* this var looks at the current char when reading string */
	
	while((c = getchar()) != EOF){
	
		if(c == '\n'){
			if(currLength > currentMaxLength){
				/* update longest length */
				currentMaxLength = currLength;
				int i;
				/* update max string */
				for(i = 0; i < currLength; i++){
					currentMaxString[i] = currentString[i];
				}
			}
			currLength = 0;
			currStringMarker = 0; /* reset marker when reach new line */
			/* clear current string */
			int j;
			for(j = 0; j < MAX_STRING_LENGTH; j++){
				currentString[j] = 0;
			}
		}else{
			++currLength;
			/* update longest string array */
			currentString[currStringMarker++] = c;
		}
	}
	
	int i;
	for(i = 0; i < currentMaxLength; i++){
		printf("%c", currentMaxString[i]);
	}
	printf("\n");
	printf("the longest string has %d characters.\n", currentMaxLength);

	return 0;
}
