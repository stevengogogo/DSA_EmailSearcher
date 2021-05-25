#include "api.h"
#include "utils.h"
#include <stdio.h>
#include "stringParse.h"

// The testdata only contains the first 100 mails (mail1 ~ mail100)
// and 2000 queries for you to debug.

int main(void)
{
      char message[] = "I23 have1 A_ very- good) (dAy+";
    int n_token = 6;
    char tokenStr[6][300] ={ 
        "i23",
        "have1",
        "a",
        "very",
        "good",
        "day"
    };


    char token[2048];
    int iStr = 0;

    for (int i=0;i<n_token;i++){
        iStr = popToken(message, token, iStr);
        if(strcmp(token, tokenStr[i]) == 0);
          printf("Expected: %s ; Got: %s (%d)\n",tokenStr[i], token, iStr);
    }

  return 0;
}
