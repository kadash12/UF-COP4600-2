#pragma GCC diagnostic ignored "-Woverflow"

#include "tests.h"

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
// other helper functions
#include "util.h"

// project includes (files from your tags folder)
#include "tags/harness.h"
#include "tags/tags.h"

void test_status_print(bool test_status) {
    if (test_status)
        printf("PASS\n\n");
    else
        printf("FAIL\n\n");
}

bool check_test_status(int pid_to_modify, int new_tag) {
    bool error = false;

    int old_tag = get_tag(pid_to_modify);

    int set_tag_ret = set_tag(pid_to_modify, new_tag);

    bool valid = is_set_valid(pid_to_modify, old_tag, new_tag);

    int get_tag_ret = get_tag(pid_to_modify);

    if (valid) {
        if (set_tag_ret == -1) {
            error = true;
            printf(
                "ERROR : set_tag systemcall failed (returned -1) when it "
                "should have passed.\n");
        }

        if (get_tag_ret != new_tag) {
            error = true;
            printf("ERROR : either get_tag failed or set_tag failed.\n");
        }

    } else {
        if (set_tag_ret != -1) {
            error = true;
            printf("ERROR : set_tag systemcall invalid result.\n");
        }

        if (old_tag != new_tag) {
            if (get_tag_ret != old_tag) {
                error = true;
                printf(
                    "ERROR : either set_tag set a tag when not allowed to, "
                    "or "
                    "get_tag failed.\n");
            }
        }
    }

    return !error;
}

bool test_1() {
    printf(
        "TESTING : Any process that does not have a parent shall have a tag of "
        "0x00000000.\n");

    bool test_status = true;

    test_status = get_tag(1) == 0;

    test_status_print(test_status);
    return test_status;
}

bool test_2() {
    printf(
        "TESTING : All child processes shall inherit the tag of their parent "
        "process (all 32 bits of it).\n");

    bool test_status = true;

    int current_pid = getpid();

    if (!re_elevate_privileges())
        printf("SEVERE_RUNTIME_FAILURE : re-elevate permissions failed.\n");

    int tag = 4600;
    int set_tag_ret = set_tag(current_pid, tag);
    int child_pid = fork();
    test_status = set_tag_ret != -1 && get_tag(child_pid) == tag;

    kill(child_pid, SIGKILL);

    test_status_print(test_status);
    return test_status;
}

bool test_3() {
    printf(
        "TESTING : A user process has read-only access to the tag of any "
        "process.\n");

    bool test_status = true;
    bool set_valid = false;

    if (!drop_privileges())
        printf("SEVERE_RUNTIME_FAILURE : drop permissions failed.\n");

    int child_pid = fork();

    int old_tag = get_tag(child_pid);
    int new_tag = 0;

    test_status = check_test_status(child_pid, new_tag) && test_status;

    kill(child_pid, SIGKILL);

    test_status_print(test_status);
    return test_status;
}

bool test_4() {
    printf(
        "TESTING : A process running as the superuser may read and write the "
        "tag of any process (all 32 bits of it, but it still cannot set the "
        "MSB to 1).\n");

    bool test_status = true;

    if (!re_elevate_privileges())
        printf("SEVERE_RUNTIME_FAILURE : re-elevate permissions failed.\n");

    int child_pid = fork();

    int new_tag = 4600;
    test_status = check_test_status(child_pid, new_tag);

    new_tag = INT_MAX + 1;
    test_status = check_test_status(child_pid, new_tag) && test_status;

    kill(child_pid, SIGKILL);

    test_status_print(test_status);
    return test_status;
}

bool test_5() {
    printf(
        "TESTING: A user process may decrease its own level, but not increase "
        "it.\n");

    bool test_status = true;

    int current_pid = getpid();

    if (!re_elevate_privileges())
        printf("SEVERE_RUNTIME_FAILURE : re-elevate permissions failed.\n");

    int new_tag = 0b011;
    test_status = check_test_status(current_pid, new_tag);

    if (!drop_privileges())
        printf("SEVERE_RUNTIME_FAILURE : drop permissions failed.\n");

    new_tag = 0b001;
    test_status = check_test_status(current_pid, new_tag) && test_status;

    new_tag = 0b101;
    test_status = check_test_status(current_pid, new_tag) && test_status;

    new_tag = 0b011;
    test_status = check_test_status(current_pid, new_tag) && test_status;

    test_status_print(test_status);
    return test_status;
}

bool test_6() {
    printf(
        "TESTING : A user process may reset a bit in its tag's bitmap to zero "
        "but not set a bit.\n");

    bool test_status = true;

    int current_pid = getpid();

    if (!re_elevate_privileges())
        printf("SEVERE_RUNTIME_FAILURE : re-elevate permissions failed.\n");

    int new_tag = 0b1100;
    test_status = check_test_status(current_pid, new_tag);

    if (!drop_privileges())
        printf("SEVERE_RUNTIME_FAILURE : drop permissions failed.\n");

    new_tag = 0b1000;
    test_status = check_test_status(current_pid, new_tag) && test_status;

    new_tag = 0b1001;
    test_status = check_test_status(current_pid, new_tag) && test_status;

    new_tag = 0b0000;
    test_status = check_test_status(current_pid, new_tag) && test_status;

    new_tag = 0b1100;
    test_status = check_test_status(current_pid, new_tag) && test_status;

    test_status_print(test_status);
    return test_status;
}

// P2 Tests start here

bool test_7() {
    printf("TESTING : Initial allocation of 10 ms. for each level.\n");
    bool stat = true;
    for (unsigned int i = 0; i <= 3; i++) {
        int tmp = get_alloc(i);
        if (tmp != 10) {
            printf("ERROR : Initial allocation for level %d is not 10ms\n", i);
            stat = false;
        }
    }
    test_status_print(stat);
    return stat;
}

bool test_8() {
    printf(
        "TESTING : Allocation can only be changed by a process with root "
        "access.\n");

    bool stat = true;

    if (!drop_privileges())
        printf("SEVERE_RUNTIME_FAILURE : drop permissions failed.\n");

    int old_alloc_time = get_alloc(0);

    int val = set_alloc(0, 1000);

    if (val != -1) {
        stat = false;
        printf("ERROR : set_alloc should return -1 if non root user\n");
    }

    int new_alloc_time = get_alloc(0);
    if (old_alloc_time != new_alloc_time) {
        stat = false;
        printf(
            "ERROR : set_alloc changed allocation time when not running as "
            "root\n");
    }

    if (!re_elevate_privileges())
        printf("SEVERE_RUNTIME_FAILURE : re-elevate permissions failed.\n");

    set_alloc(0, 100);
    old_alloc_time = get_alloc(0);

    val = set_alloc(0, 1337);

    if (val != 1337) {
        stat = false;
        printf("ERROR : set_alloc should return new_allocation on success\n");
    }

    new_alloc_time = get_alloc(0);
    if (old_alloc_time == new_alloc_time || new_alloc_time != 1337) {
        stat = false;
        printf(
            "ERROR : set_alloc did not change allocation_time when "
            "running as "
            "root\n");
    }

    test_status_print(stat);
    return stat;
}

int get_alloc_sum() {
    int acc = 0;
    for (unsigned int i = 0; i <= 3; i++) {
        acc += get_alloc(i);
    }
    return acc;
}

bool test_9() {
    printf(
        "TESTING : Sum of allocations must be non-negative and must not be "
        "under 5ms. "
        "\n");

    bool stat = true;

    if (!re_elevate_privileges())
        printf("SEVERE_RUNTIME_FAILURE : re-elevate permissions failed.\n");

    // Ensure that overall cycle time >= 5ms before running test
    set_alloc(1, 5);

    for (int i = -10; i <= 20; i++) {
        int val = set_alloc(0, i);
        if (i < 0) {
            if (val != -1) {
                stat = false;
                printf(
                    "ERROR : set_alloc should fail when allocation is "
                    "negative. \n");
                break;
            }
        } else if (val == -1) {
            stat = false;
            printf(
                "ERROR : set_alloc should succeed when allocation is "
                "positive. \n");
            break;
        }
    }

    //

    set_alloc(0, 3);
    set_alloc(1, 2);
    set_alloc(2, 0);
    set_alloc(3, 0);

    if (set_alloc(1, 1) != -1) {
        stat = false;
        printf(
            "ERROR : set_alloc should fail when sum of allocation time < 5 "
            "ms.\n");
    }

    if (set_alloc(1, 4) == -1) {
        stat = false;
        printf("ERROR : Set alloc fails when it should succeed.\n");
    }

    if (set_alloc(0, 0) != -1) {
        stat = false;
        printf(
            "ERROR : set_alloc should fail when sum of allocation time < 5 "
            "ms.\n");
    }

    if (set_alloc(0, 1) == -1) {
        stat = false;
        printf("ERROR : Set alloc fails when it should succeed.\n");
    }

    //

    set_alloc(2, 3);
    set_alloc(3, 2);
    set_alloc(0, 0);
    set_alloc(1, 0);

    if (set_alloc(3, 1) != -1) {
        stat = false;
        printf(
            "ERROR : set_alloc should fail when sum of allocation time < 5 "
            "ms.\n");
    }

    if (set_alloc(3, 4) == -1) {
        stat = false;
        printf("ERROR : Set alloc fails when it should succeed.\n");
    }

    if (set_alloc(2, 0) != -1) {
        stat = false;
        printf(
            "ERROR : set_alloc should fail when sum of allocation time < 5 "
            "ms.\n");
    }

    if (set_alloc(2, 1) == -1) {
        stat = false;
        printf("ERROR : Set alloc fails when it should succeed.\n");
    }

    test_status_print(stat);
    return stat;
}

bool test_10() {
    printf("TESTING : For both functions, level must be between 0 and 3 \n");

    bool stat = true;

    if (!re_elevate_privileges())
        printf("SEVERE_RUNTIME_FAILURE : re-elevate permissions failed.\n");
    int val;
    int new_alloc_time;

    for (int i = -10; i <= 10; i++) {
        val = get_alloc(i);
        if (i >= 0 && i <= 3) {
            if (val == -1) {
                stat = false;
                printf("ERROR : get_alloc should work with level %d\n", i);
            }
        } else {
            if (val != -1) {
                stat = false;
                printf("ERROR : get_alloc should return -1 with level %d\n", i);
            }
        }
    }

    for (int i = -10; i <= 10; i++) {
        val = set_alloc(i, 50);
        if (i >= 0 && i <= 3) {
            int new_alloc_time = get_alloc(i);
            if (val != new_alloc_time || val != 50) {
                stat = false;
                printf("ERROR : set_alloc should work with level %d\n", i);
            }
        } else {
            if (val != -1) {
                stat = false;
                printf("ERROR : set_alloc should return -1 with level %d\n", i);
            }
        }
    }

    test_status_print(stat);
    return stat;
}
