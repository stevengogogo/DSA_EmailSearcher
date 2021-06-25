#ifndef TEST_FINDSIMILAR_H
#define TEST_FINDSIMILAR_H

#include "acutest.h"
#include "FindSimilar.h"
#include "api.h"
#include "Utility.h"
#include <time.h>

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

#endif