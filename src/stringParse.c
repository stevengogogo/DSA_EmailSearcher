#include "stringParse.h"


int popToken(char message[], char token[], int iStr){
    iStr = sscanf( &message[iStr], REGULAR_EXPR, token);
    return iStr;
}