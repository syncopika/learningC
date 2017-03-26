/* a simple cipher - can decode and encode */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* function prototypes */
int ROT13encode(int c); /* chars will be interpreted as ints */
int ROT13decode(int c);

int ROT13encode(int c){

	if(c >= 65 && c <= 90){
	
		/* check if in range for adding 13. if not, wraparound */
		if(c <= 77){
			return (c + 13);
		}else{
			int newChar = (13 - (90 % c)) + 64;
			return (newChar);
		}
		
	}else if(c >= 97 && c <= 122){
	
		if(c <= 109){
			return (c + 13);
		}else{
			int newChar = (13 - (122 % c)) + 96;
			return (newChar);
		}
	}
	/* if any symbols or non-alpha chars, just return it */
	return c;
}

int ROT13decode(int c){

	if(c >= 65 && c <= 90){
	
		if(c >= 78){
			return (c - 13);
		}else{
			int newChar = 91 - (13 - (c % 65));
			return (newChar);
		}

	}else if(c >= 97 && c <= 122){
		
		if(c >= 110){
			return (c - 13);
		}else{
			int newChar = 123 - (13 - (c % 97));
			return (newChar);
		}
	}
	return c;
}

int main(int argc, char **argv){
	
	if(argc == 1){
		fprintf(stderr, "Not enough arguments. Needs a directive ('encode' or 'decode') and a file.\nOutput will be the encoded/decoded file in this directory.\n");
		exit(1);
	}
	
	/* for encoding */
	if(strcmp(argv[1], "encode") == 0){
		
		/* open up the message to read and open another file to write in */
		FILE *readFile = fopen(argv[2], "r");
		FILE *writeFile = fopen("encoded_file.txt", "w");
		
		/* get each char from the read file and encode it */
		int curChar = getc(readFile);
		
		while(curChar != EOF){
			putc(ROT13encode(curChar), writeFile);
			curChar = getc(readFile);
		}
		
		/* close files */
		fclose(readFile);
		fclose(writeFile);
		
		return 0;
	}
	
	/* for decoding */
	if(strcmp(argv[1], "decode") == 0){
		
		/* open up the message to read and open another file to write in */
		FILE *readFile = fopen(argv[2], "r");
		FILE *writeFile = fopen("decoded_file.txt", "w");
		
		/* get each char from the read file and encode it */
		int curChar = getc(readFile);
		
		while(curChar != EOF){
			putc(ROT13decode(curChar), writeFile);
			curChar = getc(readFile);
		}
		
		/* close files */
		fclose(readFile);
		fclose(writeFile);
		
		return 0;
	}
	
	return 0;
}











