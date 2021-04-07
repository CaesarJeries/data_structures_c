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

    copy_func_t copy;
    cmp_func_t compare;
    free_func_t free;
};


LinkedList* linkedListCreate(copy_func_t copy_func, free_func_t free_func, cmp_func_t compare_func) {
    assert(copy_func); assert(free_func); assert(compare_func);

    LinkedList* new_list = malloc(sizeof(*new_list));
    if (new_list) {
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

LinkedList* linkedListClone(const LinkedList* list) {
    assert(list);

    LinkedList* new_list = linkedListCreate(list->copy, list->free, list->compare);
    if (new_list) {
        LinkedListNode* src_node_itr = list->head->next;
        while (src_node_itr != list->tail) {
            if (LINKED_LIST_SUCCESS != linkedListPush(new_list, src_node_itr->data)) {
                linkedListDestroy(new_list);
                new_list = NULL;
                break;
            }

            src_node_itr = src_node_itr->next;
        }
    }

    return new_list;
}


typedef int (*op_func_t)(void* element, void* params);

static int for_each(LinkedList* list, op_func_t op, void* params) {
    LinkedListNode* node_itr = list->head->next;
    while (node_itr != list->tail) {
        int result = op(node_itr->data, params);

        if (0 != result) {
            return result;
        }

        node_itr = node_itr->next;
    }

    return 0;
}

static int element_counter(void* ignored, void* params) {
    size_t* counter = params;

    ++(*counter);

    return 0;
}

size_t linkedListSize(const LinkedList* list) {
    assert(list);

    size_t count = 0;
    for_each((LinkedList*) list, element_counter, &count);

    return count;
}


typedef struct {
    ssize_t index;
    const void* target_value;
    cmp_func_t compare;

} ElementFinderParams;


static int element_finder(void* element, void* params) {
    ElementFinderParams* param_pack = params;

    if (0 == param_pack->compare(element, param_pack->target_value)) {
        return 1;
    }
    
    ++(param_pack->index);

    return 0;
}

ssize_t linkedListIndexOf(const LinkedList* list, const void* element) {
    assert(list); assert(element);

    ElementFinderParams params = {0, element, list->compare};
    
    int result = for_each((LinkedList*) list, element_finder, &params);
    if (result != 0) {
        return params.index;
    }

    return -1;
}

LinkedListStatus linkedListPush(LinkedList* list, void* element) {
    assert(list);

    void* new_element = list->copy(element);
    if (!new_element) {
        return LINKED_LIST_MEM_ERROR;
    }

    LinkedListNode* new_node = nodeCreate(new_element);
    if (!new_node) {
        list->free(new_element);
        return LINKED_LIST_MEM_ERROR;
    }

    LinkedListNode* before_tail = list->tail->prev;

    before_tail->next = new_node;
    new_node->prev = before_tail;

    list->tail->prev = new_node;
    new_node->next = list->tail;

    return LINKED_LIST_SUCCESS;
}

void* linkedListPop(LinkedList* list) {
    assert(list);

    if (list->head->next == list->tail) {
        // list is empty
        return NULL;
    }

    LinkedListNode* to_delete = list->tail->prev;
    LinkedListNode* before_tail = to_delete->prev;
    void* data = to_delete->data;
    
    to_delete->data = NULL;
    nodeDestroy(to_delete, NULL); to_delete = NULL;

    before_tail->next = list->tail;
    list->tail->prev = before_tail;

   return data; 
}
