/* CS261- Assignment 3 - circularList.c*/
/* Name: Samantha Tone (tones@oregonstate.edu)
 * Date: 4/30/18
 * Solution description: implements a circular list with a single sentinel
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "circularList.h"

// Double link
struct Link
{
	TYPE value;
	struct Link * next;
	struct Link * prev;
};

struct CircularList
{
	int size;
	struct Link* sentinel;
};

/**
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinel's next and prev should point to the sentinel itself.
 */
static void init(struct CircularList* list)
{
	// allocates memory for sentinel
	list->sentinel = (struct Link*)malloc(sizeof(struct Link));
	assert(list->sentinel!=0);

	// assigns pts for sentinel
	list->sentinel->next = list->sentinel;
	list->sentinel->prev = list->sentinel;

	// initializes size to 0
	list->size = 0;
}

/**
 * Creates a link with the given value and NULL next and prev pointers.
 */
static struct Link* createLink(TYPE value)
{
	// allocates memory for new link
	struct Link* new = (struct Link*)malloc(sizeof(struct Link));

	// assigns NULL to next & prev ptrs
	new->next = NULL;
	new->prev = NULL;

	// sets link's value to value
	new->value = value;

	// returns created link
	return new;
}

/**
 * Adds a new link with the given value after the given link and
 * increments the list's size.
 */
static void addLinkAfter(struct CircularList* list, struct Link* link, TYPE value)
{
	// allocate memory for the new link & initialize values
	struct Link* new = createLink(value);
	assert (new!=0);

	// initializes the values of new per AFTER placement
	new->value = value;
	new->prev = link;
	new->next = link->next;

	// updates values of links already in list
	link->next->prev = new;
	link->next = new;

	// adjusts list size accordingly
	list->size++;
}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct CircularList* list, struct Link* link)
{
	// checks that list is not empty
	assert(!circularListIsEmpty(list));

	// updates the ptrs for link's prev & next ptrs to remove it from order
	link->prev->next = link->next;
	link->next->prev = link->prev;

	// adjusts list size accordingly
	list->size--;
}

/**
 * Allocates and initializes a list.
 */
struct CircularList* circularListCreate()
{
	struct CircularList* list = malloc(sizeof(struct CircularList));
	init(list);
	return list;
}

/**
 * Deallocates every link in the list and frees the list pointer.
 */
void circularListDestroy(struct CircularList* list)
{
	while (!circularListIsEmpty(list)) {
		circularListRemoveFront(list);
	}
	free(list->sentinel);
	free(list);
}

/**
 * Adds a new link with the given value to the front of the deque.
 */
void circularListAddFront(struct CircularList* list, TYPE value)
{
	// since we add after, use sentinel
	addLinkAfter(list,list->sentinel,value);
}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void circularListAddBack(struct CircularList* list, TYPE value)
{
	// since we add after, use sentinel->prev
	addLinkAfter(list,list->sentinel->prev,value);
}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE circularListFront(struct CircularList* list)
{
	// checks that list is not empty
	assert(!circularListIsEmpty(list));

	// returns value of next of sentinel
	return list->sentinel->next->value;
}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE circularListBack(struct CircularList* list)
{
	// checks that list is not empty
	assert(!circularListIsEmpty(list));

	// returns value of next of sentinel
	return list->sentinel->prev->value;
}

/**
 * Removes the link at the front of the deque.
 */
void circularListRemoveFront(struct CircularList* list)
{
	// checks that list is not empty
	assert(!circularListIsEmpty(list));

	// removes the next of sentinel
	removeLink(list,list->sentinel->next);
}

/**
 * Removes the link at the back of the deque.
 */
void circularListRemoveBack(struct CircularList* list)
{
	// checks that list is not empty
	assert(!circularListIsEmpty(list));

	// removes the prev of sentinel
	removeLink(list,list->sentinel->prev);
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int circularListIsEmpty(struct CircularList* list)
{
	// if empty, true(1); else, false(0)
	return list->size == 0;
}

/**
 * Prints the values of the links in the deque from front to back.
 */
void circularListPrint(struct CircularList* list)
{
	// checks that list is not empty
	assert(!circularListIsEmpty(list));

	// allocates space for current link used in itr starting at front
	struct Link* current = list->sentinel->next;

	// iterates through list until it hits sentinel again printing values
	while (current!=list->sentinel) {
		printf("%f ",current->value);
		current = current->next;
	}
	printf("\n");
}

/**
 * Reverses the deque.
 */
void circularListReverse(struct CircularList* list)
{
	// checks that list is not empty
	assert(!circularListIsEmpty(list));

	// creates current link for itr & int for steps through itr
	struct Link* current = list->sentinel;
	int i = list->size + 1;

	// iterates through list flipping the ptrs until sentinel is hit
	while (i!=0){
		struct Link* temp = current->next;
		// swaps the ptrs
		current->next = current->prev;
		current->prev = temp;
		// moves to next value for current
		current = current->next;
		i--;
	}


}
