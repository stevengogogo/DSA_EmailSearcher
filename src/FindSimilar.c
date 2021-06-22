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

void Init_FindSimilar(TxtSmry** smrys, int n_mails){
    ULONG nmail = (ULONG)n_mails;
    //Location of hashes
    init_MEM_SHORT(&token_hashmaps, nmail * Q_MODULO);
    //Occupied hash index
    init_MEM_ULONG(&existTokens_mem, nmail*INIT_UNIQUE_TOKEN_SIZE);
    init_TxtSmry_arr(smrys, nmail, Q_MODULO);

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
    smry->existTokens_DymArr = NULL;
    smry->text = NULL;
    smry->synced = false;
    smry->isExistTokens_DymArr = false;
}

void init_TxtSmry_arr(TxtSmry** smry, int len, int hashmapSize){
    int pin_memToken = 0;
    *smry = (TxtSmry*)malloc(sizeof(TxtSmry)*len);
    assert(*smry !=NULL);
    for(int i=0;i<len;i++){
        init_TxtSmry(&(*smry)[i], hashmapSize);
    }
}

void append_hash_TxtSmry(TxtSmry* smry, ULONG hash){
    if(smry->token[hash]==0){
        add_unique_hashlist(smry, hash);
        ++smry->nToken;
    }
    ++smry->token[hash];
}

void add_unique_hashlist(TxtSmry* smry, ULONG hash){
    //Augment array
    if(smry->nToken==INIT_UNIQUE_TOKEN_SIZE){
        smry->existTokens_DymArr = (dymArr_ULONG*)malloc(sizeof(dymArr_ULONG));
        init_dymArr_ULONG(smry->existTokens_DymArr, 2*INIT_UNIQUE_TOKEN_SIZE);

        //Copy Content
        memcpy(smry->existTokens_DymArr->i, smry->existTokens, sizeof(ULONG)*INIT_UNIQUE_TOKEN_SIZE);
        smry->existTokens_DymArr->len = INIT_UNIQUE_TOKEN_SIZE;

        //Append
        append_dymArr_ULONG(smry->existTokens_DymArr, hash);

        //Set flag    
        assert(smry->isExistTokens_DymArr = false); //only do this once
        smry->isExistTokens_DymArr = true;
    }
    else{
        smry->existTokens[smry->nToken] = hash;
        ++smry->nToken;
    }

}

void kill_TxtSmry_arr(TxtSmry* smry, int len){
    for(int i=0;i<len;i++){
        if(smry[i].existTokens_DymArr != NULL){
            kill_dymArr_ULONG(smry[i].existTokens_DymArr);
        }
    }
    free(smry);
}

TxtSmry* Preprocess_FindSimilar(mail*  mails, int n_mails){
    TxtSmry* smrys;
    Init_FindSimilar(&smrys, n_mails);

    for(int i=0;i<n_mails;i++){
        summarize_content(&smrys[i], &mails[i]);
    }

    return smrys;
}


void kill_FindSimilar(TxtSmry* smrys, int len){
    kill_TxtSmry_arr(smrys, len);
    kill_MEM_SHORT(&token_hashmaps);
    kill_MEM_ULONG(&existTokens_mem);
}

void summarize_content(TxtSmry* smry, mail* m){
    summarize_hash(smry, smry->text);
    smry->id = m->id;
    smry->synced = true;
}

void summarize_hash(TxtSmry* smry, char* text){
    smry->text = text;
}

/**Helper function*/
void init_dymArr_ULONG(dymArr_ULONG* arr, ULONG size){
    assert(size>=1);
    ULONG* is = (ULONG*)malloc(size*sizeof(ULONG));
    if(is==NULL){
        fprintf(stderr, "Init Error: Insufficient Memory.\n");
        exit(1);
    }

    arr->i = is;
    arr->len = 0;
    arr->size = size;
}

void kill_dymArr_ULONG(dymArr_ULONG* arr){
    arr->size=0;
    arr->len=0;
    free(arr->i);
};

void resize_dymArr_ULONG(dymArr_ULONG* arr, ULONG new_max_size){
    arr->size = new_max_size;
    arr->i = realloc(arr->i, sizeof(ULONG)*new_max_size);
}

void clear_Arr_ULONG(dymArr_ULONG* arr){
    arr->len = 0;
}

void append_dymArr_ULONG(dymArr_ULONG* arr, ULONG val){
    ++(arr->len);
    //Augement size

    if((arr->len+1) > arr->size){
      int new_size = (arr->size)*2 + 1;
      arr->i = realloc(arr->i, sizeof(ULONG)*new_size);
      arr->size = new_size;
      if(arr==NULL){
        fprintf(stderr, "Append Error: Insufficient Memory.\n");
        exit(1);
       }
    }

    arr->i[arr->len - 1] = val;
}

int get_item_ULONG(dymArr_ULONG arr, ULONG i){
    return arr.i[i];
}

int pop_item_ULONG(dymArr_ULONG* arr){
    if(arr->len==0)
        return EMTY_QUE_SIG;
    int val = arr->i[arr->len-1];
    --arr->len;

    return val;
}

