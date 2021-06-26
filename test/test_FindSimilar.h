#ifndef TEST_FINDSIMILAR_H
#define TEST_FINDSIMILAR_H

#include "acutest.h"
#include "FindSimilar.h"
#include "api.h"
#include "Utility.h"
#include <time.h>

/*
* MID: 9069
* Threshold: 0.150000
* Query ID : 
4922: 238 384 696 783 835 1212 1766 2280 2515 3481 4600 5672 6296 7108 7265 7370 7735 8045 8552 8731 8760 8770 9229 
*/
void test_FS_data(void){
    
    int num_mail;
    mail* mails;
    int* list = (int*)malloc(sizeof(int)*MAX_N_MAIL);
    int nlist;
    get_mails("test/data/test.in", &mails, &num_mail);
  
    //Problem
    //ID: 5
    int mid = 9451;
    double thd = 0.17;
    //Answer
    int ans[] = {1597, 4026, 4122, 5123, 7033, 7176, 7802, 7845}; 
    int lans = 8;
    infoFs infs;

    init_FS(&infs);
    proc_FS(&infs, mails, num_mail);

    //Solve
    answer_FS(&infs, mails, mid, num_mail, thd, list, &nlist);

    //Validate
    TEST_CHECK(lans == nlist);
    TEST_MSG("Expected: %d, Got %d", lans, nlist);
    for(int i=0;i<lans;i++){
        TEST_CHECK(list[i]==ans[i]);
        TEST_MSG("Exp: %d, Got: %d", ans[i], list[i]);
    }


    //GC
    free(list);
    kill_FS(&infs);
}


void void_test_matrix(void){
    Matrix_ushort M; 
    init_Matrix_ushort(&M, 1000, 200);
    M.m[999][199] = 13;
    TEST_CHECK(M.m[999][199]==13);
    TEST_CHECK(M.m[999][194]==0);
}

#endif