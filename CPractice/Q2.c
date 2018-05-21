/* CS261- Assignment 1 - Q.2*/
/* Name: Samantha Tone
 * Date: 4/17/18
 * Solution description:
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int foo(int* a, int* b, int c){

    /* Increment a */
    *a = *a + 1;
    
    /* Decrement  b */
    *b = *b - 1;
    
    /* Assign a+b to c */
    c = *a + *b;
    
    /* Return c */
    return c;

}

int main(){

    /* Declare three integers x,y and z and initialize them randomly to values in [0,10] */
    srand(time(NULL));
    int x = rand() % 11;
    int y = rand() % 11;
    int z = rand() % 11;
    int fooVal;

    /* Print the values of x, y and z */
    printf("x: %d\ny: %d\nz: %d\n",x,y,z);
    
    /* Call foo() appropriately, passing x,y,z as parameters */
    fooVal = foo(&x,&y,z);

    /* Print the value returned by foo */
    printf("Int return value of foo: %d\n",fooVal);

    /* Print the values of x, y and z */
    printf("x: %d\ny: %d\nz: %d\n",x,y,z);

    return 0;
}
    
    

