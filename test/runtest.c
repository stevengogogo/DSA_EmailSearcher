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
    //Generic Array
    //{"Generic Array (int)", test_dynamic_universal_array},
    //{"Int array insert", array_compare},
    //{"Int uArray append", test_uarray_append_int},
    //{"Int array append", test_array_append_int},
    //{"Long uArray append", test_uarray_append_long},
    //{"Long array append", test_array_append_long},
    {"Struct uArray append", test_uarray_append_struct},
    {"Struct array append", test_array_struct},
    //Dynamic Array,
    {"Dyanmic Array", test_array},
    {"Queue",test_queue},
    {"Read email", readmail},
    {"GA: init", test_init_GA},
    {"GA: summary", test_summary_GA},
    {NULL, NULL} // Terminate the test
};