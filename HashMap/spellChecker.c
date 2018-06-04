#include "hashMap.h"
#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * Allocates a string for the next word in the file and returns it. This string
 * is null terminated. Returns NULL after reaching the end of the file.
 * @param file
 * @return Allocated string or NULL.
 */
char* nextWord(FILE* file)
{
    int maxLength = 16;
    int length = 0;
    char* word = malloc(sizeof(char) * maxLength);
    while (1)
    {
        char c = fgetc(file);
        if ((c >= '0' && c <= '9') ||
            (c >= 'A' && c <= 'Z') ||
            (c >= 'a' && c <= 'z') ||
            c == '\'')
        {
            if (length + 1 >= maxLength)
            {
                maxLength *= 2;
                word = realloc(word, maxLength);
            }
            word[length] = c;
            length++;
        }
        else if (length > 0 || c == EOF)
        {
            break;
        }
    }
    if (length == 0)
    {
        free(word);
        return NULL;
    }
    word[length] = '\0';
    return word;
}

/**
 * Loads the contents of the file into the hash map.
 * @param file
 * @param map
 */
void loadDictionary(FILE* file, HashMap* map)
{
    // uses same idea from concordance in main.c to put dictionary into hashmap
    char* word = nextWord(file);
    while (word != NULL) {
        hashMapPut(map, word, 1);
        free(word);
        word = nextWord(file);
    }
    free(word);
}

// function to compute the LevenshteinDistance based off the Wiki page
int distance(char* s1, char* s2) {
    // initializes the matrix, cost ints, & matrix x,y indicies for traversal
    int x;
    int y;
    int subCost;
    int insCost;
    int delCost;
    int s1len = strlen(s1);
    int s2len = strlen(s2);
    int matrix[s2len+1][s1len+1];
    
    matrix[0][0] = 0; // top left block is always 0
    // sets up first row & first column to increase by 1 with each increasing block
    for (x=1; x<=s2len; x++)
        matrix[x][0] = x;
    for (y=1; y<=s1len; y++)
        matrix[0][y] = y;

    // loops through the matrix assigning the min between deletion, insertion, & substitution
    for (x = 1; x <= s2len; x++) {
        for (y = 1; y <= s1len; y++) {
            if (s1[y-1] == s2[x-1])
                subCost = matrix[x-1][y-1];
            else
                subCost = matrix[x-1][y-1] + 1;
            delCost = matrix[x-1][y] + 1;
            insCost = matrix[x][y-1] + 1;
            // finds minimum between the 3 to assign to matrix value
            if (subCost <= delCost && subCost <= insCost)
                matrix[x][y] = subCost;
            else if (delCost <= subCost && delCost <= insCost)
                matrix[x][y] = delCost;
            else if (insCost <= subCost && insCost <= delCost)
                matrix[x][y] = insCost;
        }
    }
    return(matrix[s2len][s1len]);
}

/**
 * Prints the concordance of the given file and performance information. Uses
 * the file input1.txt by default or a file name specified as a command line
 * argument.
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, const char** argv)
{
    HashMap* map = hashMapNew(1000);
    
    FILE* file = fopen("dictionary.txt", "r");
    clock_t timer = clock();
    loadDictionary(file, map);
    timer = clock() - timer;
    printf("Dictionary loaded in %f seconds\n", (float)timer / (float)CLOCKS_PER_SEC);

    char inputBuffer[256];
    int quit = 0;
    while (!quit)
    {
        printf("Enter a word or \"quit\" to quit: ");
        scanf("%s", inputBuffer);
        int ct = 0;
        while (inputBuffer[ct]) {
            inputBuffer[ct]=tolower(inputBuffer[ct]);
            ct++;
        }
        
        if (strcmp(inputBuffer, "quit") == 0)
        {
            quit = 1;
        }

        /* Beginning of spell checker code */
        // case where the dictionary contains the input
        else if (hashMapContainsKey(map, inputBuffer)){
            printf("The inputted word \" %s \" is spelled correctly\n", inputBuffer);
        }
        else {
            printf("The inputted word \" %s \" is spelled incorrectly\n", inputBuffer);
            printf("Did you mean one of the following words? (Please re-input word accordingly)\n");
            // updates values for each key to the distance between it & the inputBuffer
            for (int i = 0; i < map->capacity; i++) {
                HashLink* link = map->table[i];
                if (link != NULL)
                {
                    while (link != NULL)
                    {
                        int* ptrVal = hashMapGet(map,link->key);
                        (*ptrVal) = distance(inputBuffer,link->key);
                        link = link->next;
                    }
                }
            }

            // loops until 5 similar words are found
            int stopper = 0;
            int dist = 1;
            while (stopper < 5) {
                for (int i = 0; i < map->capacity; i++) {
                    HashLink* link = map->table[i];
                    if (link != NULL && stopper != 5)
                    {
                        while (link != NULL && stopper != 5)
                        {
                            int* val = hashMapGet(map,link->key);
                            if (*val == dist) {
                                stopper++;
                                printf("%d. %s\n", stopper, link->key);
                            }
                            link = link->next;
                        }
                    }
                    if (stopper == 5)
                        break;
                }
                dist++;
            }
        }

        /* End of spell checker code */
    }
    
    hashMapDelete(map);

    fclose(file);
    return 0;
}