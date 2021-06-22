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
    TxtSmry* smrys;
    int n_mails=100000;



    Init_MEM_GroupAnalysis(&smrys, n_mails);

    kill_MEM_GroupAnalysis(smrys);

  return 0;
}
