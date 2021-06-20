#include <stdio.h>

#include "acutest.h"

#include "test_utils.h"
#include "test_tokenize.h"
#include "test_GenericStack.h"

// Run TESTs 
TEST_LIST = {
    {"Utility", test_utils},
    {"Tokenize", test_popToken},
    {"Tokenize2", test_token},
    {"Generic Array (int)", test_dynamic_universal_array},
    {"Generic Stack (int)", test_stack_INT},
    {"Int array insert", array_compare},
    {"Int array append", test_array_append_int},
    {"Long array append", test_array_append_long},
    {NULL, NULL} // Terminate the test
};