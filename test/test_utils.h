#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include "acutest.h"
#include "utils.h"
#include "Utility.h"

void test_utils(void)
{
    int a, b;
    a = 1; b= 2;
    TEST_CHECK(argmax(a,b)  == 1 );
    TEST_CHECK(argmax(b,a) == 0);
    TEST_CHECK(argmax(1,1) == 1);
}

void readmail(void){
    int num_mail;
    mail* mails;
    get_mails("test/data/test.in", &mails, &num_mail);
}


#endif