/* CS261- Assignment 1 - Q.1*/
/* Name: Samantha Tone
 * Date: 4/17/18
 * Solution description:
 */
 
#include <stdio.h>
#include<stdlib.h>
#include<math.h>
#include <time.h>

struct student{

	int id;
	int score;

};

struct student* allocate(){

    /*Allocate memory for ten students*/
    struct student *ptr = (struct student *) malloc(10 * sizeof(struct student));

    /*return the pointer*/
    return ptr;

}

void generate(struct student* students){

    /*Generate random and unique ID and random scores for ten students, ID being between 1 and 10, scores between 0 and 100*/
    srand(time(NULL));
    int array[10] = {1,2,3,4,5,6,7,8,9,10};
    int random;
    for (int i = 9; i > -1; i--)
    {
        random = rand() % (i+1);
        (students + i) -> id = array[random];
        for (int j = random; j < i; j++)
        {
            array[j]=array[j+1];
        }
        array[i] = 0;
        (students + i) -> score = rand() % 101;
    }
     
}

void output(struct student* students){
    /*Output information about the ten students in the format:
        ID1 Score1
        ID2 score2
        ID3 score3
        ...
        ID10 score10*/
    struct student studVar;
    printf("== STUDENTS ==\n");
    printf("ID\tSCORE\n");
    for (int i = 0; i < 10; i++)
    {
        studVar = students[i];
        printf("%d\t%d\n",studVar.id,studVar.score);
    }
}

void summary(struct student* students){
     /*Compute and print the minimum, maximum and average scores of the ten students*/
     int min = 101;
     int max = -1;
     float total = 0.00;
     float avg;
     for (int i = 0; i < 10; i++)
     {
        if (students[i].score < min)
        {
            min = students[i].score;
        }
        if (students[i].score > max)
        {
            max = students[i].score;
        }
        total += students[i].score;
     }
     avg = total / 10;
     printf("== SCORES ==\n");
     printf("Minimum: %d\n", min);
     printf("Maximum: %d\n", max);
     printf("Average: %.2f\n", avg);
}

void deallocate(struct student* stud){
    /*Deallocate memory from stud*/
    if(stud != NULL)
        free(stud);
}

int main(){

    struct student* stud = NULL;
    
    /*call allocate*/
    stud = allocate();
    
    /*call generate*/
    generate(stud);
    
    /*call output*/
    output(stud);
    
    /*call summary*/
    summary(stud);

    /*call deallocate*/
    deallocate(stud);

    return 0;
}