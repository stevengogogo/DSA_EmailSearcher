#ifndef TEST_FINDSIMILAR_H
#define TEST_FINDSIMILAR_H

#include "acutest.h"
#include "FindSimilar.h"
#include "api.h"
#include "Utility.h"
#include <time.h>

/*
void test_powerArray(void){
    init_PowerArray(PowerArray, MAX_TOKEN_LEN, D_RABIN, Q_RABIN);

    TEST_CHECK(PowerArray[0]== 1);
    TEST_CHECK(PowerArray[1]== D_RABIN);
    TEST_CHECK(PowerArray[2]== D_RABIN*D_RABIN);
    TEST_CHECK(PowerArray[3]== D_RABIN*D_RABIN*D_RABIN);
    TEST_MSG("God %ld",PowerArray[0]);
    TEST_CHECK(power_long(10,0) == 1);
    TEST_CHECK(power_long(10,1) == 10);
    TEST_CHECK(power_long(10,2) == 100);

    //Rabin Karp
    TEST_CHECK(Hash_RK("000000\0") == 0);
    TEST_CHECK(Hash_RK("1\0") == 1);
    TEST_CHECK(Hash_RK("2\0") == 2);
    TEST_CHECK(Hash_RK("01\0") == D_RABIN);
    TEST_CHECK(Hash_RK("11\0") == D_RABIN+1);
    TEST_MSG("God %ld",Hash_RK("11"));
}
*/

void test_random(void){
    int len=6;
    long* a = (long*)malloc(sizeof(long)*len);
    long* b = (long*)malloc(sizeof(long)*len);
    
    RandGen_long(a, len, 0, Q_RABIN, 111);
    RandGen_long(b, len, 0, Q_RABIN, 111);
    
    for(int i=0;i<len;i++){
        TEST_CHECK(a[i] == b[i]);
    }

    for(int i=0;i<len;i++){
        printf("%ld ", a[i]);
    }
    
    RandGen_long(b, len, 0, Q_RABIN, 112);
    for(int i=0;i<len;i++){
        TEST_CHECK(a[i] != b[i]);
    }

    free(a);
}

void test_init_FS(void){
    TxtSmry smry;
    int n_mails;
    mail* mails;
    clock_t str;
    clock_t end;

    get_mails("test/data/test.in", &mails, &n_mails);

    str = clock();
    init_FindSimilar(&smry, n_mails);
    end = clock();
    printf("(Q:%d/D:%d)",Q_RABIN,D_RABIN);
    print_clock("Init:",str, end);

    str = clock();
    Preprocess_FindSimilar(&smry, mails, n_mails);
    end = clock();
    printf("\n(Q:%d/D:%d)",Q_RABIN,D_RABIN);
    print_clock("Preprocessing:",str, end);


    /*
    for(int i=0;i<T_MINIHASH_PERM;i++){
        printf("%ld\n", get_Matrix(&smry.SglM, i, 0));
    }
    */

    kill_FindSimilar(&smry);
}

void test_FS_data(void){
    
    int num_mail;
    mail* mails;
    TxtSmry smry;
    int* list = (int*)malloc(sizeof(int)*MAX_N_MAIL);
    int nlist;
    get_mails("test/data/test.in", &mails, &num_mail);

    //Problem
    int mid = 9069;
    double thd = 0.15;
    //Answer
    int ans[] = {238, 384, 696, 783, 835, 1212, 1766, 2280, 2515, 3481, 4600, 5672, 6296, 7108, 7265, 7370, 7735, 8045, 8552, 8731, 8760, 8770, 9229}; 
    int lans = 23;


    init_FindSimilar(&smry, num_mail);

    Preprocess_FindSimilar(&smry, mails, num_mail);

    //Solve
    answer_FindSimilar(&smry, mid, thd, mails, num_mail, list, &nlist);

    //Validate
    TEST_CHECK(lans == nlist);
    TEST_MSG("Expected total emails: %d, Got %d", lans, nlist);
    for(int i=0;i<lans;i++){
        TEST_CHECK(list[i]==ans[i]);
        TEST_MSG("Exp: %d, Got: %d", ans[i], list[i]);
    }

    printf("\n");
    printf("Number of similar item (measured): %d\n", nlist);
    
    /*
    for(int i=0;i<nlist;i++){
        printf("%d ", list[i]);
    }
    */
    


    //GC
    free(list);
    kill_FindSimilar(&smry);
}

//WIP/
void print_token(char s1[], char s2[]){
    char token1[10000];
    char token2[10000];
    long hash;
    int iStr = 0;
    int i1=0;
    int i2=0;
    //String 1
    printf("\n\n");
    while(1){
        iStr = popTokenHash(s1, token1, iStr, &hash);
        if(iStr==-1){
            break;
        }
        printf("%s ", token1);
        ++i1;
    }
    printf("\n\n");
    //String 2
    iStr = 0;
    while(1){
        iStr = popTokenHash(s2, token2, iStr, &hash);
        if(iStr==-1){
            break;
        }
        printf("%s ", token2);
        ++i2;
    }
    printf("\n\n");

}



void test_similarity(void){
    int num_mail;
    mail* mails;
    TxtSmry smry;
    int* list = (int*)malloc(sizeof(int)*MAX_N_MAIL);
    int nlist;
    get_mails("test/data/test.in", &mails, &num_mail);
    
    init_FindSimilar(&smry, num_mail);
    Preprocess_FindSimilar(&smry, mails, num_mail);

    double sim = similarity(&smry.SglM, 0, 1);
    printf("Sim: %f\n", sim);
    printf("Test1:\t%s\n", mails[0].content);
    printf("Test2:\t%s\n", mails[1].content);

    //minihash
    for(int i=0;i<T_MINIHASH_PERM;i++){
        printf("%ld %ld\n", smry.SglM.m[0][i], smry.SglM.m[1][i]);
    }

    print_token( mails[0].content,  mails[1].content);
    kill_FindSimilar(&smry);
}

#endif