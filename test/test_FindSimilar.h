#ifndef TEST_FINDSIMILAR_H
#define TEST_FINDSIMILAR_H

#include "acutest.h"
#include "FindSimilar.h"
#include "api.h"
#include "Utility.h"
#include <time.h>

void memory_allocation_FS(void){
    int num_mail = 10;
    
    //Initiation
    init_MEM(&loc_mem, num_mail*INIT_SPURIOUS_COUNT);

    TEST_CHECK(loc_mem.LEN == num_mail*INIT_SPURIOUS_COUNT);
    TEST_CHECK(loc_mem.top_unused == 0);
    
    //Garbage Collection
    kill_MEM(&loc_mem);
    TEST_CHECK(loc_mem.ARRAY == NULL);
    TEST_CHECK(loc_mem.LEN == 0);
}

void test_init_FS(void){
    TxtSmry* smrys;
    int n_mails=100;
    clock_t str;
    clock_t end;


    str = clock();
    Init_MEM_GroupAnalysis(&smrys, n_mails);
    end = clock();
    print_clock("Init: ",str, end);
    
    str = clock();
    kill_MEM_GroupAnalysis(smrys);
    end = clock();
    print_clock(" GC: ",str, end);
}
void test_summary_FS(void){
    mail* mails;
    int n_mail;
    get_mails("test/data/test.in", &mails, &n_mail);
}





#endif