#ifndef TEST_GROUPANALYSIS_H
#define TEST_GROUPANALYSIS_H

#include "acutest.h"
#include "GroupAnalysis.h"
#include "api.h"
#include "Utility.h"
#include <time.h>

void test_init_GA(void){
    TxtSmry smry;
    init_TxtSmry(&smry);
    kill_TxtSmry(&smry);
    clock_t str;
    clock_t end;

    int N = 1000;
    TxtSmry* smryArr;

    str = clock();
    init_TxtSmry_arr(&smryArr, N);
    end = clock();
    print_clock("Initiation: ",str, end);

    kill_TxtSmry_arr(smryArr, N);
}
void test_summary_GA(void){
    mail* mails;
    int n_mail;
    get_mails("test/data/test.in", &mails, &n_mail);
}





#endif