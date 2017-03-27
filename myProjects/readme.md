some things I've learned:    
    
<b>converting an int to binary</b>    
---   
-printing a calloc'd array as a string won't show 0s because calloc sets all <b>bits</b> to 0 (i.e. all indices are actually '\0', which means it's automatically a null-terminated string?). 
Since '%s' looks at chars, and the bit representation of '0' is 110000 (ASCII 48), each index is not '0' as I initially thought would happen.
<a href='http://stackoverflow.com/questions/17975575/difference-between-binary-zeros-and-ascii-character-zero'> This </a> is helpful.    
    
In int_to_binary, I used a for-loop to print out all the bits of the binary number. I also put in all the bits into a char array as integers.    
    
In int_to_bin2, I put all the bits as characters in the array and was able to print the binary number in one string (using printf and '%s').    

<b>ROT13 cipher </b>   
---    
-learned about reading and writing files.    

-created a function that rotates letters 13 places to encode and another to decode by applying the reverse.  

-the EOF of a file should be considered an int and not a char.

-things to improve: check if this works for multiple-line messages. 
    
<b>task_list   </b> 
---   
-input some tasks based on priority number and retrieve the task with the next lowest number (meaning higher priority).    
    
-finally trying to use a neat data structure (min heap) in a somewhat practical(?) application.    
    
-getting acquainted with the Win32 API for GUI making.
    
-received a good lesson on the importance of function scopes. For example, in one of my functions where I get a string from a text input window and assign it to a variable, I forgot that local variables get destroyed after a function ends.    
    
Additionally, my function method that creates a new hashmap, which takes a string as an argument, was implemented poorly in that all I did was assign a hashmap's key to the passed-in string argument. This might be ok if my whole program was taking place within a single scope, like main, but I needed to access this hashmap from another function. Therefore, when the function where I get the text input string ended, the local variable I assigned my hashmap's key to was destroyed and my hashmap's key was left pointing to some unknown area in memory, I think.    
    
The solution here was to allocate some memory, copy over the string I wanted to the new memory, and then assign my hashmap's key to that memory location. This way I could always access my hashmap from any function.
