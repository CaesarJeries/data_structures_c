#include <assert.h>
#include <malloc.h>

#include "linked_list.h"

typedef struct node {
    void* data;

    struct node* next;
    struct node* prev;

} LinkedListNode;

static LinkedListNode* nodeCreate(void* data) {
    LinkedListNode* new_node = malloc(sizeof(*new_node));
    if (new_node) {
        new_node->data = data;
        new_node->next = new_node->prev = NULL;
    }

    return new_node;
}

static void nodeDestroy(LinkedListNode* node, free_func_t free_func) {
    if (node) {
        if (free_func) free_func(node->data);
        free(node);
    }
}


struct __linked_list {
    LinkedListNode* head;
    LinkedListNode* tail;

    copy_funct_t copy;
    cmp_func_t compare;
    free_func_t free;
};


LinkedList* linkedListCreate(copy_func_t copy_func, free_func_t free_func, cmp_func_t compare_func) {
    assert(copy_func); assert(free_func); assert(compare_func);

    LinkedList* new_list = malloc(sizeof(*new_list));
    if (new_list) {
        new_list->data = NULL;
        
        new_list->head = nodeCreate(NULL);
        if (NULL == new_list->head) {
            linkedListDestroy(new_list);
            return NULL;
        }

        new_list->tail = nodeCreate(NULL);
        if (NULL == new_list->tail) {
            linkedListDestroy(new_list);
            return NULL;
        }

        // both allocations succeeded
        new_list->head->next = new_list->tail;
        new_list->tail->prev = new_list->head;
    }

    return new_list;
}

void linkedListDestroy(LinkedList* list) {
    if (list) {
        LinkedListNode* node_itr = list->head->next;
        while (node_itr != list->tail) {
            LinkedListNode* current = node_itr;
            node_itr = node_itr->next;

            nodeDestroy(current, list->free);
        }
        
        nodeDestroy(list->head, NULL);
        nodeDestroy(list->tail, NULL);

        free(list);
    }
}
