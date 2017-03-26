/* k&r 1-23 

make a program that removes comments

so far I'm pretty sure this works for single-line comments, but haven't checked for multi-line comments.
*/

#include <stdio.h>

int main(void){

	char c;
	while((c = getchar()) != EOF){
	
		/* if we come across a backslash, check if the next char is an asterisk
			then we'll know we're in a comment.
		*/
		
		if(c == '/'){
			/* if the char after the backslash if an asterisk */
			if((c = getchar()) == '*'){
				/* keep getting new chars until we get to another asterisk */
				while((c = getchar()) != '*'){
					continue;
				}
				/* at this point, the asterisk for the end-comment part should be found */
				c = getchar(); /* get to the end-backslash */
				c = getchar();
			}
		}
		
		putchar(c);
	
	}

	return 0;
}

