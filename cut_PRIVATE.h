/*
 * CUT: C Unit Tester
 * Declarations of items not intended to be seen by users.
 * (C) Copyright 2009 by Dave Aronson
 * All Rights Reserved
 */



/* DATA TYPES */



/* comparisons */
typedef enum
{
    /* These are valid with most data types */
    CUT_CMP_EQ,        /* equal */
    CUT_CMP_GT,        /* greater than */
    CUT_CMP_LT,        /* less than */
    /* now stuff peculiar to strings; see CUT_FLAG_STRSWAP */
    CUT_CMP_STR_BEG,   /* actual begins w/ expected */
    CUT_CMP_STR_CONT,  /* actual contains expected anywhere */
    CUT_CMP_STR_END,   /* actual ends w/ expected */
    /* everything else standard is a variation on one of the above! */
} cut_cmp_t;



/* what kind of data we're dealing with, based on printf codes */
typedef enum
{
    CUT_TYP_CHR  = 'c',  /* char */
    CUT_TYP_DBL  = 'f',  /* double */
    CUT_TYP_DEC  = 'd',  /* decimal-printed int */
    CUT_TYP_HEX  = 'x',  /* hex-printed int */
    CUT_TYP_OCT  = 'o',  /* octal-printed int */
    CUT_TYP_STR  = 's',  /* string */
    CUT_TYP_UINT = 'u',  /* unsigned (decimal) int */
} cut_typ_t;



/* flags affecting cut's behavior. */
typedef enum
{
    CUT_FLAG_NEGATE  = 0x01,  /* negate the test, eg EQ -> NE, or LT -> GE */
    CUT_FLAG_NOCASE  = 0x02,  /* case insensitive */
    CUT_FLAG_STRSWAP = 0x04,  /* string searches reverse haystack & needle */
} cut_flag_t;



/* FUNCTIONS */

cut_failop_t cut__assert (const char *file, const int line, const char *func, const cut_cmp_t cmp, const cut_typ_t typ, const cut_failop_t failopt, const cut_flag_t flags, const double expDbl, const double actDbl, const int expInt, const int actInt, const char *fmt, ...);

short cut__is_quiet (void);



/* MACROS */



/* first the "first-level" ones, called from outside this file */



/* normal one for most uses, w/ auto-genned msg */
#define CUT_ASSERT(cmp,prn,fail,flags,exp,act)\
do\
{\
    CUT_CHECK_IF_RETURN (cut__assert (__FILE__, __LINE__, __func__, cmp, prn, fail, flags, 0, 0, exp, act, NULL));\
} while (0)



/* normal one for most uses, w/ custom msg */
#define CUT_ASSERT_M(cmp,prn,fail,flags,exp,act,fmt...)\
do\
{\
    if (0) fprintf (stderr, fmt);\
    CUT_CHECK_IF_RETURN (cut__assert (__FILE__, __LINE__, __func__, cmp, prn, fail, flags, 0, 0, exp, act, fmt));\
} while (0)



/* normal one for doubles, w/ auto-genned msg */
#define CUT_ASSERT_D(cmp,fail,flags,exp,act)\
do\
{\
    CUT_CHECK_IF_RETURN (cut__assert (__FILE__, __LINE__, __func__, cmp, CUT_TYP_DBL, fail, flags, exp, act, 0, 0, NULL));\
} while (0)



/* normal one for doubles, w/ custom msg */
#define CUT_ASSERT_DM(cmp,fail,flags,exp,act,fmt...)\
do\
{\
    if (0) fprintf (stderr, fmt);\
    CUT_CHECK_IF_RETURN (cut__assert (__FILE__, __LINE__, __func__, cmp, CUT_TYP_DBL, fail, flags, exp, act, 0, 0, fmt));\
} while (0)



/* and now the ones referenced in the above macros */



/*
 * see if the test returned a code saying we should exit this function now
 * (this feature is why assertions have to be macros, unless we want to mess
 * with longjmps and complex stuff like that)
 */
#define CUT_CHECK_IF_RETURN(ret)\
do\
{\
 if (CUT_FAIL_RETURN == ret)\
 {\
  if (! cut__is_quiet())\
  {\
      fprintf (stderr,\
               "%s:%d: %s returning due to CUT_FAIL_RETURN\n",\
               __FILE__, __LINE__, __func__);\
  }\
  return;\
 }\
} while (0)



/* END OF FILE */
