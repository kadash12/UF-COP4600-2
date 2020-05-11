# P2 System Call Tester

This tool will test P1 for these things:

- Any process that does not have a parent shall have a tag of 0x00000000.
- All child processes shall inherit the tag of their parent process (all 32 bits of it).
- A process running as the superuser may read and write the tag of any process (all 32 bits of it, but it still
cannot set the MSB to 1).
- A user process has read-only access to the tag of any process.
- A user process may decrease its own level, but not increase it.
- A user process may reset a bit in its tag's bitmap to zero but not set a bit.

This tool will check P2 systemcalls for these things:

- Initial allocation of 10 ms. for each level
- Allocation can only be changed by a process with "root" "access.
- Allocation must be non-negative and must not be under 5ms.
- For both functions, level must be between 0 and 3

This tool will not check the scheduling behavior. It is upto you to test your scheduling behavior using your own tests.

This tool will not check if the manpage were installed successfully. Ensure that you install the manpages into the correct locations and that they are formatted properly!

It uses the library functions, not the harness functions.
Therefore it will not test your harness functions!
Ensure that they work before submitting P2!

Inside the util.h/util.c files in this folder, there are harness_get_tag and harness_set_tag functions defined. These functions should return the same value as get_tag and set_tag respectively, but are implemented using the harness functions. This is provided to make it clear how the harness functions will be used.

## Compile

To compile, you'll first need to add your tags folder into this folder.

You will then have:

- p2_student_test (folder this file is in)
    - tags (your folder)
    - README.md (this file)
    - other testing files

Once all correct, run `make` in this folder!

Note: this tester is expecting that the Makefile in the tags folder is present and is functional!

If this tester fails to compile, check your Makefile!

## Tester Usage

This CLI tester can be used by running `sudo ./p2_student_test` in this folder.

It runs automated tests and will output the results of the tests, and errors if present.
