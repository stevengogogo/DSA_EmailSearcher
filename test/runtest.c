#include <stdio.h>

#include "acutest.h"

#include "test_utils.h"
#include "test_tokenize.h"

// Run TESTs 
TEST_LIST = {
    {"Utility", test_utils},
    {"Tokenize", test_popToken},
    {NULL, NULL} // Terminate the test
};