/*
 * CUT: C Unit Tester
 * Working code.
 * (C) Copyright 2009 by Dave Aronson
 * All Rights Reserved
 */



/* do this before including string.h so we get strcasestr */
#define _GNU_SOURCE


/* PROJECT INCLUDES */

#include "cut.h"


/* GENERAL INCLUDES */

#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



/* EXPORTED VARS */

unsigned int  cut_failures = 0;


/* PRIVATE GLOBAL VARS */

static unsigned int  last_fail_count = 0;
static short         quiet = 0;



/* PROTOTYPES OF INTERNAL FUNCTIONS */

static short cmp_dbl (const cut_cmp_t cmp, const double exp, const double act);
static short cmp_int (const cut_cmp_t cmp, const int exp, const int act);
static short cmp_str (const cut_cmp_t cmp, const cut_flag_t flags, const char *exp, const char *act);
static short cmp_uint (const cut_cmp_t cmp, const unsigned int exp, const unsigned int act);
static short compare (const cut_cmp_t cmp, const cut_typ_t typ, const cut_flag_t flags, const double expDbl, const double actDbl, const int expInt, const int actInt);
static void  report_error (const char *file, const int line, const char *func, const cut_cmp_t cmp, const cut_typ_t typ, const cut_failop_t failop, const cut_flag_t flags, const void *expPtr, const void *actPtr, const char *fmt, const va_list ap);



/* EXPORTED FUNCTIONS */



/* first the ones that users are supposed to use directly */



void
cut_give_count (void)
{
    fprintf (stderr, "\nTotal counted failures: %d\n", cut_failures);
}



void
cut_set_quiet (const short q)
{
    quiet = q;
    if (q) last_fail_count = cut_failures;
    else
    {
        int ignored = cut_failures - last_fail_count;
        if (ignored > 0)
        {
            fprintf (stderr,
                    "WARNING: %d failure%s ignored in quiet mode!\n",
                    ignored, ignored > 1 ? "s" : "");
        }
    }
}



/* and now the "semi-private" ones -- that's why the two underscores */



/* assertion for most uses: ints of various sizes, doubles, and strings */
cut_failop_t
cut__assert
(
    const char         *file,
    const int           line,
    const char         *func,
    const cut_cmp_t     cmp,
    const cut_typ_t     typ,
    const cut_failop_t  failop,
    const cut_flag_t    flags,
    const double        expDbl,  /* unused if testing ints */
    const double        actDbl,  /* unused if testing ints */
    const int           expInt,  /* unused if testing dbls */
    const int           actInt,  /* unused if testing dbls */
    const char         *fmt,
    ...
)
{
    void  *actPtr;
    void  *expPtr;
    short  ok;

    /* don't bother checking, if it's for nothing! */
    if (CUT_FAIL_IGNORE == failop) return CUT_FAIL_IGNORE;

    ok = compare (cmp, typ, flags, expDbl, actDbl, expInt, actInt);
    if (flags & CUT_FLAG_NEGATE) ok = !ok;
    if (ok) return CUT_FAIL_OK;

    actPtr = (typ == CUT_TYP_DBL) ? (void *) &actDbl : (void *) &actInt;
    expPtr = (typ == CUT_TYP_DBL) ? (void *) &expDbl : (void *) &expInt;

    if (! quiet)
    {
        va_list ap;
        if (fmt && *fmt) va_start (ap, fmt);
        report_error (file, line, func, cmp, typ, failop, flags,
                      expPtr, actPtr, fmt, ap);
        if (fmt && *fmt) va_end (ap);
    }

    if (failop != CUT_FAIL_OK) cut_failures++;

    if (failop == CUT_FAIL_ABORT)
    {
        if (!quiet)
        {
            fprintf (stderr,
                     "%s:%d: %s aborting test suite due to CUT_FAIL_ABORT\n",
                     file, line, func);
        }
        cut_give_count();
        exit (cut_failures);
    }

    return failop;
}



short
cut__is_quiet (void)
{
    return quiet != 0;
}



/* INTERNAL FUNCTIONS */



static short
cmp_dbl (const cut_cmp_t cmp, const double exp, const double act)
{
    switch (cmp)
    {
        /* TODO MAYBE: adjustable tolerance for comparing doubles? */
        case CUT_CMP_EQ:  return act == exp;  break;
        case CUT_CMP_LT:  return act <  exp;  break;
        case CUT_CMP_GT:  return act >  exp;  break;
        default:
            fprintf (stderr,
                     "INTERNAL ERROR: invalid comparison %d in cmp_dbl\n",
                     cmp);
            exit (255);
        break;
    }
}



static short
cmp_int (const cut_cmp_t cmp, const int exp, const int act)
{
    switch (cmp)
    {
        case CUT_CMP_EQ:  return act == exp;  break;
        case CUT_CMP_LT:  return act < exp;   break;
        case CUT_CMP_GT:  return act > exp;   break;
        default:
            fprintf (stderr,
                     "INTERNAL ERROR: invalid comparison %d in cmp_int\n",
                     cmp);
            exit (255);
        break;
    }
}



static short
cmp_str
(
    const cut_cmp_t   cmp,
    const cut_flag_t  flags,
    const char       *exp,
    const char       *act
)
{
    int         actlen;
    char       *cPtr;
    int         diff;
    int         explen;
    cut_flag_t  insens = flags & CUT_FLAG_NOCASE;
    cut_flag_t  swap = flags & CUT_FLAG_STRSWAP;

    if (swap)
    {
        const char *tmp;
        tmp = act;
        act = exp;
        exp = tmp;
    }

    switch (cmp)
    {
        case CUT_CMP_EQ:
        case CUT_CMP_GT:
        case CUT_CMP_LT:
            if (exp == NULL && act == NULL) diff = 0;
            else if (exp == NULL) diff = act[0];
            else if (act == NULL) diff = exp[0];
            else diff = (insens ? strcasecmp : strcmp) (act, exp);
            return cmp_int (cmp, 0, diff);
        break;

        case CUT_CMP_STR_BEG:
            if (act == NULL) return 1;
            else if (exp == NULL) return *act == '\0';
            return ! (insens ? strncasecmp : strncmp) (act, exp, strlen (act));
        break;

        case CUT_CMP_STR_CONT:
            if (exp == NULL) return 1;
            else if (act == NULL) return *exp == '\0';
            cPtr = (insens ? strcasestr : strstr) (act, exp);
            return cPtr != NULL;
        break;

        case CUT_CMP_STR_END:
            if (act == NULL) return 1;
            else if (exp == NULL) return *act == '\0';
            actlen = strlen (act);
            explen = strlen (exp);
            if (actlen > explen) return 0;
            return ! (insens ? strncasecmp : strncmp) (exp + explen - actlen,
                                                       act, actlen);
        break;
    }
    fprintf (stderr, "INTERNAL ERROR: invalid string comparison option %d\n",
             cmp);
    exit (++cut_failures);
}



static short
cmp_uint (const cut_cmp_t cmp, const unsigned int exp, const unsigned int act)
{
    switch (cmp)
    {
        case CUT_CMP_EQ:  return act == exp;  break;
        case CUT_CMP_LT:  return act < exp;   break;
        case CUT_CMP_GT:  return act > exp;   break;
        default:
            fprintf (stderr,
                     "INTERNAL ERROR: invalid comparison %d in cmp_int\n",
                     cmp);
            exit (255);
        break;
    }
}


static short
compare
(
    const cut_cmp_t   cmp,
    const cut_typ_t   typ,
    const cut_flag_t  flags,
    const double      expDbl,
    const double      actDbl,
    const int         expInt,
    const int         actInt
)
{
    switch (typ)
    {
        case CUT_TYP_DBL:
            return cmp_dbl (cmp, expDbl, actDbl);
        break;

        case CUT_TYP_STR:
            return cmp_str (cmp, flags, (char *) expInt, (char *) actInt);
        break;

        case CUT_TYP_UINT:
            return cmp_uint (cmp, (unsigned int) expInt,
                                  (unsigned int) actInt);
        break;

        default:  /* assorted types of signed integers */
            return cmp_int (cmp, expInt, actInt);
        break;
    }
}



void
report_error
(
    const char          *file,
    const int            line,
    const char          *func,
    const cut_cmp_t      cmp,
    const cut_typ_t      typ,
    const cut_failop_t   failop,
    const cut_flag_t     flags,
    const void          *expPtr,
    const void          *actPtr,
    const char          *fmt,
    const va_list        ap
)
{
    const int BUFLEN = 80;

    char        *cmpStr;
    char         errFmt[BUFLEN];
    cut_flag_t   neg = flags & CUT_FLAG_NEGATE;
    cut_flag_t   swap = flags & CUT_FLAG_STRSWAP;

    if (quiet) return;

    if (swap)
    {
        const void *tmp;
        tmp = actPtr;
        actPtr = expPtr;
        expPtr = tmp;
    }

    switch (cmp)
    {
        case CUT_CMP_EQ:
            cmpStr = neg ? "!=" : "==";
        break;
        case CUT_CMP_GT:
            cmpStr = neg ? "<=" : ">";
        break;
        case CUT_CMP_LT:
            cmpStr = neg ? ">=" : "<";
        break;
        case CUT_CMP_STR_CONT:
            if (swap) cmpStr = neg ? "not in" : "in";
            else cmpStr = neg ? "not containing" : "containing";
        break;
        case CUT_CMP_STR_END:
            if (swap) cmpStr = neg ? "not ending with" : "ending with";
            else cmpStr = neg ? "not the end of" : "the end of";
        break;
        case CUT_CMP_STR_BEG:
            if (swap) cmpStr = neg ? "not starting with" : "starting with";
            else cmpStr = neg ? "not the start of" : "the start of";
        break;
    }

    /* TODO MAYBE: make sure typ is legit? */

    snprintf (errFmt, BUFLEN, "%s:%d: %s wanted %s '%%%c'; got '%%%c'",
              file, line, func, cmpStr, typ, typ);
    /*
     * ugly hack, to prevent %f from taking it as a *float* rather
     * than *double*, but still Do The Right Thing w/ strings and
     * assorted types of ints
     */
    fprintf (stderr, errFmt, *(double*)expPtr, *(double*)actPtr);
    if (fmt && *fmt)
    {
        fprintf (stderr, " (");
        vfprintf (stderr, fmt, ap);
        fprintf (stderr, ")");
        if (fmt[strlen(fmt)-1] != '\n') fputc ('\n', stderr);
    }
    else fputc ('\n', stderr);
    if (failop == CUT_FAIL_OK)
    {
        fprintf (stderr,
                 "%s:%d: %s not counting above error, due to CUT_FAIL_OK\n",
                 file, line, func);
    }
}



/* END OF FILE */
