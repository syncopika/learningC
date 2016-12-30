/* k&r 1-19 */
#include <stdio.h>

/* function prototype */
int getLength(char *s);
void reverse(char s[]);

int getLength(char *s){
	
	int length = 0;
	
	while(s[length] != '\0'){
		++length;
	}
	
	return length;
}


void reverse(char s[])
{
	int i;
	int j = getLength(s) - 1; /* decrement by 1 to account for the 0th index */
	
	for(i = 0; i < j; i++, j--){
		
		char temp = s[i];
		s[i] = s[j];
		s[j] = temp;
	}

}

int main(void){

	char c;
	char strArr[50] = {'\0'}; /* every index is set to '\0' initially */
	int marker = 0;
	
	while((c = getchar()) != '\n'){
		/* keep accepting characters */
		strArr[marker++] = c;
	}

	reverse(strArr);
	
	printf("%s\n", strArr);
	/*
	int i = 0;
	for(i = 0; i < marker; i++){
		printf("%c", strArr[i]);
	}*/

	return 0;

}
