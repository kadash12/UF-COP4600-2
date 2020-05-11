#include <errno.h>
#include <limits.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

// p1 test utility library
#include "p1_test_util.h"
// tests used in test suite
#include "tests.h"
// other helper functions
#include "util.h"

// project includes (files from your tags folder)
#include "tags/tags.h"

#define PATH_BUF_SIZE 1024

int run_test_suite() {
    printf(
        "This test suite will perform unit tests to check the "
        "correctness of your solution.\n\n");

    int num_tests_p1 = 6;
    int num_tests_p1_passed = 0;

    int num_tests_p2 = 4;
    int num_tests_p2_passed = 0;

    test_1() && ++num_tests_p1_passed;
    test_2() && ++num_tests_p1_passed;
    test_3() && ++num_tests_p1_passed;
    test_4() && ++num_tests_p1_passed;
    test_5() && ++num_tests_p1_passed;
    test_6() && ++num_tests_p1_passed;

    // P2 tests
    test_7() && ++num_tests_p2_passed;
    test_8() && ++num_tests_p2_passed;
    test_9() && ++num_tests_p2_passed;
    test_10() && ++num_tests_p2_passed;

    if (num_tests_p1 == num_tests_p1_passed)
        printf("ALL %d P1 TESTS PASSED\n", num_tests_p1);
    else
        printf("%d P1 TESTS FAILED\n", num_tests_p1 - num_tests_p1_passed);

    if (num_tests_p2 == num_tests_p2_passed)
        printf("ALL %d P2 TESTS PASSED\n", num_tests_p2);
    else
        printf("%d P2 TESTS FAILED\n", num_tests_p2 - num_tests_p2_passed);

    return (num_tests_p1 + num_tests_p2) ==
           (num_tests_p1_passed + num_tests_p2_passed);
}

int test_main(int argc, char** argv) {
    if (argc == 1) {
        printf("Running test suite: ");
        return run_test_suite();
    }
}

int main(int argc, char** argv) {
    if (getuid() != 0 || geteuid() != 0) {
        printf("Attempting to elevate to superuser ...\n\n");
        // get path to executable
        char buf[PATH_BUF_SIZE];
        int path_str_len = readlink("/proc/self/exe", buf, PATH_BUF_SIZE);
        buf[path_str_len] = '\0';
        int argv_len = 0;
        for (unsigned int i = 0; i < argc; i++) {
            argv_len += strlen(argv[i]);
        }
        char path_str[path_str_len + 5 + argv_len + (argc - 1)];
        // concatenate "sudo " with path
        strcpy(path_str, "sudo ");
        strcat(path_str, buf);
        // preserve command line arguments
        for (unsigned int i = 1; i < argc; i++) {
            strcat(path_str, " ");
            strcat(path_str, argv[i]);
        }
        // re-execute
        int ret = system(path_str);
        return ret;
    } else {
        return test_main(argc, argv);
    }
}