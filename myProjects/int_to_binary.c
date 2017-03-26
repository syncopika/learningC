/* integer to binary converter (up to 32 places)*/
#include <stdio.h>
#include <stdlib.h>
#define BYTES 33
/* I think the first argument doesn't really matter? if I were using malloc, it'd be 1*33 as the arg I think 
   anyway, I want to allocate 33 bytes, but I want the initialization of all indices to be 0. 
*/
#define CALLOC 1 


/* prototypes */
char *intToBinary(int num);
void reverse(char *str, int length);

char *intToBinary(int num)
{
	int rem = num % 2;
	int rest = num / 2;
	int marker = 0; /* this determines what index each bit should go */
	
	/* allocate some memory for the string 
	   32 should be enough, +1 for the '\0' at the end
	*/
	char *string;
	string = calloc(CALLOC, BYTES);
	
	if(string == NULL){
		fprintf(stderr, "error");
		return NULL;
	}
	
	string[marker++] = rem;
	
	while(rest != 0){
		rem = rest % 2;
		string[marker++] = rem;
		rest = rest / 2;
	}
	
	/* add the '\0' to the end of the string */
	string[marker] = '\0';

	return string;

}

void reverse(char *str, int length){
	
	int i;
	char temp;
	
	for(i = 0; i < length/2; i++){
		temp = str[i];
		str[i] = str[length - 1 - i];
		str[length - 1 - i] = temp;
	}
	
}


int main(void)
{
	char *str;
	int n;
	
	printf("Please enter a number.\n");
	scanf("%d", &n);
	
	str = intToBinary(n);
	printf("binary representation of %d is: ", n);
	
	int i;
	int length = BYTES / sizeof(char);
	reverse(str, length);
	
	for(i = 0; i < length; i++){
		printf("%d", str[i]);
	}
	
	free(str); /* free allocated memory */
	return 0;
}
