#define _GNU_SOURCE

#include "util.h"

#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

// project includes (files from your tags folder)
#include "tags/harness.h"

// this is how the get alloc harness functions will be used
int harness_get_alloc(int level) {
    int* get_alloc_params = retrieve_get_alloc_params(level);

    int ret;

    switch (get_alloc_params[1]) {
        case 0:
            ret = syscall(get_alloc_params[0]);
            break;
        case 1:
            ret = syscall(get_alloc_params[0], get_alloc_params[2]);
            break;
        case 2:
            ret = syscall(get_alloc_params[0], get_alloc_params[2],
                          get_alloc_params[3]);
            break;

        default:
            break;
    }

    free(get_alloc_params);

    return interpret_get_alloc_result(ret);
}

// this is how the set alloc harness functions will be used
int harness_set_alloc(int level, int new_allocation) {
    int* set_alloc_params = retrieve_set_alloc_params(level, new_allocation);

    int ret;

    switch (set_alloc_params[1]) {
        case 0:
            ret = syscall(set_alloc_params[0]);
            break;
        case 1:
            ret = syscall(set_alloc_params[0], set_alloc_params[2]);
            break;
        case 2:
            ret = syscall(set_alloc_params[0], set_alloc_params[2],
                          set_alloc_params[3]);
            break;

        default:
            break;
    }

    free(set_alloc_params);

    return interpret_set_alloc_result(ret);
}

// this is how the get tag harness functions will be used
int harness_get_tag(int pid) {
    int* get_tag_params = retrieve_get_tag_params(pid);

    int ret;

    switch (get_tag_params[1]) {
        case 0:
            ret = syscall(get_tag_params[0]);
            break;
        case 1:
            ret = syscall(get_tag_params[0], get_tag_params[2]);
            break;
        case 2:
            ret = syscall(get_tag_params[0], get_tag_params[2],
                          get_tag_params[3]);
            break;

        default:
            break;
    }

    free(get_tag_params);

    return interpret_get_tag_result(ret);
}

// this is how the set tag harness functions will be used
int harness_set_tag(int pid, int new_tag) {
    int* set_tag_params = retrieve_set_tag_params(pid, new_tag);

    int ret;

    switch (set_tag_params[1]) {
        case 0:
            ret = syscall(set_tag_params[0]);
            break;
        case 1:
            ret = syscall(set_tag_params[0], set_tag_params[2]);
            break;
        case 2:
            ret = syscall(set_tag_params[0], set_tag_params[2],
                          set_tag_params[3]);
            break;

        default:
            break;
    }

    free(set_tag_params);

    return interpret_set_tag_result(ret);
}

// if running as superuser this command will change process permission
// level to that of a normal user process
bool drop_privileges() {
    if (setresgid(1000, 1000, 0) == -1 || setresuid(1000, 1000, 0) == -1) {
        /* Failed: no root privileges! */
        return false;
    }
    return true;
}

// if process originally started as superuser, this command will change process
// permission level back to that of the superuser
bool re_elevate_privileges() {
    if (setresgid(0, 0, 0) == -1 || setresuid(0, 0, 0) == -1) {
        /* Failed: no root privileges! */
        return false;
    }
    return true;
}