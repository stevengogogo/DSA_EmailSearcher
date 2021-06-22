#include "FindSimilar.h"


void init_MEM(struct MEMORY* mem, ULONG len){
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
    ULONG nmail = (ULONG)n_mails;
    //Location of hashes
    init_MEM(&loc_mem, nmail * Q_MODULO* INIT_SPURIOUS_COUNT);
    //Occupied hash index
    init_MEM(&existTokens_mem, nmail*INIT_UNIQUE_TOKEN_SIZE);
    init_TokenInfo_arr(&tkf, nmail*Q_MODULO);
    init_TxtSmry_arr(smrys, nmail, tkf, Q_MODULO);

}

void kill_MEM_GroupAnalysis(TxtSmry* smrys){
    kill_MEM(&loc_mem);
    kill_MEM(&existTokens_mem);
    kill_TokenInfo_arr(smrys[0].token);
}


void init_TokenInfo(TokenInfo* tkf){
    assert(loc_mem.top_unused+INIT_SPURIOUS_COUNT <= loc_mem.LEN);
    tkf->occur = 0;
    tkf->loc = &loc_mem.ARRAY[loc_mem.top_unused];
    tkf->isRealloc = false;
    loc_mem.top_unused+= INIT_SPURIOUS_COUNT;

    assert(tkf->loc != NULL);
}

void init_TokenInfo_arr(TokenInfo** tkf, ULONG len){ 
    *tkf = (TokenInfo*)malloc(len*sizeof(TokenInfo));
    for(int i=0;i<len;i++){
        init_TokenInfo(&(*tkf)[i]);
    }
}

void kill_TokenInfo_arr(TokenInfo* tkf){
    free(tkf);
}

void init_TxtSmry(TxtSmry* smry, TokenInfo* memToken, int* pin_memToken,int hashMapsize){
    //Check memory is enough
    assert(existTokens_mem.top_unused+INIT_UNIQUE_TOKEN_SIZE <= existTokens_mem.LEN);

    smry->token = &memToken[*pin_memToken];
    smry->existTokens = &existTokens_mem.ARRAY[existTokens_mem.top_unused];

    *pin_memToken += hashMapsize;
    existTokens_mem.top_unused += INIT_UNIQUE_TOKEN_SIZE;

    smry->nToken = 0;
    smry->text = NULL;
    smry->synced = false;
    smry->isRealloc_existTokens = false;
}

void init_TxtSmry_arr(TxtSmry** smry, int len, TokenInfo* memToken, int hashMapsize){
    int pin_memToken = 0;
    *smry = (TxtSmry*)malloc(sizeof(TxtSmry)*len);
    assert(*smry !=NULL);
    for(int i=0;i<len;i++){
        init_TxtSmry(&(*smry)[i], memToken, &pin_memToken, hashMapsize);
    }
}



void kill_TxtSmry_arr(TxtSmry* smry, int len){
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