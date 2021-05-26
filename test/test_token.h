#ifndef TEST_TOKEN_H
#define TEST_TOKEN_H

#include "acutest.h"
#include "stringParse.h"
#include <string.h>

void test_token(){
    char message[] = "Dsa Final p-+ro%ject {} \" poopoo";
    int n_token = 6;
    char tokenStr[6][300] ={ 
        "dsa",
        "final",
        "p",
        "ro",
        "ject",
        "poopoo"
    };
    char token[2048];
    int iStr = 0;

    for (int i=0;i<n_token;i++){
        iStr = popToken(message, token, iStr);
        TEST_CHECK(strcmp(token, tokenStr[i]) == 0);
        TEST_MSG("Expected: %s ; Got: %s (%d)\n",tokenStr[i], token, iStr);
    }
}
#endif
