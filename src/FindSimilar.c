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
    return (x*a + b) % Q_RABIN;
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


/**Main API*/
void init_FindSimilar(TxtSmry* smry, int n_mails){
    init_PowerArray(PowerArray, MAX_TOKEN_LEN, D_RABIN, Q_RABIN);
    init_Matrix(&smry->SglM, T_MINIHASH_PERM, n_mails);
}

void kill_FindSimilar(TxtSmry* smry){
    kill_Matrix(&smry->SglM);
}

void Preprocess_FindSimilar(TxtSmry* smry, mail* mails, int n_mails){
    int a[T_MINIHASH_PERM];
    int b[T_MINIHASH_PERM];
}