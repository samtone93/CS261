/* CS261- Assignment 1 - Q.0*/
/* Name: Samantha Tone
 * Date: 4/17/18
 * Solution description:
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void fooA(int* iptr){

    /*Print the value of iptr*/
    printf("The value pointed to by iptr is: %d \n", *iptr);

    /*Print the address pointed to by iptr*/
    printf("The address pointed to by iptr is: %p \n", iptr);

    /*Print the address of iptr itself*/
    printf("The address of iptr itself is: %p \n", &iptr);

    /*Change the value of iptr itself*/
    int someVal = 0;
    iptr = &someVal;
         
}

int main(){
    
    /*declare an integer x and initialize it randomly to a value in [0,10] */
    srand(time(NULL));
    int x;
    x = rand() % 11;

    /*Print the address of x*/
    printf("The address of x is: %p \n", &x);

    /*Call fooA() with the address of x*/
    fooA(&x);

    /*Print the value of x*/
    printf("The value of x is: %d \n", x);

    /*Answer the question */
    /* The value of x is unchanged, as we are only changing the value of iptr. In order to change the value of x
     * we would need to do *iptr = 100000 */
    
    return 0;
    
}