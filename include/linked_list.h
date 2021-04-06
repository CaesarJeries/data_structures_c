#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__


typedef struct __linked_list LinkedList;

typedef void* (*copy_func_t)(const void* element);
typedef void (*free_func_t)(void* element);
typedef int (*cmp_func_t)(const void* first, const void* second);

typedef enum {
    LINKED_LIST_SUCCESS,
    LINKED_LIST_MEM_ERROR

} LinkedListStatus;


LinkedList* linkedListCreate(copy_func_t copy_func, free_func_t free_func, cmp_func_t compare_func);
void linkedListDestroy(LinkedList* list);

LinkedList* linkedListClone(const LinkedList* list);

size_t linkedListSize(const LinkedList* list);
ssize_t linkedListIndexOf(const LinkedList* list, const void* element);

void* linkedListGetAt(const LinkedList* list, size_t index);
void* linkedListRemoveAt(LinkedList* list, size_t index);

LinkedListStatus linkedListInsertBefore(LinkedList* list, void* anchor, const void* new_element);
LinkedListStatus linkedListInsertAfter(LinkedList* list, void* anchor, const void* new_element);

LinkedListStatus linkedListPush(LinkedList* list, void* element);
void* linkedListPop(LinkedList* list, LinkedListStatus* status);

LinkedListStatus linkedListPushFront(LinkedList* list, void* element);
void* linkedListPopFront(LinkedList* list, LinkedListStatus* status);


#endif // __LINKED_LIST_H__
