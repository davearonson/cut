/*
 * cut_test.c: test suite for cut.c.
 * Omits all Chr, Oct, and Hex ops, as they just change printing.
 * Omits all ops involving NEGATE, as they just negate success/failure.
 * Omits all ops involving STRSWAP, as they just swap which is which.
 * Omits all Ptr ops, as they are just aliases for Hex.
 * Omits all _M ops, as they just add on a message.
 * TODO: test the features mentioned above, that allow omitting so many tests!
 */

#include <cut.h>

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>



#define WANT_FAIL(test, v1, v2)\
do\
{\
    if (! cut__is_quiet()) cut_set_quiet (1);\
    cut_##test (CUT_FAIL_CONT, v1, v2);\
    ++myFails;\
} while (0)



#define WANT_SUCC(test, v1, v2)\
do\
{\
    if (cut__is_quiet()) cut_set_quiet (0);\
    cut_##test(CUT_FAIL_ABORT, v1, v2);\
} while (0);



static unsigned int myFails = 0;
static double       epsilon = 1e-6;



static void check_fails (const char * funcName);
static void test_cut_DblEQ (void);
static void test_cut_DblEQ_helper (double d);
static void test_cut_DblGT (void);
static void test_cut_DblGT_helper (double d);
static void test_cut_DblLT (void);
static void test_cut_DblLT_helper (double d);
static void test_cut_IStrABegE (void);
static void test_cut_IStrAContE (void);
static void test_cut_IStrAEndE (void);
static void test_cut_IStrEQ (void);
static void test_cut_IStrGT (void);
static void test_cut_IStrLT (void);
static void test_cut_IntEQ (void);
static void test_cut_IntGT (void);
static void test_cut_IntLT (void);
static void test_cut_StrABegE (void);
static void test_cut_StrAContE (void);
static void test_cut_StrAEndE (void);
static void test_cut_StrEQ (void);
static void test_cut_StrGT (void);
static void test_cut_StrLT (void);
static void test_cut_UIntEQ (void);
static void test_cut_UIntGT (void);
static void test_cut_UIntLT (void);



int
main (int argc, char *argv[])
{
    cut_set_quiet (1);

    test_cut_DblEQ();
    test_cut_DblGT();
    test_cut_DblLT();
    test_cut_IStrABegE();
    test_cut_IStrAContE();
    test_cut_IStrAEndE();
    test_cut_IStrEQ();
    test_cut_IStrGT();
    test_cut_IStrLT();
    test_cut_IntEQ();
    test_cut_IntGT();
    test_cut_IntLT();
    test_cut_StrABegE();
    test_cut_StrAContE();
    test_cut_StrAEndE();
    test_cut_StrEQ();
    test_cut_StrGT();
    test_cut_StrLT();
    test_cut_UIntEQ();
    test_cut_UIntGT();
    test_cut_UIntLT();
    return 0;  // if we got here we got as many fails as expected
}



static void
check_fails (const char * funcName)
{
    unsigned int tmpCF = cut_failures;
    unsigned int tmpMF = myFails;

    /* reset failures to prevent warning re ignored failures */
    cut_failures = 0;
    myFails = 0;
    cut_set_quiet (0);
    cut_IntEQ_M (CUT_FAIL_ABORT, tmpMF, tmpCF,
                 "Not enough failures in %s", funcName);
    cut_set_quiet (1);
}



static void
test_cut_DblEQ (void)
{
    double  d = 1e-9;
    short   i;

    test_cut_DblEQ_helper (0.0);
    for (i = -9; i <= 9; i += 2)
    {
        test_cut_DblEQ_helper (d);
        test_cut_DblEQ_helper (-d);
        d *= 100;
    }
}



static void
test_cut_DblEQ_helper (double d)
{
    const short NAMELEN = 80;
    char funcName[NAMELEN];

    WANT_SUCC (DblEQ, d, d);

    WANT_FAIL (DblEQ, d, d + epsilon);
    WANT_FAIL (DblEQ, d, d - epsilon);

    snprintf (funcName, NAMELEN, "%s(%.0f)", __func__, d);
    check_fails (funcName);
}



static void
test_cut_DblGT (void)
{
    double  d = 1e-9;
    short   i;

    test_cut_DblGT_helper (0.0);
    for (i = -9; i <= 9; i += 2)
    {
        test_cut_DblGT_helper (d);
        test_cut_DblGT_helper (-d);
        d *= 100;
    }
}



static void
test_cut_DblGT_helper (double d)
{
    const short NAMELEN = 80;
    char funcName[NAMELEN];

    WANT_SUCC (DblGT, d,           d + epsilon);
    WANT_SUCC (DblGT, d - epsilon, d);

    WANT_FAIL (DblGT, d, d);
    WANT_FAIL (DblGT, d + epsilon, d);
    WANT_FAIL (DblGT, d,           d - epsilon);

    snprintf (funcName, NAMELEN, "%s(%.0f)", __func__, d);
    check_fails (funcName);
}



static void
test_cut_DblLT (void)
{
    double  d = 1e-9;
    short   i;

    test_cut_DblLT_helper (0.0);
    for (i = -9; i <= 9; i += 2)
    {
        test_cut_DblLT_helper (d);
        test_cut_DblLT_helper (-d);
        d *= 100;
    }
}



static void
test_cut_DblLT_helper (double d)
{
    const short NAMELEN = 80;
    char funcName[NAMELEN];

    WANT_SUCC (DblLT, d + epsilon, d);
    WANT_SUCC (DblLT, d,           d - epsilon);

    WANT_FAIL (DblLT, d, d);
    WANT_FAIL (DblLT, d,           d + epsilon);
    WANT_FAIL (DblLT, d - epsilon, d);

    snprintf (funcName, NAMELEN, "%s(%.0f)", __func__, d);
    check_fails (funcName);
}



static void
test_cut_IStrABegE (void)
{
    WANT_SUCC (IStrABegE, "This is a test", "tHIS");
    /* all other tests are covered by StrABegE */
}



static void
test_cut_IStrAContE (void)
{
    char *test = "This is a test";

    WANT_SUCC (IStrAContE, "tHIS", test);
    WANT_SUCC (IStrAContE, " Is ", test);
    WANT_SUCC (IStrAContE, "Test", test);

    /* all other tests are covered by StrAContE */
}



static void
test_cut_IStrAEndE (void)
{
    WANT_SUCC (IStrAEndE, "This is a test", "Test");
    /* all other tests are covered by StrAEndE */
}



static void
test_cut_IStrEQ (void)
{
    WANT_SUCC (IStrEQ, "foo", "FOO");
    /* all other tests are covered by StrEQ */
}



static void
test_cut_IStrGT (void)
{
    WANT_SUCC (IStrGT, "aaa", "ZZZ");
    WANT_SUCC (IStrGT, "AAA", "zzz");

    WANT_FAIL (IStrGT, "zzz", "AAA");
    WANT_FAIL (IStrGT, "ZZZ", "aaa");

    check_fails (__func__);
}



static void
test_cut_IStrLT (void)
{
    WANT_SUCC (IStrLT, "zzz", "AAA");
    WANT_SUCC (IStrLT, "ZZZ", "aaa");

    WANT_FAIL (IStrLT, "aaa", "ZZZ");
    WANT_FAIL (IStrLT, "AAA", "zzz");

    check_fails (__func__);
}



static void
test_cut_IntEQ (void)
{
    WANT_SUCC (IntEQ, 0, 0);
    WANT_SUCC (IntEQ, 1, 1);
    WANT_SUCC (IntEQ, -1, -1);

    WANT_FAIL (IntEQ, 1, -1);

    check_fails (__func__);
}



static void
test_cut_IntGT (void)
{
    WANT_SUCC (IntGT, 1, 2);
    WANT_SUCC (IntGT, -1, 1);

    WANT_FAIL (IntGT, 1, 1);
    WANT_FAIL (IntGT, 2, 1);
    WANT_FAIL (IntGT, 2, -1);

    check_fails (__func__);
}



static void
test_cut_IntLT (void)
{
    WANT_SUCC (IntLT, 2, 1);
    WANT_SUCC (IntLT, 2, -1);

    WANT_FAIL (IntLT, 1, 1);
    WANT_FAIL (IntLT, 1, 2);
    WANT_FAIL (IntLT, -1, 1);

    check_fails (__func__);
}



static void
test_cut_StrABegE (void)
{
    WANT_SUCC (StrABegE, "This is a test", "This");
    WANT_SUCC (StrABegE, "This is a test", "");
    WANT_SUCC (StrABegE, "This is a test", NULL);
    WANT_SUCC (StrABegE, NULL, NULL);

    WANT_FAIL (StrABegE, NULL, "This");
    WANT_FAIL (StrABegE, "This is a test", "This is not");
    WANT_FAIL (StrABegE, "This is a test", "test");

    check_fails (__func__);
}



static void
test_cut_StrAContE (void)
{
    char *test = "This is a test";

    WANT_SUCC (StrAContE, "This", test);
    WANT_SUCC (StrAContE, " is ", test);
    WANT_SUCC (StrAContE, "test", test);
    WANT_SUCC (StrAContE, "", test);
    WANT_SUCC (StrAContE, NULL, test);
    WANT_SUCC (StrAContE, "", NULL);
    WANT_SUCC (StrAContE, NULL, NULL);

    WANT_FAIL (StrAContE, test, NULL);
    WANT_FAIL (StrAContE, test, "");
    WANT_FAIL (StrAContE, "This is not", test);
    WANT_FAIL (StrAContE, "not a test", test);

    check_fails (__func__);
}



static void
test_cut_StrAEndE (void)
{
    WANT_SUCC (StrAEndE, "This is a test", "test");
    WANT_SUCC (StrAEndE, "This is a test", "");
    WANT_SUCC (StrAEndE, "This is a test", NULL);
    WANT_SUCC (StrAEndE, NULL, NULL);

    WANT_FAIL (StrAEndE, NULL, "This");
    WANT_FAIL (StrAEndE, "This is a test", "not a test");
    WANT_FAIL (StrAEndE, "This is a test", "This");

    check_fails (__func__);
}



static void
test_cut_StrEQ (void)
{
    char *str = "foo";

    WANT_SUCC (StrEQ, str, str);
    WANT_SUCC (StrEQ, NULL, NULL);
    WANT_SUCC (StrEQ, "", "");
    WANT_SUCC (StrEQ, NULL, "");
    WANT_SUCC (StrEQ, "", NULL);

    WANT_FAIL (StrEQ, str, "blah");
    WANT_FAIL (StrEQ, str, "");
    WANT_FAIL (StrEQ, str, NULL);
    WANT_FAIL (StrEQ, NULL, str);

    check_fails (__func__);
}



static void
test_cut_StrGT (void)
{
    /* remember, in ASCII sorting, caps come first */

    WANT_SUCC (StrGT, "AAA", "ZZZ");
    WANT_SUCC (StrGT, "AAA", "aaa");
    WANT_SUCC (StrGT, "AAA", "zzz");
    WANT_SUCC (StrGT, "ZZZ", "aaa");
    WANT_SUCC (StrGT, "ZZZ", "zzz");
    WANT_SUCC (StrGT, "aaa", "zzz");

    WANT_FAIL (StrGT, "AAA", "AAA");
    WANT_FAIL (StrGT, "ZZZ", "AAA");
    WANT_FAIL (StrGT, "aaa", "AAA");
    WANT_FAIL (StrGT, "aaa", "ZZZ");
    WANT_FAIL (StrGT, "zzz", "AAA");
    WANT_FAIL (StrGT, "zzz", "ZZZ");
    WANT_FAIL (StrGT, "zzz", "aaa");

    check_fails (__func__);
}



static void
test_cut_StrLT (void)
{
    /* remember, in ASCII sorting, caps come first */

    WANT_SUCC (StrLT, "ZZZ", "AAA");
    WANT_SUCC (StrLT, "aaa", "AAA");
    WANT_SUCC (StrLT, "aaa", "ZZZ");
    WANT_SUCC (StrLT, "zzz", "AAA");
    WANT_SUCC (StrLT, "zzz", "ZZZ");
    WANT_SUCC (StrLT, "zzz", "aaa");

    WANT_FAIL (StrLT, "AAA", "AAA");

    WANT_FAIL (StrLT, "AAA", "ZZZ");
    WANT_FAIL (StrLT, "AAA", "aaa");
    WANT_FAIL (StrLT, "AAA", "zzz");
    WANT_FAIL (StrLT, "ZZZ", "aaa");
    WANT_FAIL (StrLT, "ZZZ", "zzz");
    WANT_FAIL (StrLT, "aaa", "zzz");

    check_fails (__func__);
}



static void
test_cut_UIntEQ (void)
{
    WANT_SUCC (UIntEQ, UINT_MAX, -1);
    /* other tests covered by IntEQ */
}



static void
test_cut_UIntGT (void)
{
    WANT_SUCC (UIntLT, -1, 1);
    /* other tests covered by IntGT */
}



static void
test_cut_UIntLT (void)
{
    WANT_SUCC (UIntGT, 1, -1);
    /* other tests covered by IntLT */
}



/* END OF FILE */
