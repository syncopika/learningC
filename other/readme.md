some things I've learned:    
    
 converting an int to binary    
 =================    
-printing a calloc'd array as a string won't show 0s because calloc sets all <b>bits</b> to 0 (i.e. all indices are actually '\0', which means it's automatically a null-terminated string?). 
Since '%s' looks at chars, and the bit representation of '0' is 110000 (ASCII 48), each index is not '0' as I initially thought would happen.
<a href='http://stackoverflow.com/questions/17975575/difference-between-binary-zeros-and-ascii-character-zero'> This </a> is helpful.    
    
-if you want to change the contents of a pointer within a function, you should have that function accept a pointer-to-a-pointer as an argument.
Then once inside the function, dereference the pointer-to-pointer to actually access the first pointer. I haven't done this yet, but came across it as I was looking for answers. Probably good to know.    
    
-a variable can become a pointer by attaching '&' in front, meaning 'address-of'.    
    
In int_to_binary, I used a for-loop to print out all the bits of the binary number. I also put in all the bits into the char array as integers.    
    
In int_to_bin2, I put all the bits as characters in the array and was able to print the binary number in one string.    
    
----------------
ROT13 cipher    
 ==================    
-learned about reading and writing files.    

-created a function that rotates letters 13 places to encode and another to decode by applying the reverse.  

-the EOF of a file should be considered an int and not a char.
