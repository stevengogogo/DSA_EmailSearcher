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
    init_MEM_SHORT(&token_hashmaps, num_mail*INIT_SPURIOUS_COUNT);

    TEST_CHECK(token_hashmaps.LEN == num_mail*INIT_SPURIOUS_COUNT);
    TEST_CHECK(token_hashmaps.top_unused == 0);
    
    //Garbage Collection
    kill_MEM_SHORT(&token_hashmaps);
    TEST_CHECK(token_hashmaps.ARRAY == NULL);
    TEST_CHECK(token_hashmaps.LEN == 0);
}

void test_init_FS(void){
    TxtSmry* smrys;
    int n_mails=10000;
    clock_t str;
    clock_t end;


    str = clock();
    Init_FindSimilar(&smrys, n_mails);
    end = clock();
    print_clock("Init: ",str, end);

    
    str = clock();
    kill_FindSimilar(smrys, n_mails);
    end = clock();
    print_clock(" GC: ",str, end);
}

void test_init_content_FS(void){
    TxtSmry* smrys;
    int n_mails=10000;

    Init_FindSimilar(&smrys, n_mails);

    //Initial values
    for(int i=0;i<n_mails;i++){
        TEST_CHECK(smrys[i].nToken == 0);
        TEST_CHECK(smrys[i].isExistTokens_DymArr == false);
        TEST_CHECK(smrys[i].synced == false);
        TEST_CHECK(smrys[i].text == NULL);
        TEST_CHECK(smrys[i].token[0].count == 0);
        TEST_CHECK(smrys[i].token[230].count == 0);
    }
    
    //The token array is 0 in default
    for(int i=0;i<Q_MODULO;i++){
        TEST_CHECK(smrys[n_mails-1].token[i].count==0);
        TEST_CHECK(smrys[234].token[i].count==0);
        TEST_CHECK(smrys[0].token[i].count==0);
    }

    for(int i=0;i<INIT_SPURIOUS_COUNT;i++){
        TEST_CHECK(smrys[n_mails-1].token[0].loc[i]==0);
    }

    kill_FindSimilar(smrys, n_mails);
}

void test_append_hash(void){
    TxtSmry* smrys;
    int n_mails=10000;

    Init_FindSimilar(&smrys, n_mails);

    for(int i=0;i<INIT_UNIQUE_TOKEN_SIZE-1;i++){
        add_unique_hashlist(&smrys[0], i);
    }

    TEST_CHECK(smrys[0].isExistTokens_DymArr == false);
    TEST_CHECK(smrys[0].existTokens_DymArr == NULL);

    add_unique_hashlist(&smrys[0], INIT_UNIQUE_TOKEN_SIZE-1);
    add_unique_hashlist(&smrys[0], INIT_UNIQUE_TOKEN_SIZE);
    TEST_CHECK(smrys[0].isExistTokens_DymArr == true);
    TEST_CHECK(smrys[0].existTokens_DymArr != NULL);

    for(int i=INIT_UNIQUE_TOKEN_SIZE+1;i<30*INIT_UNIQUE_TOKEN_SIZE;i++){
        add_unique_hashlist(&smrys[0], i);
    }    

    for(ULONG i=0;i<30*INIT_UNIQUE_TOKEN_SIZE;i++){
        TEST_CHECK(get_unique_hashlist(&smrys[0], (int)i) == i );
        TEST_MSG("Expected %lld; Got %lld", get_unique_hashlist(&smrys[0], (int)i),i);;
    }





    
    kill_FindSimilar(smrys, n_mails);
}

void test_summary_FS(void){
    mail* mails;
    int n_mail;
    get_mails("test/data/test.in", &mails, &n_mail);
    free(mails);
}





#endif