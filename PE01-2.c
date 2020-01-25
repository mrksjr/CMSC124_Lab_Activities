#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* getString();
void stringExp( char* );
void stringCom( char* );

void menu();
void progDesc();

int main() {
	char *str, c;
	
	while( 1 ) {
		menu();
		scanf( "%c", &c );
		
		switch( c ) {
			case 'P': case 'p':
				progDesc();
			break;
			
			case 'E': case 'e':
				printf("\n");
				while ( 1 ) {
					str = getString();
					stringExp( str ); // call function for expanding strings
					free( str ); // free allocated memory for input
					
					printf("Would you like to repeat this action? ( Y/y to repeat )\nChoice: ");
					scanf("%c", &c);
					
					if ( c == 'y' || c == 'Y' ) {
						printf("\n");
						continue;
					}
					
					break;
				}
			break;
			
			case 'C': case 'c':
				printf("\n");
				while ( 1 ) {
					str = getString();
					stringCom( str ); // call function for expanding strings
					free( str ); // free allocated memory for input
				
					printf("Would you like to repeat this action? ( Y/y to repeat )\nChoice: ");
					scanf("%c", &c);
					
					if ( c == 'y' || c == 'Y' ) {
						printf("\n");
						continue;
					}
					
					break; 
				}
			break;
			
			case '0':
				printf("\nProgram terminated.");
				return 0;
			
			default:
				printf("\nInvalid input.\n\n");
				while ( getchar() != '\n' ); // clear input buffer
				continue;
			break;
		}
		
		printf("\n");
		
		while ( getchar() != '\n' ); // clear input buffer
	}
	
	return 0;
}

char* getString() {
	while ( getchar() != '\n' ); // clear input buffer
	printf("Input a string: ");
	
	char *str = malloc( sizeof(char) );

	char c;
	// i stores the current index in the string to place new char to
	// len stores the length of the string
	int i = 0, len = 1;
	
	// get char from user until enter key is pressed
	while ( ( c = getchar() ) != '\n' ) {
		// reallocate memory for string then add one more for next iteration
		str = realloc( str, len++ * sizeof(char) );
		// concatenate char to string variable
		str[i++] = c;
	}
	str[i++] = '\0'; // add terminating character
	
	return str;
}

void stringExp( char* str ) {
	int i = 0;
	// check string validity
	while ( str[i] != '\0' ) {
		char c = str[i];
		
		// check if there are any characters that isn't a letter or a number
		if ( ( c < 'a' || c > 'z' ) && ( c < 'A' || c > 'Z' ) && ( c < '0' || c > '9' ) ) {
			printf("\nInvalid character found in string.\n\n");
			return;
		}
		
		i++;
	}
	
	// allocate memory for int array that will store the count of each character, starting at size 1
	int *n = malloc( 1 * sizeof( int ) );
	// allocate memory for char array that will store the characters in the string, starting at size 1
	char *X = malloc( 1 * sizeof( char ) );
	
	int size = 1;
	i = 0;
	n[0] = 0;
	
	while ( str[i] != '\0' ) {
	 	char c = str[i];
	 	int j = size - 1;
	 	
		if ( c >= '0' && c <= '9' ) { // current character is a number
			// reallocate new space for next element
			n = realloc( n, size * sizeof( int ) );
			
			n[j] = c - 48;
			
			// check if next character is a number
			char next = str[++i];
			while ( next >= '0' && next <= '9' ) {
				// promote current value of n[j] by one digit then add the value of next character
				n[j] = ( n[j] * 10 ) + ( next - 48 );
				next = str[++i]; // read next character
			}
			
			// then read the character succeeding the number
			c = str[i];
			// allocate new space for next element
			X = realloc( X, size * sizeof( char ) );
			// add current char to X
			X[j] = c;
		}
		else if ( ( c >= 'a' && c <= 'z' ) || ( c >= 'A' && c <= 'Z' ) ) { // current char is a letter
			// allocate new space for next element
			X = realloc( X, size * sizeof( char ) );
			
			// add current char to X
			X[j] = c;
			
			// since no number preceded the character, set its n to 1
			n = realloc( n, size * sizeof( int ) );
			n[j] = 1;
		}
		
		++i; // read next character in string
		++size; // increase size of arrays n and X
	}

	// printing the expanded form
	printf("\nExpanded form: ");
	for ( i = 0; i < size - 1; ++i ) {
		// print n copies of character X
		int j;
		for ( j = 0; j < n[i]; ++j ) {
			printf("%c", X[i] );
		}
	}
	
	printf("\n\n");

	// free allocated memory
	free( n );
	free( X );
}

void stringCom( char* str ) {
	int i = 0; // stores current index
	
	// check string validity
	while ( str[i] != '\0' ) {
		char c = str[i];
		
		// check if there are any non-letter characters
		if ( ( c < 'a' || c > 'z' ) && ( c < 'A' || c > 'Z' ) ) {
			printf("\nInvalid character found in string.\n\n");
			return;
		}
		
		i++;
	}
	
	int n = strlen( str );
	i = 0; // reset current index to start of string
	
	// iterate through the string again
	printf("\nCompressed Form: ");
	while( i < n ) {
		// get a character
		char c = str[i];
		
		int m = 1;
		// while succeeding character is same as character c, increase its count (m)
		while ( c == str[i + 1] ) {
			i++;
			m++;
		}
		
		// no need to display if count is 1
		if ( m > 1 )
			printf("%d", m);
		
		// display character
		printf("%c", c);
		
		// read next character
		i++;
	}
	
	printf("\n\n");
}

void menu() {
	printf("Welcome to this String Expansion/Compression program!\n\nPlease choose an action to perform...\n");
	printf("   [P] Program Description\n   [E] String Expansion\n   [C] String Compression\n   [0] Exit\n\nChoice: ");
}

void progDesc() {
	printf("\nString Manipulation\n\nProgram Developers:\n   Sijera, Mark Andrae A.\t2018-08513\n   Suico, Tobias O.\t\t2015-14424\n");
	printf("\nDevelopment Period: Jan 24 2020 - Jan 25 2020\n");
	printf("\nMenu Action Information\n");
	printf("\n   [E] String Expansion - takes user string input with substrings of form nX and prints n copies of\n\tthe letter X for every substring. (ie. 2a2B3c -> aaBBccc)");
	printf("\n   [C] String Compression - takes user string input and compresses the string into substrings of the\n\tform nX. (ie. aaCCCb -> 2a3Cb)");
	printf("\n   [0] Exit - terminates the program.\n\nPress ENTER to return to main menu...");
	
	while( getchar() != '\n' ); // clear input buffer
}
