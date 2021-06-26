#include "FindSimilar.h"

/*Tabulation*/
void init_Random_Table(){
    init_Matrix(&RANDOM_T, T_MINIHASH_PERM, T_MINIHASH_PERM*Q_CLUSTER);
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 256; j++){
            RANDOM_T.m[i][j] = getRandomLong();
        }
    }
}

long getRandomLong(){
    long lran = rand();
    return lran;
};

long hash_Tabu(long x, int I){
   long res = 0;
   for (int i = 0; i < T_MINIHASH_PERM; i++){
      res ^= RANDOM_T.m[i][(char)(x >> T_MINIHASH_PERM*i)];
   }
   return res;
}

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
    x = x % PERM_MOD;
    if(x<0){
        x = -x;
    }
    a = a % PERM_MOD;
    return ((x*a) % PERM_MOD + b) % PERM_MOD;
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
    init_Random_Table();
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
    init_Matrix(&hashmap, Q_CLUSTER, n_mails);

    RandGen_long(a, T_MINIHASH_PERM,123, 139412-1, 121213);
    RandGen_long(b, T_MINIHASH_PERM,3, 102221-1, 431333);

    clock_t str, end;
    str = clock();
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
            //Clustr hashing
            hash = (hash*D_CLUSTER) %Q_CLUSTER;

            ele = hashmap.m[hash][id];
            ++ele;
            set_Matrix(&hashmap, hash, id, ele);
            iStr = iNxt;
        }
    }
    end = clock();
    printf("\n[Poptoken]Seconds: %f", (double)(end-str)/ CLOCKS_PER_SEC );
    /*
    for(int i=0;i<Q_CLUSTER;i++){
        printf("%ld %ld\n", hashmap.m[i][0], hashmap.m[i][1]);
    }
    */


    str = clock();
    //mini hash aglorithm
    for(int r=0; r<Q_CLUSTER; r++){//each row
        for(long ih=0; ih<T_MINIHASH_PERM;ih++){//each hash func
            phash[ih] = hash_tabu(r, a[ih], b[ih]);
        }
        for(int c=0;c<n_mails;c++){
            if(hashmap.m[r][c] > 0){
                for(int t=0;t<T_MINIHASH_PERM;t++){
                    if(SglM->m[r][c] > phash[t]){
                        set_Matrix(SglM, t, c, phash[t]);
                        if(phash[t]<0){
                            printf(" ");
                        }
                    }
                }
            }
        }
    }

    end = clock();
    printf("\n[MiniHash]Seconds: %f", (double)(end-str)/ CLOCKS_PER_SEC );

    for(int i=0;i<T_MINIHASH_PERM;i++){
        for(int j=0;j<2;j++){
            printf("%ld ", SglM->m[i][j]);
        }
        printf("\n");
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
    double sim;

    for(int r=0;r<T_MINIHASH_PERM;r++){
        b =  sglM->m[r][IDbase];
        c = sglM->m[r][IDcmp];
        if(b==LONG_MAX || c==LONG_MAX){
            continue;
        }
        ++item;
        if(b==c){++same;}
    }


    sim = same/(same+item);

    return sim;
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
            printf("%f\n",sim);
        }
    }
}