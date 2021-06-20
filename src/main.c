#include "api.h"
#include "ExpressionMatch.h"
#include "FindSimilar.h"
#include "GroupAnalysis.h"
#include "utils.h"
#include <stdio.h>
#include <time.h>

// The testdata only contains the first 100 mails (mail1 ~ mail100)
// and 2000 queries for you to debug.

int main(void) {
    int num = 100000;
    int maxlen = INIT_NUM_ARRAY_ELEMENT;
    int* arr = (int*)malloc(maxlen*sizeof(int));
    int len = 0;

    clock_t str = clock();
    for(int i=0;i<num;i++){
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
    //print_clock("\nArray Insert", str, end);

  return 0;
}
