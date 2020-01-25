/*
	
	Program Description Stuff
	
	printf("\nEvaluating Infix Expressions\n\nProgram Developers:\n   Sijera, Mark Andrae A.\t2018-08513\n   Suico, Tobias O.\t\t2015-14424\n");
	printf("\nDevelopment Period: Jan 25 2020 - Jan ? 2020\n");
	printf("\nMenu Action Information\n");
	printf("\n   [E] Evaluate Console-input Expression(s) - takes user infix expression input and evaluates it to display its result as output.");
	printf("\n   [C] Evaluate File-input Expression(s) - takes infix expression inputs from a file and evaluates every expression to display its result as output.");
	printf("\n   [0] Exit - terminates the program.\n\nPress ENTER to return to main menu...");
*/

#include <stdio.h>
#include <stdlib.h>

struct Node {
	char data;
	struct Node *next;
};

typedef struct Node node;
typedef node *qPtr, *sPtr;

void sPush( sPtr*, char ); // push node to stack
void qPush( qPtr*, qPtr*, char ); // push node to queue
void pop( node** ); // pop node from stack/queue
void display( node* ); // display queue/stack content
void flushS2Q( sPtr*, qPtr*, qPtr* ); // move stack contents to queue

int main() {
	sPtr stack = NULL;
	qPtr qStart = NULL, qEnd = NULL;
	
	// sample start
	printf("Pushing stuff to stack...\n");
	printf("Push \'a\'\n");
	sPush( &stack, 'a' );
	printf("Push \'b\'\n");
	sPush( &stack, 'b' );
	printf("Push \'c\'\n\n");
	sPush( &stack, 'c' );
	
	printf("Pushing stuff to queue...\n");
	printf("Enqueue \'a\'\n");
	qPush( &qStart, &qEnd, 'a' );
	printf("Enqueue \'b\'\n");
	qPush( &qStart, &qEnd, 'b' );
	printf("Enqueue \'c\'\n\n");
	qPush( &qStart, &qEnd, 'c' );
	
	
	printf("Displaying...\nStack: ");
	display( stack );
	printf("\nQueue: ");
	display(  qStart );
	// sample end
	
	return 0;
}

void sPush( sPtr *start, char data ) {
	// create new node
	sPtr newPtr = malloc( sizeof( node ) );
	
	if ( newPtr != NULL ) {
		// assign data to new node
		newPtr->data = data;
		// point new node next ptr to current start
		newPtr->next = *start;
		
		// make new node start of stack
		*start = newPtr;
	} else
		printf("Can't create new node.");
}

void qPush( qPtr *start, qPtr* end, char data ) {
	// create new node
	qPtr newPtr = malloc( sizeof( node ) );
	
	if ( newPtr != NULL ) {
		// assign data to new node
		newPtr->data = data;
		// point new node next ptr to NULL
		newPtr->next = NULL;
		
		if ( *end == NULL )
			// if queue is empty, make new ptr the start of queue
			*start = newPtr;
		else
			// otherwise place it after the current end node of queue
			( *end )->next = newPtr;
		
		// make new node end of queue
		*end = newPtr;
	} else
		printf("Can't create new node.");
}

void pop( node** targNode ) {
	node* temp;
	
	// store ptr to target node to a temporary ptr
	temp = *targNode;
	// then make target node ptr point to next node
	*targNode = ( *targNode )->next;
	
	// free target ptr
	free( temp );
}

void display( node* current ) {
	// print data in current node while it isn't null
	while ( current != NULL ) {
		printf("%c ", current->data );
		current = current->next;
	}
}

void flushS2Q( sPtr* src, qPtr* start, qPtr* end ) {
	while( *src != NULL ) {
		// push top of stack to end of queue
		qPush( start, end, ( *src )->data );
		// pop top of stack
		pop( src );
	}
}
