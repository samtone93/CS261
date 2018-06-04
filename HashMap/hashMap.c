/*
 * CS 261 Data Structures
 * Assignment 5
 * Name: Samantha Tone
 * Date: 6/4/18
 */

#include "hashMap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

int hashFunction1(const char* key)
{
    int r = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        r += key[i];
    }
    return r;
}

int hashFunction2(const char* key)
{
    int r = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        r += (i + 1) * key[i];
    }
    return r;
}

/**
 * Creates a new hash table link with a copy of the key string.
 * @param key Key string to copy in the link.
 * @param value Value to set in the link.
 * @param next Pointer to set as the link's next.
 * @return Hash table link allocated on the heap.
 */
HashLink* hashLinkNew(const char* key, int value, HashLink* next)
{
    HashLink* link = malloc(sizeof(HashLink));
    link->key = malloc(sizeof(char) * (strlen(key) + 1));
    strcpy(link->key, key);
    link->value = value;
    link->next = next;
    return link;
}

/**
 * Free the allocated memory for a hash table link created with hashLinkNew.
 * @param link
 */
static void hashLinkDelete(HashLink* link)
{
    free(link->key);
    free(link);
}

/**
 * Initializes a hash table map, allocating memory for a link pointer table with
 * the given number of buckets.
 * @param map
 * @param capacity The number of table buckets.
 */
void hashMapInit(HashMap* map, int capacity)
{
    map->capacity = capacity;
    map->size = 0;
    map->table = malloc(sizeof(HashLink*) * capacity);
    for (int i = 0; i < capacity; i++)
    {
        map->table[i] = NULL;
    }
}

/**
 * Removes all links in the map and frees all allocated memory. You can use
 * hashLinkDelete to free the links.
 * @param map
 */
void hashMapCleanUp(HashMap* map)
{
    // checks that map is not NULL before proceeding
    assert(map != NULL);

    // initializes HashLinks outside of loop to avoid mem leaks
    HashLink* curLink;
    HashLink* nextLink;
    int mapCap = hashMapCapacity(map);

    // for loop to free each of the links in map
    for (int i = 0; i < mapCap; i++) {
        // sets the curLink equal to the current index of the table
        curLink = map->table[i];

        // if there is linked list at the index, while loop is used to clear each index
        while (curLink != NULL) {
            // creates nextLink to hold next of curLink for when its cleared
            nextLink = curLink->next;
            // deletes curLink
            hashLinkDelete(curLink);
            // uses nextLink to move curLink to next link position
            curLink = nextLink;
        }
    }

    // once each link is removed, table is cleared & map size is 0 again
    free(map->table);
    map->size = 0;
}

/**
 * Creates a hash table map, allocating memory for a link pointer table with
 * the given number of buckets.
 * @param capacity The number of buckets.
 * @return The allocated map.
 */
HashMap* hashMapNew(int capacity)
{
    HashMap* map = malloc(sizeof(HashMap));
    hashMapInit(map, capacity);
    return map;
}

/**
 * Removes all links in the map and frees all allocated memory, including the
 * map itself.
 * @param map
 */
void hashMapDelete(HashMap* map)
{
    hashMapCleanUp(map);
    free(map);
}

/**
 * Returns a pointer to the value of the link with the given key  and skip traversing as well. Returns NULL
 * if no link with that key is in the table.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 * 
 * @param map
 * @param key
 * @return Link value or NULL if no matching link.
 */
int* hashMapGet(HashMap* map, const char* key)
{
    // checks that map & key are not NULL
    assert(map != NULL && key != NULL);

    // uses the HASH_FUNCTION & capacity to find the index
    int index = HASH_FUNCTION(key) % hashMapCapacity(map);
    // assigns this table index to curLink, so it can traverse links at index
    HashLink* curLink = map->table[index];

    // while loop uses to traverse the list at the index to find specified key
    while (curLink != NULL) {
        // for the case when curLink->key == key
        if (strcmp(curLink->key,key) == 0) {
            return &(curLink->value);
        }
        // goes to next place if the keys are not equal
        curLink = curLink->next;
    }

    // in case the matching keys are not found, NULL is returned
    return NULL;
}

/**
 * Resizes the hash table to have a number of buckets equal to the given
 * capacity. After allocating the new table, all of the links need to be
 * rehashed into it because the capacity has changed.
 * 
 * Remember to free the old table and any old links if you use hashMapPut to
 * rehash them.
 * 
 * @param map
 * @param capacity The new number of buckets.
 */
void resizeTable(HashMap* map, int capacity)
{
    // asserts that map & cap are not NULL
    assert(map != NULL);

    // stores oldCap, creates curLink, & sets new tempMap for traversal 
    int oldCap = hashMapCapacity(map);
    HashLink* curLink;
    HashMap* tempMap = hashMapNew(capacity);

    // for loop traverses each index of former map, assigning it to tempMap table
    for (int i = 0; i < oldCap; i++) {
        curLink = map->table[i];
        // traverses the linked list at index to put keys/value in hash table at index
        while (curLink != NULL) {
            hashMapPut(tempMap, curLink->key, curLink->value);
            curLink = curLink->next;
        }
    }

    // cleans up previous map & assigns all the map values accordingly
    hashMapCleanUp(map);
    map->size = tempMap->size;
    map->table = tempMap->table;
    map->capacity = tempMap->capacity;

    // cleans up the temp values
    tempMap->table = NULL;
    free(tempMap);
}

/**
 * Updates the given key-value pair in the hash table. If a link with the given
 * key already exists, this will just update the value and skip traversing. Otherwise, it will
 * create a new link with the given key and value and add it to the table
 * bucket's linked list. You can use hashLinkNew to create the link.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 * 
 * @param map
 * @param key
 * @param value
 */
void hashMapPut(HashMap* map, const char* key, int value)
{
    // checks that map & key are valid
    assert(map != NULL && key!= NULL);

    // resizes table if we've already reached the table load
    if (hashMapTableLoad(map) >= MAX_TABLE_LOAD)
        resizeTable(map, 2*map->capacity);

    // sets up the index value based on key
    int index = HASH_FUNCTION(key) % hashMapCapacity(map);
    if (index < 0) {
        index += hashMapCapacity(map);
    }

    // in the case that the key already exists
    if (hashMapContainsKey(map, key)) {
        int* ptrVal = hashMapGet(map, key);
        (*ptrVal) += value;
    }

    // otherwise
    else {
        // creates new link to be added sans next ptr then checks it isn't NULL
        HashLink* newLink = hashLinkNew(key, value, NULL);
        assert(newLink != NULL);

        // case where the index bucket is empty
        if (map->table[index] == NULL)
            map->table[index] = newLink;
        // otherwise
        else {
            // create curLink for traversing LL in bucket
            HashLink* curLink = map->table[index];
            // traverses until it hits the last link
            while (curLink->next != NULL)
                curLink = curLink->next;
            curLink->next = newLink;
        }

        // adds to map size
        map->size++;
    }
}

/**
 * Removes and frees the link with the given key from the table. If no such link
 * exists, this does nothing. Remember to search the entire linked list at the
 * bucket. You can use hashLinkDelete to free the link.
 * @param map
 * @param key
 */
void hashMapRemove(HashMap* map, const char* key)
{
    // checks that map & key aren't NULL
    assert(map != NULL && key != NULL);

    // sets up links & index for while loop
    int index = HASH_FUNCTION(key) % hashMapCapacity(map);
    HashLink* curLink = map->table[index];
    HashLink* prevLink = map->table[index];

    // while loop to traverse linked list at index
    while (curLink != NULL) {
        // case for when key is found
        if (strcmp(curLink->key,key) == 0) {
            // case for when link to remove is first link
            if (curLink == map->table[index])
                map->table[index] = curLink->next;
            // link to remove isn't first link
            else
                prevLink->next = curLink->next;
            hashLinkDelete(curLink);
            map->size--;
            curLink = NULL;
        }
        // case for when key isn't found
        else {
            prevLink = curLink;
            curLink = curLink->next;
        }
    }
}

/**
 * Returns 1 if a link with the given key is in the table and 0 otherwise.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 * 
 * @param map
 * @param key
 * @return 1 if the key is found, 0 otherwise.
 */
int hashMapContainsKey(HashMap* map, const char* key)
{
    // checks that map & key aren't NULL
    assert(map != NULL && key != NULL);

    // initializes curLink & index used in while loop
    int index = HASH_FUNCTION(key) % hashMapCapacity(map);
    HashLink* curLink = map->table[index];

    // while loop to search each value of linked list at index until NULL is encountered
    while (curLink != NULL) {
        // if keys are equal return 1
        if (strcmp(curLink->key, key) == 0) {
            return 1;
        }
        // go on to next vaue if they are not equal
        curLink = curLink->next;
    }

    // returns 0 if key is not found
    return 0;
}

/**
 * Returns the number of links in the table.
 * @param map
 * @return Number of links in the table.
 */
int hashMapSize(HashMap* map)
{
    // checks that map isn't NULL
    assert(map != NULL);
    
    // returns size
    return map->size;
}

/**
 * Returns the number of buckets in the table.
 * @param map
 * @return Number of buckets in the table.
 */
int hashMapCapacity(HashMap* map)
{
    // checks that map isn't NULL
    assert(map != NULL);

    // returns capacity
    return map->capacity;
}

/**
 * Returns the number of table buckets without any links.
 * @param map
 * @return Number of empty buckets.
 */
int hashMapEmptyBuckets(HashMap* map)
{
    // checks that map is valid
    assert (map != NULL);

    // initializes emptyCt & cap used in for loop
    int emptyCt = 0;
    int mapCap = hashMapCapacity(map);

    // for loop to find each NULL bucket
    for (int i = 0; i < mapCap; i++) {
        if (map->table[i] == NULL) {
            emptyCt++;
        }
    }

    // returns emptyCt
    return emptyCt;
}

/**
 * Returns the ratio of (number of links) / (number of buckets) in the table.
 * Remember that the buckets are linked lists, so this ratio tells you nothing
 * about the number of empty buckets. Remember also that the load is a floating
 * point number, so don't do integer division.
 * @param map
 * @return Table load.
 */
float hashMapTableLoad(HashMap* map)
{
    // checks that map isn't NULL
    assert(map != NULL);

    // returns ratio of tableLoad
    return (float)hashMapSize(map) / (float)hashMapCapacity(map);
}

/**
 * Prints all the links in each of the buckets in the table.
 * @param map
 */
void hashMapPrint(HashMap* map)
{
    for (int i = 0; i < map->capacity; i++)
    {
        HashLink* link = map->table[i];
        if (link != NULL)
        {
            printf("\nBucket %i ->", i);
            while (link != NULL)
            {
                printf(" (%s, %d) ->", link->key, link->value);
                link = link->next;
            }
        }
    }
    printf("\n");
}