#include <check.h>
#include <stdlib.h>
#include <string.h>

#include "linked_list.h"

static void* str_copy(const void* src) {
    size_t length = strlen(src);

    char* dest = malloc(length + 1);
    if (dest) {
        strcpy(dest, src);
    }

    return dest;
}

static void str_free(void* s) {
    free(s);
}

static int str_cmp(const void* first, const void* second) {
    return strcmp(first, second);
}

 
START_TEST(test_list_create) {
    LinkedList* list = linkedListCreate(str_copy, str_free, str_cmp);

    ck_assert_uint_eq(linkedListSize(list), 0);

    linkedListDestroy(list);
}
END_TEST

START_TEST(test_list_size) {
    LinkedList* list = linkedListCreate(str_copy, str_free, str_cmp);

    ck_assert_uint_eq(linkedListSize(list), 0);
    
    linkedListPush(list, "AAA");
    ck_assert_uint_eq(linkedListSize(list), 1);
    
    linkedListPush(list, "BBB");
    ck_assert_uint_eq(linkedListSize(list), 2);

    linkedListDestroy(list);
}
END_TEST


START_TEST(test_list_index_of) {
    LinkedList* list = linkedListCreate(str_copy, str_free, str_cmp);

    ck_assert_uint_eq(linkedListIndexOf(list, "AAAA"), -1);

    linkedListPush(list, "AAA");
    linkedListPush(list, "BBB");

    ck_assert_uint_eq(linkedListIndexOf(list, "AAA"), 0);
    ck_assert_uint_eq(linkedListIndexOf(list, "BBB"), 1);
    ck_assert_uint_eq(linkedListIndexOf(list, "Non-existent"), -1);

    linkedListDestroy(list);
}
END_TEST

START_TEST(test_list_get_at) {
    LinkedList* list = linkedListCreate(str_copy, str_free, str_cmp);

    ck_assert_ptr_null(linkedListGetAt(list, 0));
    ck_assert_ptr_null(linkedListGetAt(list, 1));

    linkedListPush(list, "AAA");
    linkedListPush(list, "BBB");

    ck_assert_str_eq(linkedListGetAt(list, 0), "AAA");
    ck_assert_str_eq(linkedListGetAt(list, 1), "BBB");
    ck_assert_ptr_null(linkedListGetAt(list, 2));

    linkedListDestroy(list);
}
END_TEST

START_TEST(test_list_remove_at) {
    LinkedList* list = linkedListCreate(str_copy, str_free, str_cmp);

    ck_assert_ptr_null(linkedListRemoveAt(list, 0));
    ck_assert_ptr_null(linkedListRemoveAt(list, 23));

    linkedListPush(list, "AAA");

    char* s = linkedListRemoveAt(list, 0);

    ck_assert_uint_eq(linkedListSize(list), 0);

    ck_assert_str_eq(s, "AAA");
    free(s); s = NULL;

    linkedListPush(list, "AAA");
    linkedListPush(list, "BBB");
    linkedListPush(list, "CCC");

    s = linkedListRemoveAt(list, 1);
    ck_assert_str_eq(s, "BBB");
    free(s); s = NULL;

    ck_assert_str_eq(linkedListGetAt(list, 0), "AAA");
    ck_assert_str_eq(linkedListGetAt(list, 1), "CCC");
    ck_assert_ptr_null(linkedListGetAt(list, 2));
    
    s = linkedListRemoveAt(list, 1);
    ck_assert_str_eq(s, "CCC");
    free(s); s = NULL;

    ck_assert_str_eq(linkedListGetAt(list, 0), "AAA");
    ck_assert_ptr_null(linkedListGetAt(list, 1));
    ck_assert_ptr_null(linkedListGetAt(list, 2));

    linkedListDestroy(list);
}
END_TEST

START_TEST(test_list_push) {
    LinkedList* list = linkedListCreate(str_copy, str_free, str_cmp);

    ck_assert_int_eq(linkedListPush(list, "AAA"), LINKED_LIST_SUCCESS);
    ck_assert_uint_eq(linkedListSize(list), 1);
    ck_assert_str_eq(linkedListGetAt(list, 0), "AAA");

    linkedListPush(list, "BBB");
    ck_assert_uint_eq(linkedListSize(list), 2);
    ck_assert_str_eq(linkedListGetAt(list, 0), "AAA");
    ck_assert_str_eq(linkedListGetAt(list, 1), "BBB");
    
    linkedListPush(list, "CCC");
    ck_assert_uint_eq(linkedListSize(list), 3);
    ck_assert_str_eq(linkedListGetAt(list, 0), "AAA");
    ck_assert_str_eq(linkedListGetAt(list, 1), "BBB");
    ck_assert_str_eq(linkedListGetAt(list, 2), "CCC");

    linkedListDestroy(list);
}
END_TEST

START_TEST(test_list_pop) {
    LinkedList* list = linkedListCreate(str_copy, str_free, str_cmp);

    linkedListPush(list, "AAA");
    linkedListPush(list, "BBB");
    linkedListPush(list, "CCC");

    char* s = linkedListPop(list);
    ck_assert_str_eq(s, "CCC");
    free(s); s = NULL;
    ck_assert_uint_eq(linkedListSize(list), 2);
    
    s = linkedListPop(list);
    ck_assert_str_eq(s, "BBB");
    free(s); s = NULL;
    ck_assert_uint_eq(linkedListSize(list), 1);

    s = linkedListPop(list);
    ck_assert_str_eq(s, "AAA");
    free(s); s = NULL;
    ck_assert_uint_eq(linkedListSize(list), 0);

    ck_assert_ptr_null(linkedListPop(list));

    linkedListDestroy(list);
}
END_TEST
 
START_TEST(test_list_push_front) {
    LinkedList* list = linkedListCreate(str_copy, str_free, str_cmp);

    ck_assert_int_eq(linkedListPushFront(list, "AAA"), LINKED_LIST_SUCCESS);
    ck_assert_uint_eq(linkedListSize(list), 1);
    ck_assert_str_eq(linkedListGetAt(list, 0), "AAA");

    linkedListPushFront(list, "BBB");
    ck_assert_uint_eq(linkedListSize(list), 2);
    ck_assert_str_eq(linkedListGetAt(list, 1), "AAA");
    ck_assert_str_eq(linkedListGetAt(list, 0), "BBB");
    
    linkedListPushFront(list, "CCC");
    ck_assert_uint_eq(linkedListSize(list), 3);
    ck_assert_str_eq(linkedListGetAt(list, 2), "AAA");
    ck_assert_str_eq(linkedListGetAt(list, 1), "BBB");
    ck_assert_str_eq(linkedListGetAt(list, 0), "CCC");

    linkedListDestroy(list);
}
END_TEST

START_TEST(test_list_pop_front) {
    LinkedList* list = linkedListCreate(str_copy, str_free, str_cmp);

    linkedListPush(list, "AAA");
    linkedListPush(list, "BBB");
    linkedListPush(list, "CCC");

    char* s = linkedListPopFront(list);
    ck_assert_str_eq(s, "AAA");
    free(s); s = NULL;
    ck_assert_uint_eq(linkedListSize(list), 2);
    
    s = linkedListPopFront(list);
    ck_assert_str_eq(s, "BBB");
    free(s); s = NULL;
    ck_assert_uint_eq(linkedListSize(list), 1);

    s = linkedListPopFront(list);
    ck_assert_str_eq(s, "CCC");
    free(s); s = NULL;
    ck_assert_uint_eq(linkedListSize(list), 0);

    ck_assert_ptr_null(linkedListPopFront(list));

    linkedListDestroy(list);
}
END_TEST
Suite* list_tests_suite(void) {
    Suite* s = suite_create("List Tests");

    /* Core test case */
    TCase* tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_list_create);
    tcase_add_test(tc_core, test_list_size);
    tcase_add_test(tc_core, test_list_index_of);
    tcase_add_test(tc_core, test_list_get_at);
    tcase_add_test(tc_core, test_list_remove_at);
    tcase_add_test(tc_core, test_list_push);
    tcase_add_test(tc_core, test_list_pop);
    tcase_add_test(tc_core, test_list_push_front);
    tcase_add_test(tc_core, test_list_pop_front);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void) {
    Suite* s = list_tests_suite();
    SRunner* sr = srunner_create(s);

    srunner_run_all(sr, CK_VERBOSE);
    
    int num_failures = srunner_ntests_failed(sr);
    
    srunner_free(sr);
    
    return (num_failures == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
