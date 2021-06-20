#ifndef TEST_GENERICSTACK_H
#define TEST_GENERICSTACK_H

#include "utils.h"

void test_dynamic_universal_array(void){
    uArray arr;
    init_uArray(&arr, sizeof(int));
    int num = 100000;
    int item;

    //Append Item
    for(int i=0;i<num;i++){
        append_uArray(&arr, &i); //[1...100000]
    }

    //Get item
    for(int i=0;i<num;i++){
        get_uArray(&arr, i, &item);
        TEST_CHECK(item==i);
        TEST_MSG("Got %d; Expected %d", item, i);
    }

    kill_uArray(&arr);
}

void test_stack_INT(void){
    uStack s;
    //Initiate a stack with integer storage
    init_uStack(&s, sizeof(int));

}




#endif