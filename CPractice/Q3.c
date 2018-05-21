/* CS261- Assignment 1 - Q.3*/
/* Name:
 * Date:
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

void sort(struct student* students, int n){

    /*Sort the n students based on their score*/
    struct student temp;
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n-1; j++)
        {
            if(students[j].score > students[j+1].score)
            {
                temp = students[j];
                students[j] = students[j+1];
                students[j+1] = temp;
            }
        }
    }

}

int main(){

    /*Declare an integer n and assign it a value.*/
	int n = 25;
    
    /*Allocate memory for n students using malloc.*/
	struct student *students = (struct student *) malloc(n * sizeof(struct student));

    /*Generate random and unique IDs and random scores for the n students, using rand().*/
	srand(time(NULL));
	int array[n];
	for (int i =0; i<n; i++)
	{
		array[i] = i+1;
	}
	int random;
	for (int i = n-1; i > -1; i--)
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
    
    /*Print the contents of the array of n students.*/
	struct student studVar;
	printf("== BEFORE SORTING ==\n");
	printf("ID\tSCORE\n");
	for (int i = 0; i < n; i++)
	{
		studVar = students[i];
		printf("%d\t%d\n",studVar.id,studVar.score);
	}

    /*Pass this array along with n to the sort() function*/
    sort(students, n);

    /*Print the contents of the array of n students.*/
    printf("== AFTER SORTING ==\n");
    printf("ID\tSCORE\n");
    for (int i = 0; i < n; i++)
    {
        studVar = students[i];
        printf("%d\t%d\n",studVar.id,studVar.score);
    }
    
    return 0;
}
