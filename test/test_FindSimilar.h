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
    init_MEM_ULONG(&existTokens_mem, num_mail*INIT_UNIQUE_TOKEN_SIZE);

    TEST_CHECK(existTokens_mem.LEN == num_mail*INIT_UNIQUE_TOKEN_SIZE);
    TEST_CHECK(existTokens_mem.top_unused == 0);
    
    //Garbage Collection
    kill_MEM_ULONG(&existTokens_mem);
    TEST_CHECK(existTokens_mem.ARRAY == NULL);
    TEST_CHECK(existTokens_mem.LEN == 0);
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
    for(int i=0;i<Q_RABIN;i++){
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
        TEST_MSG("Expected %ld; Got %ld", get_unique_hashlist(&smrys[0], (int)i),i);;
    }

    
    kill_FindSimilar(smrys, n_mails);
}

void test_summary_FS(void){
    mail* mails;
    int n_mail;
    get_mails("test/data/test.in", &mails, &n_mail);
    free(mails);
}


void test_RabinKarp_hashing(void){
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
    int iEndExp[5] =  {4,8,19,25, -1};//expected stop site
    char iEndExpSr[4] = {' ','+',' ','?'};
    for(int i=0;i<4;i++){
        TEST_CHECK(text[iEndExp[i]]==iEndExpSr[i]);
        TEST_MSG("Got %c at site %d (C: %c)", iEndExpSr[i], iEndExp[i], text[iEndExp[i]]);
    }

    int i = 0;
    while(1){
        iEnd = popTokenHash(text, token, iStr, &hash);
        if(token[0]!='\0' ){
            TEST_CHECK(iEnd == iEndExp[i]);
            TEST_MSG("iEnd=%d(%c); Expected=%d(%c); Token: %s", iEnd, text[iEnd],iEndExp[i], text[iEndExp[i]], token);
            TEST_CHECK(i<= strlen(text));
        }


        if(iEnd==-1){
            break;
        }
        else{
            iStr = iEnd;
            ++i;
        }
    }

    TEST_CHECK(i ==5-1 );
    TEST_MSG("i=%d", i);


}


#endif