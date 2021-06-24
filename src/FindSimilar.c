#include "FindSimilar.h"

void init_MEM_ULONG(struct MEMORY_ULONG* mem, ULONG len){
    mem->LEN = len;
    //mem->ARRAY = (int*)malloc(mem->LEN*sizeof(int));
    mem->ARRAY = (int*)calloc( mem->LEN, sizeof(int));
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
    //No string left
    if (iStr < 0){
        token[0] = '\0';
        return -1;
    }

    int i = 0; //token[i]
    while(message[iStr] != '\0' ){
        c = message[iStr];
        asc = (int)c; //ascii number

        if (isRegularExpr_ASCII(asc)){
            if (isUpperCase_ASCII(c))
                c = tolower(c);
            token[i] = c;
            *Hash = updateHash(c, *Hash);
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

int updateHash(char c, int Hash_cur){
    int HashUPD;
    HashUPD = Hash_cur * D_RABIN + char2num(c);
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
    smry->maxSpurious = 0;
}

void init_TxtSmry_arr(TxtSmry** smry, int len, int hashmapSize){
    int pin_memToken = 0;
    *smry = (TxtSmry*)calloc(len, sizeof(TxtSmry));
    assert(*smry !=NULL);
    for(int i=0;i<len;i++){
        init_TxtSmry(&(*smry)[i], hashmapSize);
    }
}

void append_hash_TxtSmry(TxtSmry* smry, int hash){
    if(smry->token[hash].count==0){
        _add_unique_hashlist(smry, hash);
        ++smry->nToken;
    }
    ++smry->token[hash].count;
}

void _add_unique_hashlist(TxtSmry* smry, int hash){
    //Augment array
    if(smry->nToken==INIT_UNIQUE_TOKEN_SIZE){
        smry->existTokens_DymArr = (dymArr*)malloc(sizeof(dymArr));
        init_dymArr(smry->existTokens_DymArr, 2*INIT_UNIQUE_TOKEN_SIZE);

        //Set flag    
        assert(smry->isExistTokens_DymArr == false); //only do this once
        smry->isExistTokens_DymArr = true;
    }

    //Data [INIT...]
    if(smry->isExistTokens_DymArr){
        append_dymArr(smry->existTokens_DymArr, hash);
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
            kill_dymArr(smry[i].existTokens_DymArr);
            free(smry[i].existTokens_DymArr);
        }
    }
    free(smry);
}

void Preprocess_FindSimilar(TxtSmry* smrys, mail*  mails, int n_mails){

    for(int i=0;i<n_mails;i++){
        summarize_content(&smrys[i], &mails[i]);
    }
}


void kill_FindSimilar(TxtSmry* smrys, int len){
    kill_TxtSmry_arr(smrys, len);
    kill_MEM_ULONG(&existTokens_mem);
}

void summarize_content(TxtSmry* smry, mail* m){
    smry->id = m->id;
    summarize_hash(smry, m->content);
    smry->synced = true;
}

void summarize_hash(TxtSmry* smry, char* text){
    //Record original text
    smry->text = text;
    //Retrieving Tokens
    char token[TOKEN_STRING_LENGTH];
    char tkH[TOKEN_STRING_LENGTH]; //history token
    int iloc;
    int iStrH = 0;
    int iStr = 0; //Current pin
    int iNxt; //Next pin
    int hash;


    while(1){
        iNxt = popTokenHash(text, token, iStr, &hash);
        if(iNxt == -1){//no token left
            break;
        }

        //Check new token is duplicate
        for(int i=0;i<INIT_SPURIOUS_COUNT;i++){
            if(i<smry->token[hash].count){
                iStrH = smry->token[hash].loc[i];
                iStrH = popToken(text, tkH, iStrH);
                if(strncmp(tkH, token, strlen(token))!=0){
                    if(smry->id==0){
                        printf("%s ", token);
                        printf("%s \n", tkH);
                    }
                }
            }
        }


        //Append unique hash 
        if(smry->token[hash].count==0){//unique token
            append_hash_TxtSmry(smry, hash);
            ++smry->nToken;
        }

        //Append New Hash Until FULL
        if(smry->token[hash].count<INIT_SPURIOUS_COUNT){
            iloc = smry->token[hash].count;
            smry->token[hash].loc[iloc] = iStr;
        }
        ++smry->token[hash].count;

        //Next token
        iStr = iNxt;

        if(smry->maxSpurious<smry->token[hash].count)
            smry->maxSpurious = smry->token[hash].count;
    }


}

