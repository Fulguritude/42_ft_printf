# 42_ft_printf

ft_printf: homemade printf for 42.

Tests provided require only knowledge of C, unlike many ft_printf test suites.
Check tests/main_asprintf.c to see tests, more info is given there.
Tests are filterable with macros provided in the main file.

The file tests/main_asprintf_caps.c runs tests for capitalized type specifiers.
Note that since D, O and U are non-standard, the test suite for capitalized
input is untrustworthy for ints. It functions for floats though.

Check the makefile for more ease of use.

Note that printing debug lines within your own ft_printf or the regular
printf will not make the tests fail, which is the main interest of this test
suite.

Tidbits concerning how to build your own printf have been sprinkled here and
there throughout the code.
