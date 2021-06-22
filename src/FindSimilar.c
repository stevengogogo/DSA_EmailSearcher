#include "FindSimilar.h"

void init_LOC_MEM(struct LOC_MEM* loc_mem, int num_mail){
    loc_mem->LEN = num_mail * Q_MODULO;
    loc_mem->ARRAY = (int*)malloc(loc_mem->LEN*sizeof(int));
    loc_mem->top_unused = 0;
}

void kill_LOC_MEM(struct LOC_MEM* loc_mem){
    free(loc_mem->ARRAY);
    loc_mem->ARRAY = NULL;
    loc_mem->LEN = 0;
    loc_mem->top_unused = EMTY_QUE_SIG;
}


void init_TokenInfo(TokenInfo* tkf){
    tkf->occur = 0;
    //init_dymArr(&tkf->loc, 1);
}

void init_TokenInfo_arr(TokenInfo* tkf, int len){
    for(int i=0;i<len;i++)
        init_TokenInfo(&tkf[i]);
}

void kill_TokenInfo(TokenInfo* tkf){
    //kill_dymArr(&tkf->loc);
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
    smry->text = NULL;
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