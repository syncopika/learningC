some things I've learned:    
    
 converting an int to binary    
 =================    
-printing a calloc'd array as a string won't show 0s because calloc sets all <b>bits</b> to 0 (i.e. all indices are actually '\0', which means it's automatically a null-terminated string?). 
Since '%s' looks at chars, and the bit representation of '0' is 110000 (ASCII 48), each index is not '0' as I initially thought would happen.
<a href='http://stackoverflow.com/questions/17975575/difference-between-binary-zeros-and-ascii-character-zero'> This </a> is helpful.    
    
-if you want to edit some elements in a pointer (i.e. char array) within a function, you should have that function accept a pointer-to-a-pointer as an argument.
Then once inside the function, dereference the argument to actually access the array.    
    
-a variable can become a pointer by attaching '&' in front, meaning 'address-of'. 
