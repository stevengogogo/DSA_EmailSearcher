#include "FindSimilar.h"

void init_MEM_ULONG(struct MEMORY_ULONG* mem, ULONG len){
    mem->LEN = len;
    //mem->ARRAY = (int*)malloc(mem->LEN*sizeof(int));
    mem->ARRAY = (ULONG*)calloc( mem->LEN, sizeof(ULONG));
    assert(mem->ARRAY != NULL);
    mem->top_unused = 0;
}
void init_MEM_SHORT(struct MEMORY_SHORT* mem, ULONG len){
    mem->LEN = len;
    //mem->ARRAY = (int*)malloc(mem->LEN*sizeof(int));
    mem->ARRAY = (USHORT*)calloc( mem->LEN, sizeof(USHORT));
    assert(mem->ARRAY != NULL);
    mem->top_unused = 0;
}

void kill_MEM_ULONG(struct MEMORY_ULONG* mem){
    free(mem->ARRAY);
    mem->ARRAY = NULL;
    mem->LEN = 0;
    mem->top_unused = EMTY_QUE_SIG;
}

void kill_MEM_SHORT(struct MEMORY_SHORT* mem){
    free(mem->ARRAY);
    mem->ARRAY = NULL;
    mem->LEN = 0;
    mem->top_unused = EMTY_QUE_SIG;
}

void Init_MEM_FindSimilar(TxtSmry** smrys, int n_mails){
    ULONG nmail = (ULONG)n_mails;
    //Location of hashes
    init_MEM_SHORT(&token_hashmaps, nmail * Q_MODULO);
    //Occupied hash index
    init_MEM_ULONG(&existTokens_mem, nmail*INIT_UNIQUE_TOKEN_SIZE);
    init_TxtSmry_arr(smrys, nmail, Q_MODULO);

}

void kill_MEM_FindSimilar(TxtSmry* smrys){
    kill_MEM_SHORT(&token_hashmaps);
    kill_MEM_ULONG(&existTokens_mem);
    free(smrys);
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

TxtSmry* Preprocess_FindSimilar(mail*  mails, int n_mails){
    TxtSmry* smrys;
    Init_MEM_FindSimilar(&smrys, n_mails);

    for(int i=0;i<n_mails;i++){
        summarize_content(&smrys[i], &mails[i]);
    }

    return smrys;
}


void kill_FindSimilar(TxtSmry* smrys){
    kill_MEM_FindSimilar(smrys);
}

void summarize_content(TxtSmry* smry, mail* m){
    summarize_hash(smry, smry->text);
    smry->id = m->id;
    smry->synced = true;
}

void summarize_hash(TxtSmry* smry, char* text){
    smry->text = text;
}