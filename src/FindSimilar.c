#include "FindSimilar.h"

void init_MEM_ULONG(struct MEMORY_ULONG* mem, ULONG len){
    mem->LEN = len;
    //mem->ARRAY = (int*)malloc(mem->LEN*sizeof(int));
    mem->ARRAY = (UINT*)calloc( mem->LEN, sizeof(ULONG));
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

/*******HASH*******/
int popTokenHash(char message[], char token[], int iStr, int* Hash){
    char c;
    int asc; //ascii number
    *Hash = 0; //reset hash value
    int Dn_cur = 0;
    //No string left
    if (iStr < 0){
        token[0] = '\0';
        return -1;
    }

    int i = 0; //token[i]
    while(message[iStr] != '\0' ){
        c = message[iStr];
        asc = (int)c; //ascii number
        Dn_cur = 0;

        if (isRegularExpr_ASCII(asc)){
            if (isUpperCase_ASCII(c))
                c = tolower(c);
            token[i] = c;
            *Hash += updateHash(c, *Hash, &Dn_cur);
            ++i;
            ++iStr;
        }
        else{
            if (i==0){
                ++iStr;
                continue;
            }
            else 
                break;
        }

    }

    if (message[iStr] == '\0'){ // EOF
        iStr= -1;
    }

    token[i] = '\0'; //end of token

    return iStr;
}

int updateHash(char c, int Hash_cur, int* Dn_cur){
    int HashUPD;
    *Dn_cur = (*Dn_cur * D_RABIN) % Q_RABIN;
    HashUPD = Hash_cur * (*Dn_cur) + (int)c;
    HashUPD = HashUPD % Q_RABIN;
    return HashUPD;
}


/*******Main API****/
void Init_FindSimilar(TxtSmry** smrys, int n_mails){
    ULONG nmail = (ULONG)n_mails;
    //Occupied hash index
    init_MEM_ULONG(&existTokens_mem, nmail*INIT_UNIQUE_TOKEN_SIZE);
    init_TxtSmry_arr(smrys, nmail, Q_RABIN);

}



void init_TxtSmry(TxtSmry* smry, int hashMapsize){
    //Check memory is enough
    assert(existTokens_mem.top_unused+INIT_UNIQUE_TOKEN_SIZE <= existTokens_mem.LEN);

    smry->existTokens = &existTokens_mem.ARRAY[existTokens_mem.top_unused];

    existTokens_mem.top_unused += INIT_UNIQUE_TOKEN_SIZE;

    smry->nToken = 0;
    smry->existTokens_DymArr = NULL;
    smry->text = NULL;
    smry->synced = false;
    smry->isExistTokens_DymArr = false;
}

void init_TxtSmry_arr(TxtSmry** smry, int len, int hashmapSize){
    int pin_memToken = 0;
    *smry = (TxtSmry*)calloc(len, sizeof(TxtSmry));
    assert(*smry !=NULL);
    for(int i=0;i<len;i++){
        init_TxtSmry(&(*smry)[i], hashmapSize);
    }
}

void append_hash_TxtSmry(TxtSmry* smry, ULONG hash){
    if(smry->token[hash].count==0){
        add_unique_hashlist(smry, hash);
        ++smry->nToken;
    }
    ++smry->token[hash].count;
}

void add_unique_hashlist(TxtSmry* smry, ULONG hash){
    //Augment array
    if(smry->nToken==INIT_UNIQUE_TOKEN_SIZE){
        smry->existTokens_DymArr = (dymArr_ULONG*)malloc(sizeof(dymArr_ULONG));
        init_dymArr_ULONG(smry->existTokens_DymArr, 2*INIT_UNIQUE_TOKEN_SIZE);

        //Set flag    
        assert(smry->isExistTokens_DymArr == false); //only do this once
        smry->isExistTokens_DymArr = true;
    }

    //Data [INIT...]
    if(smry->isExistTokens_DymArr){
        append_dymArr_ULONG(smry->existTokens_DymArr, hash);
    }
    else{//Data [0,..INIT-1]
        smry->existTokens[smry->nToken] = hash;
    }
    ++smry->nToken;
}

ULONG get_unique_hashlist(TxtSmry* smry, int i){
    ULONG uniHash;
    if (i<INIT_UNIQUE_TOKEN_SIZE){
        uniHash = smry->existTokens[i];
    }
    else{
        int len = smry->existTokens_DymArr->len;
        assert(i-INIT_UNIQUE_TOKEN_SIZE < len);
        uniHash = smry->existTokens_DymArr->i[i-INIT_UNIQUE_TOKEN_SIZE];
    }
    return uniHash;
}

void kill_TxtSmry_arr(TxtSmry* smry, int len){
    for(int i=0;i<len;i++){
        if(smry[i].isExistTokens_DymArr){
            kill_dymArr_ULONG(smry[i].existTokens_DymArr);
            free(smry->existTokens_DymArr);
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
    kill_MEM_ULONG(&existTokens_mem);
}

void summarize_content(TxtSmry* smry, mail* m){
    summarize_hash(smry, smry->text);
    smry->id = m->id;
    smry->synced = true;
}

void summarize_hash(TxtSmry* smry, char* text){
    //Record original text
    smry->text = text;
    //Retrieving Tokens
    char token[TOKEN_STRING_LENGTH];
    int iStr = 0; //Current pin
    int iNxt; //Next pin
    int hash;

    while(1){
        iNxt = popTokenHash(text, token, iStr, &hash);
        if(iNxt == -1){//no token left
            break;
        }

        //TODO


        
    }


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

