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
    {"Generic Stack (int)", test_stack_INT},
    {NULL, NULL} // Terminate the test
};