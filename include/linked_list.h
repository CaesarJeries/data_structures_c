#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

#include <stddef.h> // size_t, ssize_t

typedef struct __linked_list LinkedList;

/*
A generic linked list.
Elements are stored by value (copied using the copy function passed at list creation)
Elements are compared using the compare function passed at list creation.
Elements are freed using the free function passed at list creation.
*/

typedef void* (*copy_func_t)(const void* element);
typedef void (*free_func_t)(void* element);
typedef int (*cmp_func_t)(const void* first, const void* second);

typedef enum {
    LINKED_LIST_SUCCESS,
    LINKED_LIST_MEM_ERROR

} LinkedListStatus;

// create a new empty linked list
LinkedList* linkedListCreate(copy_func_t copy_func, free_func_t free_func, cmp_func_t compare_func);

// free all memory associated with the list (including elements)
void linkedListDestroy(LinkedList* list);

// deep clone a list
LinkedList* linkedListClone(const LinkedList* list);

// get list size (number of elements in the list)
size_t linkedListSize(const LinkedList* list);

// get index of a given element. return -1 if `element` is not found
ssize_t linkedListIndexOf(const LinkedList* list, const void* element);

// returns a pointer to the element located at `index`
void* linkedListGetAt(const LinkedList* list, size_t index);

// unlinks the element located at `index` from the list, and returns its address
// it's the user's responsibility is to free the memory address.
void* linkedListRemoveAt(LinkedList* list, size_t index);

// add/remove an element to/from the end/front of the list
// the pop functions remove the element from the list, and return
// its address. it's the user's responsibility to free the memory block
// associated with the element's address
LinkedListStatus linkedListPush(LinkedList* list, const void* element);
void* linkedListPop(LinkedList* list);
LinkedListStatus linkedListPushFront(LinkedList* list, void* element);
void* linkedListPopFront(LinkedList* list);


// a function that prints a string representation of the given element
typedef void (*print_func_t)(const void*);

void linkedListPrint(const LinkedList* list, print_func_t print_element);

#endif // __LINKED_LIST_H__
