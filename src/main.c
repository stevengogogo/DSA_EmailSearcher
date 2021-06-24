#include "api.h"
#include "ExpressionMatch.h"
#include "FindSimilar.h"
#include "GroupAnalysis.h"
#include "utils.h"
#include <stdio.h>
#include <time.h>

// The testdata only contains the first 100 mails (mail1 ~ mail100)
// and 2000 queries for you to debug.


int main(void) {
    char text[10000] = "What day+--@#4231is today??87\0";
    char tokenStr[5][300] = {
        "what",
        "day",
        "4231is",
        "today",
        "87"
    };

    char token[10000];
    int iStr=0;
    int iEnd;
    int hash;

    /*Expected iteration*/
    int iEndExp[5] =  {4,8,17,19,-1};//expected stop site
    char iEndExpSr[4] = {' ','+',' ','?'};

    int i = 0;
    while(1){
        iEnd = popTokenHash(text, token, iStr, &hash);
        if(token[0]!='\0' ){
            
        }

        if(iEnd==-1){
            break;
        }
        else{
            iStr = iEnd;
            ++i;
        }
    }




  return 0;
}
