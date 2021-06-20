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
        uArray arr;
    init_uArray(&arr, sizeof(long));
    int num = 15000;
    int item;
    long i;
    clock_t str;
    clock_t end;

    str = clock();
    for(i=0;i<num;i++){
        append_uArray(&arr, &i); //[1...100000]
    }
    end = clock();
    //print_clock("uArray Append",str, end);

  return 0;
}
