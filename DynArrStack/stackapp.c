/* CS261 - Assignment 2 - Part 3*/
/* Name: Samantha Tone
 * Date: 4/23/18
 * Solution description: Application of the Stack - Checking balanced parentheses, braces, and brackets
 */

/*	stack.c: Stack application. */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dynArray.h"


/* ***************************************************************
Using stack to check for unbalanced parentheses.
***************************************************************** */

/* Returns the next character of the string, once reaches end return '0' (zero)
	param: 	s pointer to a string 	
	pre: s is not null		
*/
char nextChar(char* s)
{
	static int i = -1;	
	char c;
	++i;	
	c = *(s+i);			
	if ( c == '\0' )
		return '\0';	
	else 
		return c;
}

/* Checks whether the (), {}, and [] are balanced or not
	param: 	s pointer to a string 	
	pre: s is not null	
	post:	
*/
int isBalanced(char* s)
{
	/* FIXME: You will write this function */

	DynArr *dyn;
	dyn = newDynArr(50);
	char c;

    while ((c = nextChar(s)) != '0') {
        if ((c == '(') || (c == '{' ) || (c == '[')) {
            pushDynArr(dyn,c);
        }

        else if (c == ')') {
            if (topDynArr(dyn) == '(') {
                popDynArr(dyn);
            }
            else {
                return 0;
            }
        }

        else if (c == '}') {
            if (topDynArr(dyn) == '{') {
                popDynArr(dyn);
            }
            else {
                return 0;
            }
        }

        else if (c == ']') {
            if (topDynArr(dyn) == '[') {
                popDynArr(dyn);
            }
            else {
                return 0;
            }
        }
    }

    if(!isEmptyDynArr(dyn)){
        return 0;
    }
    deleteDynArr(dyn);
    return 1;

}

int main(int argc, char* argv[]){

    char* s=argv[1];
	int res;
	
	printf("Assignment 2\n");

	res = isBalanced(s);

	if (res)
		printf("The string %s is balanced\n",s);
	else 
		printf("The string %s is not balanced\n",s);
	
	return 0;	
}

