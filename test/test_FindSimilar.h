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
    init_MEM(&token_hashmaps, num_mail*INIT_SPURIOUS_COUNT);

    TEST_CHECK(token_hashmaps.LEN == num_mail*INIT_SPURIOUS_COUNT);
    TEST_CHECK(token_hashmaps.top_unused == 0);
    
    //Garbage Collection
    kill_MEM(&token_hashmaps);
    TEST_CHECK(token_hashmaps.ARRAY == NULL);
    TEST_CHECK(token_hashmaps.LEN == 0);
}

void test_init_FS(void){
    TxtSmry* smrys;
    int n_mails=10000;
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

void test_init_content_FS(void){
    TxtSmry* smrys;
    int n_mails=1000;



    Init_MEM_GroupAnalysis(&smrys, n_mails);


    for(int i=0;i<n_mails;i++){
        TEST_CHECK(smrys[i].nToken == 0);
        TEST_CHECK(smrys[i].isRealloc_existTokens == false);
        TEST_CHECK(smrys[i].synced == false);
        TEST_CHECK(smrys[i].text == NULL);
        TEST_CHECK(smrys[i].token[0] == 0);
        TEST_CHECK(smrys[i].token[230] == 0);
    }
    
    for(int i=0;i<Q_MODULO;i++){
        TEST_CHECK(smrys[n_mails-1].token[i]==0);
    }

    kill_MEM_GroupAnalysis(smrys);

}


void test_summary_FS(void){
    mail* mails;
    int n_mail;
    get_mails("test/data/test.in", &mails, &n_mail);
}





#endif