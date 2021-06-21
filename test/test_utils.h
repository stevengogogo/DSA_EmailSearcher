#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include "acutest.h"
#include "utils.h"
#include "Utility.h"
#include <string.h>

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

    TEST_CHECK(mails[0].id == 0); 
    TEST_MSG("Got %d\n", mails[0].id);
    TEST_CHECK(strcmp(mails[0].from, "Tim\0")==0); 
    TEST_MSG("Got %s\n", mails[0].from);
    TEST_CHECK(strcmp(mails[0].content, "Got Minas-Rio is an iron ore mining project in Brazil.[1] It is one of the world's largest mining projects, and is initially expected to export 26.5 million tonnes of iron ore in 2013, through a 525km slurry pipeline to a port at Au;[2] production potential is 53 Mtpa or higher.[3] The project was bought by Anglo American PLC, which is facing high costs.[4][5] The mine has certified reserves of 4.6 billion tonnes of itabirite.[6] There have been delays in starting the project, but in December 2010, Anglo American obtained a key license needed from Brazilian government before mining could start.[7][8]  I read the paragraph on http://wikipedia.org\0")==0); 
    TEST_MSG("Got %s\n", mails[0].content);
    TEST_CHECK(strcmp(mails[0].subject, "Minas-Rio\0")==0); 
    TEST_MSG("Got %s\n", mails[0].subject);
    TEST_CHECK(strcmp(mails[0].to, "Tony\0")==0); 
    TEST_MSG("Got %s\n", mails[0].to);
}


#endif