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

 
Suite* list_tests_suite(void) {
    Suite* s = suite_create("List Tests");

    /* Core test case */
    TCase* tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_list_create);
    tcase_add_test(tc_core, test_list_size);
    tcase_add_test(tc_core, test_list_index_of);
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
