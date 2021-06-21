#ifndef GROUPANALYSIS_H
#define GROUPANALYSIS_H
#include "utils.h"
#define Q 100000
/** Token Information*/
typedef struct TokenInfo{
    int occur;
    dymArr* loc;
} TokenInfo;

/** Text Summary*/
typedef struct TxtSmry{
    TokenInfo token[Q];
    dymArr* nonZero; //Token locations
    int nToken;
} TxtSmry;


#endif