#include <stdio.h> // Statement to include all info from the 'stdio.h' library

int main()         // Defines a function called 'main' that recieves no arguments. It is currently defined as a int function, 
				           // which means that the return value is expected to be an integer.
{
		int newVar;    // Declaration of a new integer variable. The computer initialized a certain amount of bytes and expects only integers to be assigned to this. 
		newVar = 0;    // The initialized variable is assigned the value of 0. 

		char newCharVar = 'a'; // Variables can be declared and assigned in the same line.

		printf("Hello, world\n"); // This function is declared and defined in 'stdio.h' Simply prints the sequence of characters to the terminal. 
		// '\n' is C notation for a new line character. Means the cursor should automatically move to the next line in the terminal 
    // after printing the sequence of characters before it.

		return 0; // Function returns 0 since functions are expected to return something. 
} // All the statements within the curly brackets are the statements of that particular function.