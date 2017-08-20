// run-length encoding
// a compression algorithm

#include <stdio.h>
#include <stdlib.h>

/* prototype */
char *compress(char *string);
int len(char *string);

/* compress definition */
char *compress(char *string){
    /* printf("the string is: %s\n", string); */
	int i;
	char currChar = '\0';
	int count = 0;
	int currIndex = 0;
	char *compressedString = calloc(1, 1); 
	
	/* need to read the null-term to count the last char */
	for(i = 0; i <= len(string); i++){
		/* for first char in string */
		if(i == 0){
			currChar = string[i];
			count++;
		}else{
			if(string[i] != currChar){
				compressedString = realloc(compressedString, currIndex + 3);
				sprintf(compressedString, "%s%c%d", compressedString, currChar, count);
				/* printf("compressed str: %s\n", compressedString); */
				currIndex += 2;
				currChar = string[i]; 	/* reset currChar */
				count = 1; 				/* reset count */
			}else{
				count++;
			}
		}
	}

	/* add null term */
	compressedString[currIndex] = '\0';
	
	return compressedString;
}

/* define length function */
int len(char *string){
	int count = 0;
	while(*string != '\0'){
		count++;
		string++;
	}
	return count;
}

/*
	accept as an argument the string to compress 
*/
int main(int argc, char **argv){

	char *str = argv[1];

	char *ans = compress(str);
	
	printf("the compressed str is: %s\n", ans);
	free(ans);
	
	return 0;
}