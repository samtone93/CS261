/* CS261- Assignment 1 - Q.4*/
/* Name: Samantha Tone
 * Date: 4/17/18
 * Solution description:
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

/*converts ch to upper case, assuming it is in lower case currently*/
char toUpperCase(char ch){
     return ch-'a'+'A';
}


void camelCase(char* word){
    int i = 0;
    int j = 0;
    int k = 0;
    /*Convert to camelCase*/
    while(word[i] != '\0')
    {
        if (word[i] >= 'a' && word[i] <= 'z')
        {
            if (k == 0)
            {
                word[i] = word[i];
            }
            else
            {
                word[i] = toUpperCase(word[i]);
                k = 0;
            }
            i++;
        }
        else if (word[i] == '_')
        {
            for (j=i; j<100; j++)
            {
                word[j] = word[j+1];
            }
            k = 1;
        }
        else
        {
            for (i = 0; i < 1000; i++)
            {
                word[i] = '\0';
            }
            i = 0;
        }
    }
}

int main(){

    char str[1000];

    /*Read the string from the keyboard */
    printf("Enter a string: ");
    scanf("%s", str);

    /*Call camelCase*/
    camelCase(str);

    /*Print the new the string */
    if (str[0]=='\0')
    {
        printf("ERROR: INVALID INPUT\n");
    }
    else
    {
        printf("Inputted string in (lower) camelCase: %s\n", str);
    }

    
    return 0;
}