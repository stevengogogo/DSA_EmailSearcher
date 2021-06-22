#include "FindSimilar.h"


void init_MEM(struct MEMORY* mem, int len){
    mem->LEN = len;
    mem->ARRAY = (int*)malloc(mem->LEN*sizeof(int));
    assert(mem->ARRAY != NULL);
    mem->top_unused = 0;
}

void kill_MEM(struct MEMORY* mem){
    free(mem->ARRAY);
    mem->ARRAY = NULL;
    mem->LEN = 0;
    mem->top_unused = EMTY_QUE_SIG;
}

void Init_MEM_GroupAnalysis(TxtSmry** smrys, int n_mails){
    TokenInfo* tkf = NULL;
    //Location of hashes
    init_MEM(&loc_mem, n_mails*Q_MODULO*INIT_SPURIOUS_COUNT);
    //Occupied hash index
    init_MEM(&existTokens_mem, n_mails*INIT_UNIQUE_TOKEN_SIZE);
    init_TokenInfo_arr(&tkf, n_mails*Q_MODULO);
    init_TxtSmry_arr(smrys, n_mails, tkf, existTokens_mem);

}

void kill_MEM_GroupAnalysis(TxtSmry* smrys){
    kill_MEM(&loc_mem);
    kill_MEM(&existTokens_mem);
    kill_TokenInfo_arr(smrys[0].token);
}


void init_TokenInfo(TokenInfo* tkf, int* mem){
    tkf->occur = 0;
    tkf->loc = mem;
    tkf->isRealloc = false;
}

void init_TokenInfo_arr(TokenInfo** tkf, int len){
    *tkf = (TokenInfo*)malloc(sizeof(TokenInfo)*len);
    assert(tkf!=NULL);
    for(int i=0;i<len;i++){
        assert(loc_mem.top_unused < loc_mem.LEN);
        init_TokenInfo(tkf[i], loc_mem.ARRAY[loc_mem.top_unused]);
        ++loc_mem.top_unused;
    }
}


void kill_TokenInfo_arr(TokenInfo* tkf){
    free(tkf);
}


void init_TxtSmry(TxtSmry* smry, TokenInfo* memToken, int pin_Token, MEMORY* memExistToken, int pin_ExistToken){
    smry->token = &memToken[pin_Token];
    smry->existTokens = &memExistToken->ARRAY[pin_ExistToken];
    smry->nToken = 0;
    smry->text = NULL;
    smry->synced = false;
    smry->isRealloc_existTokens = false;
}

void init_TxtSmry_arr(TxtSmry** smry, int len){
    *smry = (TxtSmry*)malloc(len*sizeof(TxtSmry));
    assert(*smry != NULL);
    
    for(int i=0;i<len;i++){
        init_TxtSmry(&(*smry)[i], );
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

TxtSmry* Preprocess_GroupAnalysis(mail*  mails, int n_mails){
    TxtSmry* smrys;
    Init_MEM_GroupAnalysis(&smrys, n_mails);
    return smrys;
}


void kill_GroupAnalysis(TxtSmry* smrys){
    kill_MEM_GroupAnalysis(smrys);
}