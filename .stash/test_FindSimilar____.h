#ifndef TEST_FINDSIMILAR_H
#define TEST_FINDSIMILAR_H

#include "acutest.h"
#include "FindSimilar.h"
#include "api.h"
#include "Utility.h"
#include <time.h>

void test_powerArray(void){
    init_PowerArray(PowerArray, MAX_TOKEN_LEN, D_RABIN, Q_RABIN);

    TEST_CHECK(power_long(10,0) == 1);
    TEST_CHECK(power_long(10,1) == 10);
    TEST_CHECK(power_long(10,2) == 100);
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
    kill_FindSimilar(smrys);
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
        _add_unique_hashlist(&smrys[0], i);
    }

    TEST_CHECK(smrys[0].isExistTokens_DymArr == false);
    TEST_CHECK(smrys[0].existTokens_DymArr == NULL);

    _add_unique_hashlist(&smrys[0], INIT_UNIQUE_TOKEN_SIZE-1);
    _add_unique_hashlist(&smrys[0], INIT_UNIQUE_TOKEN_SIZE);
    TEST_CHECK(smrys[0].isExistTokens_DymArr == true);
    TEST_CHECK(smrys[0].existTokens_DymArr != NULL);

    for(int i=INIT_UNIQUE_TOKEN_SIZE+1;i<30*INIT_UNIQUE_TOKEN_SIZE;i++){
        _add_unique_hashlist(&smrys[0], i);
    }    

    for(int i=0;i<30*INIT_UNIQUE_TOKEN_SIZE;i++){
        TEST_CHECK(get_unique_hashlist(&smrys[0], (int)i) == i );
        TEST_MSG("Expected %d; Got %d", get_unique_hashlist(&smrys[0], (int)i),i);;
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
    int hashExp;

    /*Expected iteration*/
    int iEndExp[5] =  {4,8,19,25, -1};//expected stop site
    char iEndExpSr[4] = {' ','+',' ','?'};
    for(int i=0;i<4;i++){
        TEST_CHECK(text[iEndExp[i]]==iEndExpSr[i]);
        TEST_MSG("Got %c at site %d (C: %c)", iEndExpSr[i], iEndExp[i], text[iEndExp[i]]);
    }

    int i = 0;
    int j = 0;
    while(1){
        iEnd = popTokenHash(text, token, iStr, &hash);
        if(token[0]!='\0' ){
            TEST_CHECK(iEnd == iEndExp[i]);
            TEST_MSG("iEnd=%d(%c); Expected=%d(%c); Token: %s", iEnd, text[iEnd],iEndExp[i], text[iEndExp[i]], token);
            TEST_CHECK(i<= strlen(text));
            TEST_CHECK(strncmp(tokenStr[j],token,strlen(token))==0);

            //Hash
            hashExp = HashString(token, D_RABIN, Q_RABIN);
            TEST_CHECK(hashExp == hash);
            TEST_MSG("Got %d; Exp: %d; token: %s", hash, hashExp, token);
            ++j;
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

void test_summarize(void){
    int num_mail;
    mail* mails;
    TxtSmry* smrys;
    clock_t str;
    clock_t end;

    get_mails("test/data/test.in", &mails, &num_mail);

    Init_FindSimilar(&smrys, num_mail);

    Preprocess_FindSimilar(smrys, mails, 30);

    kill_FindSimilar(smrys, num_mail);
    free(mails);
}

void test_summarize_benchmark(void){
    int num_mail;
    mail* mails;
    int countOver=0;
    TxtSmry* smrys;
    clock_t str;
    clock_t end;

    get_mails("test/data/test.in", &mails, &num_mail);

    Init_FindSimilar(&smrys, num_mail);
    
    str = clock();
    Preprocess_FindSimilar(smrys, mails, num_mail);
    end = clock();
    print_clock("(10000 email)Time: ", str, end);

    for(int i=0;i<num_mail;i++){
        if(smrys[i].maxSpurious>0){
            ++countOver;
        }
    }
    printf(" Spurious Overflow: %d/%d", countOver, num_mail);

    for(int i=0;i<num_mail;i++){
        if( smrys[i].maxSpurious > 0){
        //printf(" Max Spurious: %d (out of %d unique hash)\n",smrys[i].maxSpurious, smrys[i].nToken);
        }
    }

    kill_FindSimilar(smrys, num_mail);
    free(mails);
}


void test_tokenhash(void){
    char text[10000] = "aefarqt4qq5b342344f fwe++--~~~huhfa1+---23I faead we t+ga\0";
    char token1[1000];
    char token2[1000];
    int i1 = 0;
    int i2 = 0;
    int h;

    while(1){
        i1 = popTokenHash(text, token1, i1, &h);
        i2 = popToken(text, token2, i2);

        
        TEST_CHECK(strcmp(token1,token2)==0);
        TEST_CHECK(i1==i2);
        //TEST_CHECK(i1==i2);
        if(i2==-1){
            break;
        }
    }
    
}

/*
* MID: 9069
* Threshold: 0.150000
* Query ID : 
4922: 238 384 696 783 835 1212 1766 2280 2515 3481 4600 5672 6296 7108 7265 7370 7735 8045 8552 8731 8760 8770 9229 
*/
void test_FS_data(void){
    
    int num_mail;
    mail* mails;
    TxtSmry* smrys;
    int* list = (int*)malloc(sizeof(int)*MAX_N_MAIL);
    int nlist;
    get_mails("test/data/test.in", &mails, &num_mail);

    //Problem
    int mid = 9069;
    double thd = 0.15;
    //Answer
    int ans[] = {238, 384, 696, 783, 835, 1212, 1766, 2280, 2515, 3481, 4600, 5672, 6296, 7108, 7265, 7370, 7735, 8045, 8552, 8731, 8760, 8770, 9229}; 
    int lans = 23;


    Init_FindSimilar(&smrys, num_mail);

    Preprocess_FindSimilar(smrys, mails, num_mail);

    //Solve
    answer_FindSimilar(smrys, mid, thd, num_mail, list, &nlist);

    //Validate
    TEST_CHECK(lans == nlist);
    TEST_MSG("Expected: %d, Got %d", lans, nlist);
    for(int i=0;i<lans;i++){
        TEST_CHECK(list[i]==ans[i]);
        TEST_MSG("Exp: %d, Got: %d", ans[i], list[i]);
    }

    printf("\n");
    for(int i=0;i<nlist;i++){
        printf("%d ", list[i]);
    }


    //GC
    free(list);
    kill_FindSimilar(smrys, num_mail);
}

#endif