#include "FindSimilar.h"

/*Rabin Karp Hashing*/
void init_PowerArray(long* arr, int len, long base, long mod){
    long p=1;
    arr[0] = p;
    for(int i=1;i<len;i++){
        p = (p*base) % mod;
        arr[i] = p;
    }
}

long Hash_RK(char tokenStr[]){
    int i=0;
    long hash = 0;
    long Dn;
    long c;
    while(tokenStr[i]!='\0'){
        if(i<MAX_TOKEN_LEN)
            Dn = PowerArray[i];
        else
            Dn = power_long(D_RABIN, i);

        c = char2num(tokenStr[i]);
        hash += (c*Dn) % Q_RABIN;
        ++i;
    }
    return hash % Q_RABIN;
}

long power_long(long x, int n){
    long p = 1;
    for(int i=0;i<n;i++){
        p = p*x % Q_RABIN;
    }
    return p%Q_RABIN;
}

/*Permuation*/
/** Tabulation hashing*/
long hash_tabu(long x, long a, long b){
    return (x*a + b) % PERM_MOD;
}

/** Return location*/
int popTokenHash(char message[], char token[], int iStr, long* Hash){
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
    *Hash = Hash_RK(token);

    return iStr;
}

/*Minihashing*/
void set_Sgl_Vec(Matrix* SglM, char text[], int ID, long* a, long* b, short* hashMap){
    //Rest hash
    memset(hashMap,0, sizeof(short)*Q_RABIN);
    //RK hash map
    int iStr = 0;
    char token[MAX_TOKEN_LEN];
    //long Added[MAX_TOKEN_NUM];
    int iNxt;
    long hash;
    long hi[T_MINIHASH_PERM];


    //Build Hash Map
    while(1){
        iNxt = popTokenHash(text, token, iStr, &hash);
        if(iNxt==-1){
            break;
        }
        ++hashMap[hash];
        iStr = iNxt;
    }

    //Permutation
    for(long i=0; i<T_MINIHASH_PERM;i++){
        miniHash(SglM, hashMap, a[i], b[i], i, ID);
    }

}

void miniHash(Matrix* SglM, short* hashmap, long a, long b, int IP, int ID){
    long perm = 0;
    long i=0;
    perm = hash_tabu(perm, a, b);
    bool run=false;
    for(int h=0;h < Q_RABIN;h++){
        if(hashmap[perm]>0){
            set_Matrix(SglM, IP, ID, perm);
            run = true;
            break;
        }
        perm = hash_tabu(perm, a, b);
        ++i;
    }

    /*
    if(!run){
        printf("Not found: %d %d (a: %ld; b: %ld)\n",IP, ID, a, b);
    }
    */
}

/**Main API*/
void init_FindSimilar(TxtSmry* smry, int n_mails){
    init_PowerArray(PowerArray, MAX_TOKEN_LEN, D_RABIN, Q_RABIN);
    init_Matrix(&smry->SglM, T_MINIHASH_PERM, n_mails);
    for(int r=0;r<T_MINIHASH_PERM;r++){
        for(int c=0; c<n_mails; c++){
            smry->SglM.m[r][c] = LONG_MAX;
        }
    }
}

void kill_FindSimilar(TxtSmry* smry){
    kill_Matrix(&smry->SglM);
}

void Preprocess_FindSimilar(TxtSmry* smry, mail* mails, int n_mails){
    //Build hash map
    char* text;
    char token[MAX_TOKEN_LEN];
    int iStr = 0;
    int iNxt;
    long phash[T_MINIHASH_PERM];
    long ele;
    long hash;
    Matrix* SglM = &smry->SglM;
    //Random Permutation
    long* a = (long*)malloc(sizeof(long)*T_MINIHASH_PERM);
    long* b = (long*)malloc(sizeof(long)*T_MINIHASH_PERM);
    Matrix hashmap;
    init_Matrix(&hashmap, Q_RABIN, n_mails);
    RandGen_long(a, T_MINIHASH_PERM,0, Q_RABIN);
    RandGen_long(b, T_MINIHASH_PERM,0, Q_RABIN);

    //2D hash map [numHash, numDoc]
    for(int id=0;id<n_mails; id++){  
        //Reset  
        text = mails[id].content;
        iStr = 0;
        hash = 0;
        //Build Hash Map
        while(1){
            iNxt = popTokenHash(text, token, iStr, &hash);
            if(iNxt==-1){
                break;
            }
            ele = get_Matrix(&hashmap,  hash, id);
            ++ele;
            set_Matrix(&hashmap, hash, id, ele);
            iStr = iNxt;
        }
    }


    //mini hash aglorithm
    for(int r=0; r<Q_RABIN; r++){//each row
        for(int ih=0; ih<T_MINIHASH_PERM;ih++){//each hash func
            phash[ih] = hash_tabu(phash[ih], a[ih], b[ih]);

        }
        for(int c=0;c<n_mails;c++){
            if(get_Matrix(&hashmap, r, c) > 0){
                for(int h=0;h<T_MINIHASH_PERM;h++){
                    if(get_Matrix(SglM, h, c) > phash[h]){
                        set_Matrix(SglM, h, c, phash[h]);
                    }
                }
            }
        }
    }

    //GC
    kill_Matrix(&hashmap);
    free(a);
    free(b);
}



double similarity(Matrix* sglM, int IDbase, int IDcmp){
    long b, c;
    double item=0;
    double same=0;

    for(int r=0;r<sglM->nrow;r++){
        b = get_Matrix(sglM, r, IDbase);
        c = get_Matrix(sglM, r, IDcmp);
        if(b==LONG_MAX || c==LONG_MAX){
            continue;
        }
        ++item;
        if(b==c){++same;}
    }
    return same/(same+item);
}

void answer_FindSimilar(TxtSmry* smry, int ID, double threshold, mail* mails, int n_mails, int* SimList, int* lenSim){
    int IDcmp;
    double sim;
    *lenSim = 0;
    for(int i=0;i<n_mails;i++){
        IDcmp = mails[i].id;
        
        if(IDcmp == ID){ 
            continue;
        }

        sim = similarity(&smry->SglM, ID, IDcmp);

        if(sim>threshold){
            SimList[*lenSim] = IDcmp;
            ++(*lenSim);
        }
    }
}