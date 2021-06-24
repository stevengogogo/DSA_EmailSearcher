#include <stdio.h>

#include "acutest.h"

#include "test_utils.h"
#include "test_tokenize.h"
#include "test_GenericStack.h"
#include "test_dymarr.h"
#include "test_FindSimilar.h"
#include "test_GroupAnalysis.h"

// Run TESTs 
TEST_LIST = {
    {"Utility", test_utils},
    //Tokenize
    {"Tokenize", test_popToken},
    {"Tokenize2", test_token},
    {"Regular Expression", test_Regex},
    //Generic Array
    //{"Generic Array (int)", test_dynamic_universal_array},
    //{"Int array insert", array_compare},
    //{"Int uArray append", test_uarray_append_int},
    //{"Int array append", test_array_append_int},
    //{"Long uArray append", test_uarray_append_long},
    //{"Long array append", test_array_append_long},
    //{"Struct uArray append", test_uarray_append_struct},
    //{"Struct array append", test_array_struct},
    //Dynamic Array,
    {"Dyanmic Array", test_array},
    {"Queue",test_queue},
    {"Read email", readmail},
    {"Find Similar: Memory", memory_allocation_FS},
    {"Find Similar: init", test_init_FS},
    {"Find Similar: init content", test_init_content_FS},
    {"Find Similar: append hash",test_append_hash},
    {"Find Similar: summary", test_summary_FS},
    {"Find Similar: Rabin Karp", test_RabinKarp_hashing},
    {NULL, NULL} // Terminate the test
};