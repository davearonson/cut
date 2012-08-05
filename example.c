/* example of how to use cut */

#include <cut.h>

#include <stdio.h>
#include <stdlib.h>


void
cut_test_foo()
{
    cut_DblLT (CUT_FAIL_CONT, 1.0, 1.1);
    cut_set_quiet (0);
    cut_IntEQ_M (CUT_FAIL_OK, 1, 0, "This is %c test", 'a');
    cut_IntGE (CUT_FAIL_RETURN, -2, -5);
    cut_IntEQ (CUT_FAIL_ABORT, 3, 0);
}


void
cut_test_bar()
{
    cut_StrGE_M (CUT_FAIL_IGNORE, "foo", "Bar", "This is %c test", 'b');
    cut_IntEQ (CUT_FAIL_ABORT, 3, 0);
    cut_IntEQ (CUT_FAIL_OK, 4, 0);
}


int
main (int argc, char *argv[])
{
    cut_set_quiet (1);
    cut_test_foo();
    cut_test_bar();
    cut_give_count();
    return cut_failures;
}
