#ifndef UTIL
#define UTIL

#include <stdbool.h>

// P2
int harness_get_alloc(int level);
int harness_set_alloc(int level, int new_allocation);

// P1
int harness_get_tag(int pid);
int harness_set_tag(int pid, int new_tag);

bool drop_privileges();

bool re_elevate_privileges();

#endif  // UTIL