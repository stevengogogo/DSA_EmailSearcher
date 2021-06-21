#include "GroupAnalysis.h"

void init_TokenInfo(TokenInfo* tkf){
    tkf->occur = 0;
    init_dymArr(&tkf->loc, 1);
}

void init_TokenInfo_arr(TokenInfo* tkf, int len){
    for(int i=0;i<len;i++)
        init_TokenInfo(&tkf[i]);
}

void kill_TokenInfo(TokenInfo* tkf){
    kill_dymArr(&tkf->loc);
    tkf->occur = 0;
}

void kill_TokenInfo_arr(TokenInfo* tkf, int len){
    for(int i=0; i<len;i++){
        kill_TokenInfo(&tkf[i]);
    }
}


void init_TxtSmry(TxtSmry* smry){
    smry->nonZero;
    init_TokenInfo_arr(smry->token, Q_MODULO);
    init_dymArr(&smry->nonZero, INIT_NONZERO_SIZE);
    smry->nToken = 0;
    smry->text = (char*)malloc(MAX_CONTENT_SIZE*sizeof(char));
    smry->synced = false;
}

void init_TxtSmry_arr(TxtSmry** smry, int len){
    *smry = (TxtSmry*)malloc(len*sizeof(TxtSmry));
    
    if (smry==NULL){
        fprintf(stderr, "Memory Error (Txt summary): Insufficient Memory.\n");
        exit(1);
    }

    for(int i=0;i<len;i++){
        init_TxtSmry(&(*smry)[i]);
    }
}

void kill_TxtSmry(TxtSmry* smry){
    kill_TokenInfo_arr(smry->token, Q_MODULO);
    kill_dymArr(&smry->nonZero);
    free(smry->text);
    //smry->nToken = 0;
    //smry->synced = false;
}

void kill_TxtSmry_arr(TxtSmry* smry, int len){
    for(int i=0;i<len;i++)
        kill_TxtSmry(&smry[i]);
    free(smry);
}