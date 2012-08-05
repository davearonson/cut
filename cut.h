/*
 * CUT: C Unit Tester
 * Declarations of things intended for user usage.
 * (C) Copyright 2009 by Dave Aronson
 * All Rights Reserved
 */



/* DATA TYPES */



/* what to do when a test fails */
typedef enum
{
    CUT_FAIL_ABORT,   /* abort entire test run */
    CUT_FAIL_CONT,    /* count, but continue function */
    CUT_FAIL_IGNORE,  /* don't report, let alone count */
    CUT_FAIL_OK,      /* don't count as a failure, just report */
    CUT_FAIL_RETURN,  /* count, and return from func, as most frameworks do */
} cut_failop_t;



#include "cut_PRIVATE.h"  /* has to wait 'cuz it needs failop_t */



/* FUNCTIONS */


void  cut_give_count (void);
void  cut_set_quiet (const short q);



/* GLOBAL VARS */

extern unsigned int  cut_failures;



/* MACROS -- these are the main things end-users will use */

/*
 * Broadly, these are named cut_typCM or cut_typCM_M, where typ is the data
 * type, CM is the comparison, and _M means you want to add a custom message,
 * which is in printf style (format string and maybe further args to replace
 * placeholders).  If you add more, please be consistent, and tell me about it
 * so I can consider it for inclusion in further releases.
 *
 * You don't need to be concerned with the definition, unless you want to add
 * more.  In that case, you need to grok CUT_ASSERT[_DBL][_MSG],
 * and the flags, all defined in cut_PRIVATE.h... and probably more stuff,
 * because you probably want to add an additional data type and/or comparison.
 */

/*
 * WARNING: Some compilers treat chars as signed, some as unsigned.  The C99
 * standard only says it must be consistent... within a given implementation.
 * So, be VERY CAREFUL with order comparisons, when including above & below ~!
 * Or maybe make explicit signed & unsigned sets of macros....
 */

#define cut_ChrEQ(          fail, exp, act)             CUT_ASSERT(   CUT_CMP_EQ      , CUT_TYP_CHR , fail, 0 , exp, act)
#define cut_ChrEQ_M(        fail, exp, act, fmt...)     CUT_ASSERT_M( CUT_CMP_EQ      , CUT_TYP_CHR , fail, 0 , exp, act, fmt)
#define cut_ChrGE(          fail, exp, act)             CUT_ASSERT(   CUT_CMP_LT      , CUT_TYP_CHR , fail, CUT_FLAG_NEGATE, exp, act)
#define cut_ChrGE_M(        fail, exp, act, fmt...)     CUT_ASSERT_M( CUT_CMP_LT      , CUT_TYP_CHR , fail, CUT_FLAG_NEGATE, exp, act, fmt)
#define cut_ChrGT(          fail, exp, act)             CUT_ASSERT(   CUT_CMP_GT      , CUT_TYP_CHR , fail, 0 , exp, act)
#define cut_ChrGT_M(        fail, exp, act, fmt...)     CUT_ASSERT_M( CUT_CMP_GT      , CUT_TYP_CHR , fail, 0 , exp, act, fmt)
#define cut_ChrLE(          fail, exp, act)             CUT_ASSERT(   CUT_CMP_GT      , CUT_TYP_CHR , fail, CUT_FLAG_NEGATE, exp, act)
#define cut_ChrLE_M(        fail, exp, act, fmt...)     CUT_ASSERT_M( CUT_CMP_GT      , CUT_TYP_CHR , fail, CUT_FLAG_NEGATE, exp, act, fmt)
#define cut_ChrLT(          fail, exp, act)             CUT_ASSERT(   CUT_CMP_LT      , CUT_TYP_CHR , fail, 0 , exp, act)
#define cut_ChrLT_M(        fail, exp, act, fmt...)     CUT_ASSERT_M( CUT_CMP_LT      , CUT_TYP_CHR , fail, 0 , exp, act, fmt)
#define cut_ChrNE(          fail, exp, act)             CUT_ASSERT(   CUT_CMP_EQ      , CUT_TYP_CHR , fail, CUT_FLAG_NEGATE, exp, act)
#define cut_ChrNE_M(        fail, exp, act, fmt...)     CUT_ASSERT_M( CUT_CMP_EQ      , CUT_TYP_CHR , fail, CUT_FLAG_NEGATE, exp, act, fmt)
#define cut_DblEQ(          fail, exp, act)             CUT_ASSERT_D( CUT_CMP_EQ      ,               fail, 0 , exp, act)
#define cut_DblEQ_M(        fail, exp, act, fmt...)     CUT_ASSERT_DM(CUT_CMP_EQ      ,               fail, 0 , exp, act, fmt)
#define cut_DblGE(          fail, exp, act)             CUT_ASSERT_D( CUT_CMP_LT      ,               fail, CUT_FLAG_NEGATE, exp, act)
#define cut_DblGE_M(        fail, exp, act, fmt...)     CUT_ASSERT_DM(CUT_CMP_LT      ,               fail, CUT_FLAG_NEGATE, exp, act, fmt)
#define cut_DblGT(          fail, exp, act)             CUT_ASSERT_D( CUT_CMP_GT      ,               fail, 0 , exp, act)
#define cut_DblGT_M(        fail, exp, act, fmt...)     CUT_ASSERT_DM(CUT_CMP_GT      ,               fail, 0 , exp, act, fmt)
#define cut_DblLE(          fail, exp, act)             CUT_ASSERT_D( CUT_CMP_GT      ,               fail, CUT_FLAG_NEGATE, exp, act)
#define cut_DblLE_M(        fail, exp, act, fmt...)     CUT_ASSERT_DM(CUT_CMP_GT      ,               fail, CUT_FLAG_NEGATE, exp, act, fmt)
#define cut_DblLT(          fail, exp, act)             CUT_ASSERT_D( CUT_CMP_LT      ,               fail, 0 , exp, act)
#define cut_DblLT_M(        fail, exp, act, fmt...)     CUT_ASSERT_DM(CUT_CMP_LT      ,               fail, 0 , exp, act, fmt)
#define cut_DblNE(          fail, exp, act)             CUT_ASSERT_D( CUT_CMP_EQ      ,               fail, CUT_FLAG_NEGATE, exp, act)
#define cut_DblNE_M(        fail, exp, act, fmt...)     CUT_ASSERT_DM(CUT_CMP_EQ      ,               fail, CUT_FLAG_NEGATE, exp, act, fmt)
#define cut_HexEQ(          fail, exp, act)             CUT_ASSERT(   CUT_CMP_EQ      , CUT_TYP_HEX , fail, 0 , exp, act)
#define cut_HexEQ_M(        fail, exp, act, fmt...)     CUT_ASSERT_M( CUT_CMP_EQ      , CUT_TYP_HEX , fail, 0 , exp, act, fmt)
#define cut_HexGE(          fail, exp, act)             CUT_ASSERT(   CUT_CMP_LT      , CUT_TYP_HEX , fail, CUT_FLAG_NEGATE, exp, act)
#define cut_HexGE_M(        fail, exp, act, fmt...)     CUT_ASSERT_M( CUT_CMP_LT      , CUT_TYP_HEX , fail, CUT_FLAG_NEGATE, exp, act, fmt)
#define cut_HexGT(          fail, exp, act)             CUT_ASSERT(   CUT_CMP_GT      , CUT_TYP_HEX , fail, 0 , exp, act)
#define cut_HexGT_M(        fail, exp, act, fmt...)     CUT_ASSERT_M( CUT_CMP_GT      , CUT_TYP_HEX , fail, 0 , exp, act, fmt)
#define cut_HexLE(          fail, exp, act)             CUT_ASSERT(   CUT_CMP_GT      , CUT_TYP_HEX , fail, CUT_FLAG_NEGATE, exp, act)
#define cut_HexLE_M(        fail, exp, act, fmt...)     CUT_ASSERT_M( CUT_CMP_GT      , CUT_TYP_HEX , fail, CUT_FLAG_NEGATE, exp, act, fmt)
#define cut_HexLT(          fail, exp, act)             CUT_ASSERT(   CUT_CMP_LT      , CUT_TYP_HEX , fail, 0 , exp, act)
#define cut_HexLT_M(        fail, exp, act, fmt...)     CUT_ASSERT_M( CUT_CMP_LT      , CUT_TYP_HEX , fail, 0 , exp, act, fmt)
#define cut_HexNE(          fail, exp, act)             CUT_ASSERT(   CUT_CMP_EQ      , CUT_TYP_HEX , fail, CUT_FLAG_NEGATE, exp, act)
#define cut_HexNE_M(        fail, exp, act, fmt...)     CUT_ASSERT_M( CUT_CMP_EQ      , CUT_TYP_HEX , fail, CUT_FLAG_NEGATE, exp, act, fmt)
#define cut_IStrABegE(      fail, exp, act)             CUT_ASSERT(   CUT_CMP_STR_BEG , CUT_TYP_STR , fail, CUT_FLAG_NOCASE, (int)exp, (int)act)
#define cut_IStrABegE_M(    fail, exp, act, fmt...)     CUT_ASSERT_M( CUT_CMP_STR_BEG , CUT_TYP_STR , fail, CUT_FLAG_NOCASE, (int)exp, (int)act, fmt)
#define cut_IStrAContE(     fail, exp, act)             CUT_ASSERT(   CUT_CMP_STR_CONT, CUT_TYP_STR , fail, CUT_FLAG_NOCASE, (int)exp, (int)act)
#define cut_IStrAContE_M(   fail, exp, act, fmt...)     CUT_ASSERT_M( CUT_CMP_STR_CONT, CUT_TYP_STR , fail, CUT_FLAG_NOCASE, (int)exp, (int)act, fmt)
#define cut_IStrAEndE(      fail, exp, act)             CUT_ASSERT(   CUT_CMP_STR_END , CUT_TYP_STR , fail, CUT_FLAG_NOCASE, (int)exp, (int)act)
#define cut_IStrAEndE_M(    fail, exp, act, fmt...)     CUT_ASSERT_M( CUT_CMP_STR_END , CUT_TYP_STR , fail, CUT_FLAG_NOCASE, (int)exp, (int)act, fmt)
#define cut_IStrANotBegE(   fail, exp, act)             CUT_ASSERT(   CUT_CMP_STR_BEG , CUT_TYP_STR , fail, CUT_FLAG_NEGATE|CUT_FLAG_NOCASE|CUT_FLAG_STRSWAP, (int)exp, (int)act)
#define cut_IStrANotBegE_M( fail, exp, act, fmt...)     CUT_ASSERT_M( CUT_CMP_STR_BEG , CUT_TYP_STR , fail, CUT_FLAG_NEGATE|CUT_FLAG_NOCASE|CUT_FLAG_STRSWAP, (int)exp, (int)act, fmt)
#define cut_IStrANotContE(  fail, exp, act)             CUT_ASSERT(   CUT_CMP_STR_CONT, CUT_TYP_STR , fail, CUT_FLAG_NOCASE|CUT_FLAG_NEGATE, (int)exp, (int)act)
#define cut_IStrANotContE_M(fail, exp, act, fmt...)     CUT_ASSERT_M( CUT_CMP_STR_CONT, CUT_TYP_STR , fail, CUT_FLAG_NOCASE|CUT_FLAG_NEGATE, (int)exp, (int)act, fmt)
#define cut_IStrANotEndE(   fail, exp, act)             CUT_ASSERT(   CUT_CMP_STR_END , CUT_TYP_STR , fail, CUT_FLAG_NEGATE|CUT_FLAG_NOCASE|CUT_FLAG_STRSWAP, (int)exp, (int)act)
#define cut_IStrANotEndE_M( fail, exp, act, fmt...)     CUT_ASSERT_M( CUT_CMP_STR_END , CUT_TYP_STR , fail, CUT_FLAG_NEGATE|CUT_FLAG_NOCASE|CUT_FLAG_STRSWAP, (int)exp, (int)act, fmt)
#define cut_IStrEBegA(      fail, exp, act)             CUT_ASSERT(   CUT_CMP_STR_BEG , CUT_TYP_STR , fail, CUT_FLAG_NOCASE|CUT_FLAG_STRSWAP, (int)exp, (int)act)
#define cut_IStrEBegA_M(    fail, exp, act, fmt...)     CUT_ASSERT_M( CUT_CMP_STR_BEG , CUT_TYP_STR , fail, CUT_FLAG_NOCASE|CUT_FLAG_STRSWAP, (int)exp, (int)act, fmt)
#define cut_IStrEContA(     fail, exp, act)             CUT_ASSERT(   CUT_CMP_STR_CONT, CUT_TYP_STR , fail, CUT_FLAG_NOCASE|CUT_FLAG_STRSWAP, (int)exp, (int)act)
#define cut_IStrEContA_M(   fail, exp, act, fmt...)     CUT_ASSERT_M( CUT_CMP_STR_CONT, CUT_TYP_STR , fail, CUT_FLAG_NOCASE|CUT_FLAG_STRSWAP, (int)exp, (int)act, fmt)
#define cut_IStrEEndA(      fail, exp, act)             CUT_ASSERT(   CUT_CMP_STR_END , CUT_TYP_STR , fail, CUT_FLAG_NOCASE|CUT_FLAG_STRSWAP, (int)exp, (int)act)
#define cut_IStrEEndA_M(    fail, exp, act, fmt...)     CUT_ASSERT_M( CUT_CMP_STR_END , CUT_TYP_STR , fail, CUT_FLAG_NOCASE|CUT_FLAG_STRSWAP, (int)exp, (int)act, fmt)
#define cut_IStrENotBegA(   fail, exp, act)             CUT_ASSERT(   CUT_CMP_STR_BEG , CUT_TYP_STR , fail, CUT_FLAG_NOCASE|CUT_FLAG_NEGATE, (int)exp, (int)act)
#define cut_IStrENotBegA_M( fail, exp, act, fmt...)     CUT_ASSERT_M( CUT_CMP_STR_BEG , CUT_TYP_STR , fail, CUT_FLAG_NOCASE|CUT_FLAG_NEGATE, (int)exp, (int)act, fmt)
#define cut_IStrENotContA(  fail, exp, act)             CUT_ASSERT(   CUT_CMP_STR_CONT, CUT_TYP_STR , fail, CUT_FLAG_NEGATE|CUT_FLAG_NOCASE|CUT_FLAG_STRSWAP, (int)exp, (int)act)
#define cut_IStrENotContA_M(fail, exp, act, fmt...)     CUT_ASSERT_M( CUT_CMP_STR_CONT, CUT_TYP_STR , fail, CUT_FLAG_NEGATE|CUT_FLAG_NOCASE|CUT_FLAG_STRSWAP, (int)exp, (int)act, fmt)
#define cut_IStrENotEndA(   fail, exp, act)             CUT_ASSERT(   CUT_CMP_STR_END , CUT_TYP_STR , fail, CUT_FLAG_NOCASE|CUT_FLAG_NEGATE, (int)exp, (int)act)
#define cut_IStrENotEndA_M( fail, exp, act, fmt...)     CUT_ASSERT_M( CUT_CMP_STR_END , CUT_TYP_STR , fail, CUT_FLAG_NOCASE|CUT_FLAG_NEGATE, (int)exp, (int)act, fmt)
#define cut_IStrEQ(         fail, exp, act)             CUT_ASSERT(   CUT_CMP_EQ      , CUT_TYP_STR , fail, CUT_FLAG_NOCASE , (int)exp, (int)act)
#define cut_IStrEQ_M(       fail, exp, act, fmt...)     CUT_ASSERT_M( CUT_CMP_EQ      , CUT_TYP_STR , fail, CUT_FLAG_NOCASE , (int)exp, (int)act, fmt)
#define cut_IStrGE(         fail, exp, act)             CUT_ASSERT(   CUT_CMP_LT      , CUT_TYP_STR , fail, CUT_FLAG_NOCASE|CUT_FLAG_NEGATE, (int)exp, (int)act)
#define cut_IStrGE_M(       fail, exp, act, fmt...)     CUT_ASSERT_M( CUT_CMP_LT      , CUT_TYP_STR , fail, CUT_FLAG_NOCASE|CUT_FLAG_NEGATE, (int)exp, (int)act, fmt)
#define cut_IStrGT(         fail, exp, act)             CUT_ASSERT(   CUT_CMP_GT      , CUT_TYP_STR , fail, CUT_FLAG_NOCASE , (int)exp, (int)act)
#define cut_IStrGT_M(       fail, exp, act, fmt...)     CUT_ASSERT_M( CUT_CMP_GT      , CUT_TYP_STR , fail, CUT_FLAG_NOCASE , (int)exp, (int)act, fmt)
#define cut_IStrLE(         fail, exp, act)             CUT_ASSERT(   CUT_CMP_GT      , CUT_TYP_STR , fail, CUT_FLAG_NOCASE|CUT_FLAG_NEGATE, (int)exp, (int)act)
#define cut_IStrLE_M(       fail, exp, act, fmt...)     CUT_ASSERT_M( CUT_CMP_GT      , CUT_TYP_STR , fail, CUT_FLAG_NOCASE|CUT_FLAG_NEGATE, (int)exp, (int)act, fmt)
#define cut_IStrLT(         fail, exp, act)             CUT_ASSERT(   CUT_CMP_LT      , CUT_TYP_STR , fail, CUT_FLAG_NOCASE , (int)exp, (int)act)
#define cut_IStrLT_M(       fail, exp, act, fmt...)     CUT_ASSERT_M( CUT_CMP_LT      , CUT_TYP_STR , fail, CUT_FLAG_NOCASE , (int)exp, (int)act, fmt)
#define cut_IStrNE(         fail, exp, act)             CUT_ASSERT(   CUT_CMP_EQ      , CUT_TYP_STR , fail, CUT_FLAG_NOCASE|CUT_FLAG_NEGATE, (int)exp, (int)act)
#define cut_IStrNE_M(       fail, exp, act, fmt...)     CUT_ASSERT_M( CUT_CMP_EQ      , CUT_TYP_STR , fail, CUT_FLAG_NOCASE|CUT_FLAG_NEGATE, (int)exp, (int)act, fmt)
#define cut_IntEQ(          fail, exp, act)             CUT_ASSERT(   CUT_CMP_EQ      , CUT_TYP_DEC , fail, 0 , exp, act)
#define cut_IntEQ_M(        fail, exp, act, fmt...)     CUT_ASSERT_M( CUT_CMP_EQ      , CUT_TYP_DEC , fail, 0 , exp, act, fmt)
#define cut_IntGE(          fail, exp, act)             CUT_ASSERT(   CUT_CMP_LT      , CUT_TYP_DEC , fail, CUT_FLAG_NEGATE, exp, act)
#define cut_IntGE_M(        fail, exp, act, fmt...)     CUT_ASSERT_M( CUT_CMP_LT      , CUT_TYP_DEC , fail, CUT_FLAG_NEGATE, exp, act, fmt)
#define cut_IntGT(          fail, exp, act)             CUT_ASSERT(   CUT_CMP_GT      , CUT_TYP_DEC , fail, 0 , exp, act)
#define cut_IntGT_M(        fail, exp, act, fmt...)     CUT_ASSERT_M( CUT_CMP_GT      , CUT_TYP_DEC , fail, 0 , exp, act, fmt)
#define cut_IntLE(          fail, exp, act)             CUT_ASSERT(   CUT_CMP_GT      , CUT_TYP_DEC , fail, CUT_FLAG_NEGATE, exp, act)
#define cut_IntLE_M(        fail, exp, act, fmt...)     CUT_ASSERT_M( CUT_CMP_GT      , CUT_TYP_DEC , fail, CUT_FLAG_NEGATE, exp, act, fmt)
#define cut_IntLT(          fail, exp, act)             CUT_ASSERT(   CUT_CMP_LT      , CUT_TYP_DEC , fail, 0 , exp, act)
#define cut_IntLT_M(        fail, exp, act, fmt...)     CUT_ASSERT_M( CUT_CMP_LT      , CUT_TYP_DEC , fail, 0 , exp, act, fmt)
#define cut_IntNE(          fail, exp, act)             CUT_ASSERT(   CUT_CMP_EQ      , CUT_TYP_DEC , fail, CUT_FLAG_NEGATE, exp, act)
#define cut_IntNE_M(        fail, exp, act, fmt...)     CUT_ASSERT_M( CUT_CMP_EQ      , CUT_TYP_DEC , fail, CUT_FLAG_NEGATE, exp, act, fmt)
#define cut_OctEQ(          fail, exp, act)             CUT_ASSERT(   CUT_CMP_EQ      , CUT_TYP_OCT , fail, 0 , exp, act)
#define cut_OctEQ_M(        fail, exp, act, fmt...)     CUT_ASSERT_M( CUT_CMP_EQ      , CUT_TYP_OCT , fail, 0 , exp, act, fmt)
#define cut_OctGE(          fail, exp, act)             CUT_ASSERT(   CUT_CMP_LT      , CUT_TYP_OCT , fail, CUT_FLAG_NEGATE, exp, act)
#define cut_OctGE_M(        fail, exp, act, fmt...)     CUT_ASSERT_M( CUT_CMP_LT      , CUT_TYP_OCT , fail, CUT_FLAG_NEGATE, exp, act, fmt)
#define cut_OctGT(          fail, exp, act)             CUT_ASSERT(   CUT_CMP_GT      , CUT_TYP_OCT , fail, 0 , exp, act)
#define cut_OctGT_M(        fail, exp, act, fmt...)     CUT_ASSERT_M( CUT_CMP_GT      , CUT_TYP_OCT , fail, 0 , exp, act, fmt)
#define cut_OctLE(          fail, exp, act)             CUT_ASSERT(   CUT_CMP_GT      , CUT_TYP_OCT , fail, CUT_FLAG_NEGATE, exp, act)
#define cut_OctLE_M(        fail, exp, act, fmt...)     CUT_ASSERT_M( CUT_CMP_GT      , CUT_TYP_OCT , fail, CUT_FLAG_NEGATE, exp, act, fmt)
#define cut_OctLT(          fail, exp, act)             CUT_ASSERT(   CUT_CMP_LT      , CUT_TYP_OCT , fail, 0 , exp, act)
#define cut_OctLT_M(        fail, exp, act, fmt...)     CUT_ASSERT_M( CUT_CMP_LT      , CUT_TYP_OCT , fail, 0 , exp, act, fmt)
#define cut_OctNE(          fail, exp, act)             CUT_ASSERT(   CUT_CMP_EQ      , CUT_TYP_OCT , fail, CUT_FLAG_NEGATE, exp, act)
#define cut_OctNE_M(        fail, exp, act, fmt...)     CUT_ASSERT_M( CUT_CMP_EQ      , CUT_TYP_OCT , fail, CUT_FLAG_NEGATE, exp, act, fmt)
#define cut_PtrEQ(          fail, exp, act)             CUT_ASSERT(   CUT_CMP_EQ      , CUT_TYP_HEX , fail, 0 , (int)exp, (int)act)
#define cut_PtrEQ_M(        fail, exp, act, fmt...)     CUT_ASSERT_M( CUT_CMP_EQ      , CUT_TYP_HEX , fail, 0 , (int)exp, (int)act, fmt)
#define cut_PtrGE(          fail, exp, act)             CUT_ASSERT(   CUT_CMP_LT      , CUT_TYP_HEX , fail, CUT_FLAG_NEGATE, (int)exp, (int)act)
#define cut_PtrGE_M(        fail, exp, act, fmt...)     CUT_ASSERT_M( CUT_CMP_LT      , CUT_TYP_HEX , fail, CUT_FLAG_NEGATE, (int)exp, (int)act, fmt)
#define cut_PtrGT(          fail, exp, act)             CUT_ASSERT(   CUT_CMP_GT      , CUT_TYP_HEX , fail, 0 , (int)exp, (int)act)
#define cut_PtrGT_M(        fail, exp, act, fmt...)     CUT_ASSERT_M( CUT_CMP_GT      , CUT_TYP_HEX , fail, 0 , (int)exp, (int)act, fmt)
#define cut_PtrLE(          fail, exp, act)             CUT_ASSERT(   CUT_CMP_GT      , CUT_TYP_HEX , fail, CUT_FLAG_NEGATE, (int)exp, (int)act)
#define cut_PtrLE_M(        fail, exp, act, fmt...)     CUT_ASSERT_M( CUT_CMP_GT      , CUT_TYP_HEX , fail, CUT_FLAG_NEGATE, (int)exp, (int)act, fmt)
#define cut_PtrLT(          fail, exp, act)             CUT_ASSERT(   CUT_CMP_LT      , CUT_TYP_HEX , fail, 0 , (int)exp, (int)act)
#define cut_PtrLT_M(        fail, exp, act, fmt...)     CUT_ASSERT_M( CUT_CMP_LT      , CUT_TYP_HEX , fail, 0 , (int)exp, (int)act, fmt)
#define cut_PtrNE(          fail, exp, act)             CUT_ASSERT(   CUT_CMP_EQ      , CUT_TYP_HEX , fail, CUT_FLAG_NEGATE, (int)exp, (int)act)
#define cut_PtrNE_M(        fail, exp, act, fmt...)     CUT_ASSERT_M( CUT_CMP_EQ      , CUT_TYP_HEX , fail, CUT_FLAG_NEGATE, (int)exp, (int)act, fmt)
#define cut_PtrNotNull(     fail, exp, act)             CUT_ASSERT(   CUT_CMP_EQ      , CUT_TYP_HEX , fail, CUT_FLAG_NEGATE, (int)exp, NULL)
#define cut_PtrNotNull_M(   fail, exp, act, fmt...)     CUT_ASSERT_M( CUT_CMP_EQ      , CUT_TYP_HEX , fail, CUT_FLAG_NEGATE, (int)exp, NULL, fmt)
#define cut_PtrNull(        fail, exp, act)             CUT_ASSERT(   CUT_CMP_EQ      , CUT_TYP_HEX , fail, 0 , (int)exp, NULL)
#define cut_PtrNull_M(      fail, exp, act, fmt...)     CUT_ASSERT_M( CUT_CMP_EQ      , CUT_TYP_HEX , fail, 0 , (int)exp, NULL, fmt)
#define cut_StrABegE(       fail, exp, act)             CUT_ASSERT(   CUT_CMP_STR_BEG , CUT_TYP_STR , fail, 0, (int)exp, (int)act)
#define cut_StrABegE_M(     fail, exp, act, fmt...)     CUT_ASSERT_M( CUT_CMP_STR_BEG , CUT_TYP_STR , fail, 0, (int)exp, (int)act, fmt)
#define cut_StrAContE(      fail, exp, act)             CUT_ASSERT(   CUT_CMP_STR_CONT, CUT_TYP_STR , fail, 0, (int)exp, (int)act)
#define cut_StrAContE_M(    fail, exp, act, fmt...)     CUT_ASSERT_M( CUT_CMP_STR_CONT, CUT_TYP_STR , fail, 0, (int)exp, (int)act, fmt)
#define cut_StrAEndE(       fail, exp, act)             CUT_ASSERT(   CUT_CMP_STR_END , CUT_TYP_STR , fail, 0, (int)exp, (int)act)
#define cut_StrAEndE_M(     fail, exp, act, fmt...)     CUT_ASSERT_M( CUT_CMP_STR_END , CUT_TYP_STR , fail, 0, (int)exp, (int)act, fmt)
#define cut_StrANotBegE(    fail, exp, act)             CUT_ASSERT(   CUT_CMP_STR_BEG , CUT_TYP_STR , fail, CUT_FLAG_NEGATE|CUT_FLAG_STRSWAP, (int)exp, (int)act)
#define cut_StrANotBegE_M(  fail, exp, act, fmt...)     CUT_ASSERT_M( CUT_CMP_STR_BEG , CUT_TYP_STR , fail, CUT_FLAG_NEGATE|CUT_FLAG_STRSWAP, (int)exp, (int)act, fmt)
#define cut_StrANotContE(   fail, exp, act)             CUT_ASSERT(   CUT_CMP_STR_CONT, CUT_TYP_STR , fail, CUT_FLAG_NEGATE, (int)exp, (int)act)
#define cut_StrANotContE_M( fail, exp, act, fmt...)     CUT_ASSERT_M( CUT_CMP_STR_CONT, CUT_TYP_STR , fail, CUT_FLAG_NEGATE, (int)exp, (int)act, fmt)
#define cut_StrANotEndE(    fail, exp, act)             CUT_ASSERT(   CUT_CMP_STR_END , CUT_TYP_STR , fail, CUT_FLAG_NEGATE|CUT_FLAG_STRSWAP, (int)exp, (int)act)
#define cut_StrANotEndE_M(  fail, exp, act, fmt...)     CUT_ASSERT_M( CUT_CMP_STR_END , CUT_TYP_STR , fail, CUT_FLAG_NEGATE|CUT_FLAG_STRSWAP, (int)exp, (int)act, fmt)
#define cut_StrEBegA(       fail, exp, act)             CUT_ASSERT(   CUT_CMP_STR_BEG , CUT_TYP_STR , fail, CUT_FLAG_STRSWAP, (int)exp, (int)act)
#define cut_StrEBegA_M(     fail, exp, act, fmt...)     CUT_ASSERT_M( CUT_CMP_STR_BEG , CUT_TYP_STR , fail, CUT_FLAG_STRSWAP, (int)exp, (int)act, fmt)
#define cut_StrEContA(      fail, exp, act)             CUT_ASSERT(   CUT_CMP_STR_CONT, CUT_TYP_STR , fail, CUT_FLAG_STRSWAP, (int)exp, (int)act)
#define cut_StrEContA_M(    fail, exp, act, fmt...)     CUT_ASSERT_M( CUT_CMP_STR_CONT, CUT_TYP_STR , fail, CUT_FLAG_STRSWAP, (int)exp, (int)act, fmt)
#define cut_StrEEndA(       fail, exp, act)             CUT_ASSERT(   CUT_CMP_STR_END , CUT_TYP_STR , fail, CUT_FLAG_STRSWAP, (int)exp, (int)act)
#define cut_StrEEndA_M(     fail, exp, act, fmt...)     CUT_ASSERT_M( CUT_CMP_STR_END , CUT_TYP_STR , fail, CUT_FLAG_STRSWAP, (int)exp, (int)act, fmt)
#define cut_StrENotBegA(    fail, exp, act)             CUT_ASSERT(   CUT_CMP_STR_BEG , CUT_TYP_STR , fail, CUT_FLAG_NEGATE, (int)exp, (int)act)
#define cut_StrENotBegA_M(  fail, exp, act, fmt...)     CUT_ASSERT_M( CUT_CMP_STR_BEG , CUT_TYP_STR , fail, CUT_FLAG_NEGATE, (int)exp, (int)act, fmt)
#define cut_StrENotContA(   fail, exp, act)             CUT_ASSERT(   CUT_CMP_STR_CONT, CUT_TYP_STR , fail, CUT_FLAG_NEGATE|CUT_FLAG_STRSWAP, (int)exp, (int)act)
#define cut_StrENotContA_M( fail, exp, act, fmt...)     CUT_ASSERT_M( CUT_CMP_STR_CONT, CUT_TYP_STR , fail, CUT_FLAG_NEGATE|CUT_FLAG_STRSWAP, (int)exp, (int)act, fmt)
#define cut_StrENotEndA(    fail, exp, act)             CUT_ASSERT(   CUT_CMP_STR_END , CUT_TYP_STR , fail, CUT_FLAG_NEGATE, (int)exp, (int)act)
#define cut_StrENotEndA_M(  fail, exp, act, fmt...)     CUT_ASSERT_M( CUT_CMP_STR_END , CUT_TYP_STR , fail, CUT_FLAG_NEGATE, (int)exp, (int)act, fmt)
#define cut_StrEQ(          fail, exp, act)             CUT_ASSERT(   CUT_CMP_EQ      , CUT_TYP_STR , fail, 0 , (int)exp, (int)act)
#define cut_StrEQ_M(        fail, exp, act, fmt...)     CUT_ASSERT_M( CUT_CMP_EQ      , CUT_TYP_STR , fail, 0 , (int)exp, (int)act, fmt)
#define cut_StrEmpty(       fail, exp, act)             CUT_ASSERT(   CUT_CMP_EQ      , CUT_TYP_STR , fail, 0, "" , (int)act)
#define cut_StrEmpty_M(     fail, exp, act, fmt...)     CUT_ASSERT_M( CUT_CMP_EQ      , CUT_TYP_STR , fail, 0, "" , (int)act, fmt)
#define cut_StrGE(          fail, exp, act)             CUT_ASSERT(   CUT_CMP_LT      , CUT_TYP_STR , fail, CUT_FLAG_NEGATE, (int)exp, (int)act)
#define cut_StrGE_M(        fail, exp, act, fmt...)     CUT_ASSERT_M( CUT_CMP_LT      , CUT_TYP_STR , fail, CUT_FLAG_NEGATE, (int)exp, (int)act, fmt)
#define cut_StrGT(          fail, exp, act)             CUT_ASSERT(   CUT_CMP_GT      , CUT_TYP_STR , fail, 0 , (int)exp, (int)act)
#define cut_StrGT_M(        fail, exp, act, fmt...)     CUT_ASSERT_M( CUT_CMP_GT      , CUT_TYP_STR , fail, 0 , (int)exp, (int)act, fmt)
#define cut_StrLE(          fail, exp, act)             CUT_ASSERT(   CUT_CMP_GT      , CUT_TYP_STR , fail, CUT_FLAG_NEGATE, (int)exp, (int)act)
#define cut_StrLE_M(        fail, exp, act, fmt...)     CUT_ASSERT_M( CUT_CMP_GT      , CUT_TYP_STR , fail, CUT_FLAG_NEGATE, (int)exp, (int)act, fmt)
#define cut_StrLT(          fail, exp, act)             CUT_ASSERT(   CUT_CMP_LT      , CUT_TYP_STR , fail, 0 , (int)exp, (int)act)
#define cut_StrLT_M(        fail, exp, act, fmt...)     CUT_ASSERT_M( CUT_CMP_LT      , CUT_TYP_STR , fail, 0 , (int)exp, (int)act, fmt)
#define cut_StrNE(          fail, exp, act)             CUT_ASSERT(   CUT_CMP_EQ      , CUT_TYP_STR , fail, CUT_FLAG_NEGATE, (int)exp, (int)act)
#define cut_StrNE_M(        fail, exp, act, fmt...)     CUT_ASSERT_M( CUT_CMP_EQ      , CUT_TYP_STR , fail, CUT_FLAG_NEGATE, (int)exp, (int)act, fmt)
#define cut_StrNotEmpty(    fail, exp, act)             CUT_ASSERT(   CUT_CMP_EQ      , CUT_TYP_STR , fail, CUT_FLAG_NEGATE, "", (int)act)
#define cut_StrNotEmpty_M(  fail, exp, act, fmt...)     CUT_ASSERT_M( CUT_CMP_EQ      , CUT_TYP_STR , fail, CUT_FLAG_NEGATE, "", (int)act, fmt)
#define cut_UIntEQ(         fail, exp, act)             CUT_ASSERT(   CUT_CMP_EQ      , CUT_TYP_UINT, fail, 0 , exp, act)
#define cut_UIntEQ_M(       fail, exp, act, fmt...)     CUT_ASSERT_M( CUT_CMP_EQ      , CUT_TYP_UINT, fail, 0 , exp, act, fmt)
#define cut_UIntGE(         fail, exp, act)             CUT_ASSERT(   CUT_CMP_LT      , CUT_TYP_UINT, fail, CUT_FLAG_NEGATE, exp, act)
#define cut_UIntGE_M(       fail, exp, act, fmt...)     CUT_ASSERT_M( CUT_CMP_LT      , CUT_TYP_UINT, fail, CUT_FLAG_NEGATE, exp, act, fmt)
#define cut_UIntGT(         fail, exp, act)             CUT_ASSERT(   CUT_CMP_GT      , CUT_TYP_UINT, fail, 0 , exp, act)
#define cut_UIntGT_M(       fail, exp, act, fmt...)     CUT_ASSERT_M( CUT_CMP_GT      , CUT_TYP_UINT, fail, 0 , exp, act, fmt)
#define cut_UIntLE(         fail, exp, act)             CUT_ASSERT(   CUT_CMP_GT      , CUT_TYP_UINT, fail, CUT_FLAG_NEGATE, exp, act)
#define cut_UIntLE_M(       fail, exp, act, fmt...)     CUT_ASSERT_M( CUT_CMP_GT      , CUT_TYP_UINT, fail, CUT_FLAG_NEGATE, exp, act, fmt)
#define cut_UIntLT(         fail, exp, act)             CUT_ASSERT(   CUT_CMP_LT      , CUT_TYP_UINT, fail, 0 , exp, act)
#define cut_UIntLT_M(       fail, exp, act, fmt...)     CUT_ASSERT_M( CUT_CMP_LT      , CUT_TYP_UINT, fail, 0 , exp, act, fmt)
#define cut_UIntNE(         fail, exp, act)             CUT_ASSERT(   CUT_CMP_EQ      , CUT_TYP_UINT, fail, CUT_FLAG_NEGATE, exp, act)
#define cut_UIntNE_M(       fail, exp, act, fmt...)     CUT_ASSERT_M( CUT_CMP_EQ      , CUT_TYP_UINT, fail, CUT_FLAG_NEGATE, exp, act, fmt)



/* END  OF FILE */
