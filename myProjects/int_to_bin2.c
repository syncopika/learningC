/* integer to binary converter (up to 32 places)*/
#include <stdio.h>
#include <stdlib.h>
#define BYTES 33

/* prototypes */
char *intToBinary(int num);
void reverse(char *string);

/* converting function */
char *intToBinary(int num)
{
	int rem = num % 2;
	int rest = num / 2;
	int marker = 0; /* this determines what index each bit should go */
	
	/* allocate some memory for the string 
	   32 should be enough, +1 for the '\0' at the end
	*/
	char *string;
	string = malloc(BYTES);
	
	if(string == NULL){
		fprintf(stderr, "error");
		return NULL;
	}
	
	/* initialize everything to 0 first */
	int i;
	for(i = 0; i < BYTES; i++){
		string[i] = 0 + '0';
	}
	
	string[marker++] = rem + '0'; /* add '0' to make rem a char */
	
	while(rest != 0){
		rem = rest % 2;
		string[marker++] = rem + '0';
		rest = rest / 2;
	}
	
	/* add the '\0' to the end of the string */
	string[BYTES - 1] = '\0';

	return string;

}

void reverse(char *string)
{
	int i;
	char temp;

	for(i = 0; i < (BYTES-2)/2; i++){
		temp = string[i];
		string[i] = string[BYTES - 2 - i];
		string[BYTES - 2 - i] = temp;
	}
}

int main(void)
{
	char *str;
	int n;
	
	printf("Please enter a number.\n");
	scanf("%d", &n);
	
	str = intToBinary(n);
	reverse(str);

	printf("the binary representation of %d is:\n%s \n", n, str);
	
	
	free(str); /* free allocated memory */
	return 0;
}




