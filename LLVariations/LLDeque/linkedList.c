/* CS261- Assignment 3 - linkedList.c*/
/* Name: Samantha Tone (tones@oregonstate.edu)
 * Date: 4/30/18
 * Solution description: implements a linked list with back & front sentinels
 */

#include "linkedList.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

// Double link
struct Link
{
	TYPE value;
	struct Link* next;
	struct Link* prev;
};

// Double linked list with front and back sentinels
struct LinkedList
{
	int size;
	struct Link* frontSentinel;
	struct Link* backSentinel;
};

/**
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinels' next and prev should point to eachother or NULL
 * as appropriate.
 */
static void init(struct LinkedList* list) {
	// allocates memory for frontSentinel
    list->frontSentinel = (struct Link*)malloc(sizeof(struct Link));
    assert(list->frontSentinel!=0);

    // allocates memory for backSentinel
    list->backSentinel = (struct Link*)malloc(sizeof(struct Link));
    assert(list->backSentinel!=0);

    // assigns the ptrs for each sentinel
    list->frontSentinel->next = list->backSentinel;
    list->backSentinel->prev = list->frontSentinel;
    list->frontSentinel->prev = NULL;
    list->backSentinel->next = NULL;

    // initializes size to 0
    list->size = 0;
}

/**
 * Adds a new link with the given value before the given link and
 * increments the list's size.
 */
static void addLinkBefore(struct LinkedList* list, struct Link* link, TYPE value)
{
    // allocate memory for the new link & initialize values
    struct Link* new = (struct Link*)malloc(sizeof(struct Link));
    assert (new!=0);

    // initializes the values of new per BEFORE placement
    new->value = value;
    new->prev = link->prev;
    new->next = link;

    // updates the values of the links already in the list
    link->prev->next = new;
    link->prev = new;

    // updates size to include new link
    list->size++;
}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct LinkedList* list, struct Link* link)
{
	// updates the ptrs for link's prev & next ptrs to remove it from order
    link->prev->next = link->next;
    link->next->prev = link->prev;

    // frees memory used by link then adjusts the list size
    free(link);
    list->size--;
}

/**
 * Allocates and initializes a list.
 */
struct LinkedList* linkedListCreate()
{
	struct LinkedList* newDeque = malloc(sizeof(struct LinkedList));
	init(newDeque);
	return newDeque;
}

/**
 * Deallocates every link in the list including the sentinels,
 * and frees the list itself.
 */
void linkedListDestroy(struct LinkedList* list)
{
	while (!linkedListIsEmpty(list))
	{
		linkedListRemoveFront(list);
	}
	free(list->frontSentinel);
	free(list->backSentinel);
	free(list);
}

/**
 * Adds a new link with the given value to the front of the deque.
 */
void linkedListAddFront(struct LinkedList* list, TYPE value)
{
	// since we add before must use the next of frontSentinel
    addLinkBefore(list, list->frontSentinel->next, value);
}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void linkedListAddBack(struct LinkedList* list, TYPE value)
{
	// adds before the backSentinel
    addLinkBefore(list, list->backSentinel, value);
}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE linkedListFront(struct LinkedList* list)
{
	// checks that the list is not empty
    assert(!linkedListIsEmpty(list));

    // returns the value of the next of frontSentinel
    return list->frontSentinel->next->value;
}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE linkedListBack(struct LinkedList* list)
{
    // checks that the list is not empty
    assert(!linkedListIsEmpty(list));

    // returns the value of the prev of backSentinel
    return list->backSentinel->prev->value;
}

/**
 * Removes the link at the front of the deque.
 */
void linkedListRemoveFront(struct LinkedList* list)
{
    // checks that the list is not empty
    assert(!linkedListIsEmpty(list));

    // removes the next of frontSentinel
    removeLink(list,list->frontSentinel->next);
}

/**
 * Removes the link at the back of the deque.
 */
void linkedListRemoveBack(struct LinkedList* list)
{
    // checks that the list is not empty
    assert(!linkedListIsEmpty(list));

    // removes the prev of backSentinel
    removeLink(list,list->backSentinel->prev);
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int linkedListIsEmpty(struct LinkedList* list)
{
	// if empty, true(1); else, false(0)
    return list->size == 0;
}

/**
 * Prints the values of the links in the deque from front to back.
 */
void linkedListPrint(struct LinkedList* list)
{
	// checks that the list is not empty
    assert(!linkedListIsEmpty(list));

    // allocates space for current link used in itr starting at front
    struct Link* current = list->frontSentinel->next;

    // iterates through list until it hits back sentinel printing values
    while (current!=list->backSentinel) {
        printf("%d ",current->value);
        current = current->next;
    }
    printf("\n");
}

/**
 * Adds a link with the given value to the bag.
 */
void linkedListAdd(struct LinkedList* list, TYPE value)
{
	// adds value to the bag by appending as next of frontSentinel
    addLinkBefore(list,list->frontSentinel->next,value);
}

/**
 * Returns 1 if a link with the value is in the bag and 0 otherwise.
 */
int linkedListContains(struct LinkedList* list, TYPE value)
{
    // checks that the list is not empty
    assert(!linkedListIsEmpty(list));

    // allocates space for current link used in itr starting at front
    struct Link* current = list->frontSentinel->next;

    // iterates through list until it hits back sentinel or value
    while (current!=list->backSentinel) {
        if (current->value == value) {
            return 1;
        }
        // updates current for next itr
        current = current->next;
    }

    // returns 0 if value was never hit during itr
    return 0;
}

/**
 * Removes the first occurrence of a link with the given value.
 */
void linkedListRemove(struct LinkedList* list, TYPE value)
{
	// checks that the list is not empty
    assert(!linkedListIsEmpty(list));

    // checks that list contains value before going through itr
    assert(linkedListContains(list,value));

    // allocates space for current link used in itr starting at front
    struct Link* current = list->frontSentinel->next;

    // iterates through list until the first value is removed (free current)
    while (current!=0) {
        if (current->value == value) {
            removeLink(list,current);
            current = 0;
        }
        else {
            current = current->next;
        }
    }

}
