#include "FindSimilar.h"


void init_MEM(struct MEMORY* mem, ULONG len){
    mem->LEN = len;
    //mem->ARRAY = (int*)malloc(mem->LEN*sizeof(int));
    mem->ARRAY = (int*)calloc( mem->LEN, sizeof(int));
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
    ULONG nmail = (ULONG)n_mails;
    //Location of hashes
    init_MEM(&token_hashmaps, nmail * Q_MODULO);
    //Occupied hash index
    init_MEM(&existTokens_mem, nmail*INIT_UNIQUE_TOKEN_SIZE);
    init_TxtSmry_arr(smrys, nmail, Q_MODULO);

}

void kill_MEM_GroupAnalysis(TxtSmry* smrys){
    kill_MEM(&token_hashmaps);
    kill_MEM(&existTokens_mem);
}


void init_TxtSmry(TxtSmry* smry, int hashMapsize){
    //Check memory is enough
    assert(token_hashmaps.top_unused+hashMapsize <= token_hashmaps.LEN);
    assert(existTokens_mem.top_unused+INIT_UNIQUE_TOKEN_SIZE <= existTokens_mem.LEN);

    smry->token = &token_hashmaps.ARRAY[token_hashmaps.top_unused];
    smry->existTokens = &existTokens_mem.ARRAY[existTokens_mem.top_unused];

    token_hashmaps.top_unused += hashMapsize;
    existTokens_mem.top_unused += INIT_UNIQUE_TOKEN_SIZE;

    smry->nToken = 0;
    smry->text = NULL;
    smry->synced = false;
    smry->isRealloc_existTokens = false;
}

void init_TxtSmry_arr(TxtSmry** smry, int len, int hashmapSize){
    int pin_memToken = 0;
    *smry = (TxtSmry*)malloc(sizeof(TxtSmry)*len);
    assert(*smry !=NULL);
    for(int i=0;i<len;i++){
        init_TxtSmry(&(*smry)[i], hashmapSize);
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