#ifndef TEST_GENERICSTACK_H
#define TEST_GENERICSTACK_H

#include "utils.h"
#include "time.h"

void print_clock(char* s,clock_t str, clock_t end){
    double total_t = (double)(end - str) / CLOCKS_PER_SEC;
    printf("%s Elapsed %f", s,total_t);
}

void test_dynamic_universal_array(void){
    uArray arr;
    init_uArray(&arr, sizeof(int));
    int num = 15000;
    int item;
    int i;
    clock_t str;
    clock_t end;

    //Append Item
    str = clock();
    for(i=0;i<num;i++){
        append_uArray(&arr, &i); //[1...100000]
    }
    end = clock();
    print_clock("\nuArray Append",str, end);

    //Get item
    str = clock();
    for(i=0;i<num;i++){
        get_uArray(&arr, i, &item);
        TEST_CHECK(item==i);
        TEST_MSG("Got %d; Expected %d", item, i);
    }
    end = clock();
    print_clock("\nuArray Get",str, end);

    //remove item
    str = clock();
    for(i=0;i<num;i++){
        remove_uArray(&arr, arr.len-1);
    }
    TEST_CHECK(arr.len == 0);
    end = clock();
    print_clock("\nuArray remove",str, end);

    //Insert item
    str = clock();
    for(i=0;i<num;i++){
        insert_uArray(&arr, 0, &i); //[1...100000]
    }
    end = clock();
    print_clock("\nuArray Insert",str, end);

    kill_uArray(&arr);
}

void array_compare(void){
    int num = 15000, i;
    int maxlen = INIT_NUM_ARRAY_ELEMENT;
    int* arr = (int*)malloc(maxlen*sizeof(int));
    int len= 0;
    
    //Integer array
    clock_t str = clock();
    for(i=0;i<num;i++){
        ++len;
        if (len==maxlen){
            maxlen = maxlen * 2 + 1;
            arr = realloc(arr,(maxlen)*sizeof(int));
        }

        //Shift right
        for(int j=0;j<len-1;j++){
            arr[j+1] = arr[j];
        }
        //Insert at i
        arr[0] = i;
    }
    clock_t end = clock();
    print_clock("Array Insert", str, end);

}

void test_array_append_int(void){
    int num = 15000, i;
    int maxlen = INIT_NUM_ARRAY_ELEMENT;
    int* arr = (int*)malloc(maxlen*sizeof(int));
    int len= 0;
    //Append
    clock_t str = clock();
    for(i=0;i<num;i++){
        ++len;
        if (len==maxlen){
            maxlen = maxlen * 2 + 1;
            arr = realloc(arr,(maxlen)*sizeof(long));
        }
        arr[len-1] = i;
    }
    clock_t end = clock();
    print_clock("Array Append", str, end);
}

void test_array_append_long(void){
    int num = 15000;
    long i;
    int maxlen = INIT_NUM_ARRAY_ELEMENT;
    long* arr = (long*)malloc(maxlen*sizeof(long));
    int len= 0;
    //Append
    clock_t str = clock();
    for(i=0;i<num;i++){
        ++len;
        if (len==maxlen){
            maxlen = maxlen * 2 + 1;
            arr = realloc(arr,(maxlen)*sizeof(long));
        }
        arr[len-1] = i;
    }
    clock_t end = clock();
    print_clock("Array Append", str, end);
}


void test_stack_INT(void){
    uStack s;
    //Initiate a stack with integer storage
    init_uStack(&s, sizeof(int));
}




#endif