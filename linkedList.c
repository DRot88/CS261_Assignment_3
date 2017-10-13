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
	// FIXME: you must write this
	list->frontSentinel = malloc(sizeof(struct Link));
	assert(list->frontSentinel != 0);
	list->backSentinel = malloc(sizeof(struct Link));
	assert(list->backSentinel != 0);
	list->frontSentinel->next = list->backSentinel;
	list->frontSentinel->prev = NULL;
	list->backSentinel->prev = list->frontSentinel;
	list->backSentinel->next = NULL;
	list->size = 0;
}

/**
 * Adds a new link with the given value before the given link and
 * increments the list's size.
 */
static void addLinkBefore(struct LinkedList* list, struct Link* link, TYPE value)
{
	// FIXME: you must write this
	struct Link *newLink = malloc(sizeof(struct Link));
	assert(newLink != 0);

	newLink->value = value;				/* set value of new link */
	newLink->next = link;					/* newlink->next is now the link we want to add before */
	newLink->prev = link->prev;		/* new link previous is current links previous */
	link->prev->next = newLink;		/* old link previous->next now points to new link */
	link->prev = newLink;					/* old link previous points to new link */

	list->size++;									/* increase size of linked list */
}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct LinkedList* list, struct Link* link)
{
	// FIXME: you must write this		/* FOR EXAMPLE REFERENCE: Links 1-2-3, removing link 2 */
	link->prev->next = link->next;	/* 2->prev(1)->next now points to (3) */
	link->next->prev = link->prev;	/* 2->next(3)->prev now points to (1) */

	free(link);											/* remove link (2) */
	link = 0;												/* set link to null */
	list->size--;										/* decrement size */

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
	// FIXME: you must write this
	addLinkBefore(list, list->frontSentinel->next, value); /* add link to before first value pointed by sentinel */

}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void linkedListAddBack(struct LinkedList* list, TYPE value)
{
	// FIXME: you must write this
	addLinkBefore(list, list->backSentinel, value);
}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE linkedListFront(struct LinkedList* list)
{
	// FIXME: you must write this
	assert(!linkedListIsEmpty(list));
	return list->frontSentinel->next->value;
}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE linkedListBack(struct LinkedList* list)
{
	// FIXME: you must write this
	assert(!linkedListIsEmpty(list));
	return list->backSentinel->prev->value;
}

/**
 * Removes the link at the front of the deque.
 */
void linkedListRemoveFront(struct LinkedList* list)
{
	// FIXME: you must write this
	assert(!linkedListIsEmpty(list));
	removeLink(list, list->frontSentinel->next);
}

/**
 * Removes the link at the back of the deque.
 */
void linkedListRemoveBack(struct LinkedList* list)
{
	// FIXME: you must write this
	assert(!linkedListIsEmpty(list));
	removeLink(list, list->backSentinel->prev);	
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int linkedListIsEmpty(struct LinkedList* list)
{
	// FIXME: you must write this
	if (list->size == 0)
	{
		return 1;
	}

	return 0;
}

/**
 * Prints the values of the links in the deque from front to back.
 */
void linkedListPrint(struct LinkedList* list)
{
	// FIXME: you must write this
	struct Link *temp = malloc(sizeof(struct Link));
	assert (temp != 0);

	temp = list->frontSentinel->next;

	while (temp->next != 0) {
		printf("%d", temp->value);
		temp = temp->next;
		if (temp->next != 0) {
			printf("->");
		} else {
			printf("\n");
		}
	}

}

/**
 * Adds a link with the given value to the bag.
 */
void linkedListAdd(struct LinkedList* list, TYPE value)
{
	// FIXME: you must write this
	addLinkBefore(list, list->frontSentinel->next, value);

}

/**
 * Returns 1 if a link with the value is in the bag and 0 otherwise.
 */
int linkedListContains(struct LinkedList* list, TYPE value)
{
	// FIXME: you must write this
	struct Link *searchVal = malloc(sizeof(struct Link));
	assert (searchVal != 0);

	searchVal = list->frontSentinel->next;
	while(searchVal->next != 0) {
		if (EQ(searchVal->value, value)) {
			printf("Value %d found in the list!\n", value);
			return 1;
		}
		searchVal = searchVal->next;
	}
	printf("Value %d not found in the list!\n", value);
	return 0;
}

/**
 * Removes the first occurrence of a link with the given value.
 */
void linkedListRemove(struct LinkedList* list, TYPE value)
{
	// FIXME: you must write this
	assert(!linkedListIsEmpty(list));
	if(linkedListContains(list, value)) {
		printf("Removing value %d from the list!\n", value);
		struct Link *linkToRemove = malloc(sizeof(struct Link));
		assert (linkToRemove != 0);
		linkToRemove = list->frontSentinel->next;
		while(linkToRemove->value != value) {
			linkToRemove = linkToRemove->next;
		}
		removeLink(list, linkToRemove);
	}
}
