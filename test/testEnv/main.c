#include "api.h"
//#include "api.h"
#ifndef EXPRESSIONMATCH_H
#define EXPRESSIONMATCH_H
/**
 * @file utils.h
 * @author Shao-Ting Chiu (r07945001@ntu.edu.tw)
 * @brief General Utilities for C language
 * @version 0.1
 * @date 2021-03-08
 * @note 
 * Reference
 * 1. Universal Stack is modified from: https://github.com/igniting/generic-stack
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <ctype.h> // tolower
#include <time.h>
#define INIT_NUM_ARRAY_ELEMENT 10
#define EMTY_QUE_SIG -121242
#define MAX_N_MAIL 11000
typedef unsigned char byte;

/************Math************/

/**
 * @brief Get arg max
 * 
 * @param a 
 * @param b 
 * @return int 
 */
int argmax(int a,int b);

/**
 * Check `val` is in [lower,upper]
 */
bool inDomainInt(int val, int lower, int upper);

/************Tokenize************/

/**
 * @brief Pop token from message. 
 * 
 * @param token Buffer string. Token will be saved here. `\0` if no token left
 * @param message main text
 * @param iStr reading head
 * @return int updated reading head `iStr`. -1: end of string
 */
int popToken(char message[], char token[], int iStr);

/**
 * @brief Judge a character belong to regular expression or not
 * @note Regular expression: %[a-zA-Z0-9]
 * @return true 
 * @return false 
 */
bool isRegularExpr_ASCII(int);
bool isNumber_ASCII(int);
bool isUpperCase_ASCII(int);
bool isLowerCase_ASCII(int);
/**
 * @brief [0-9] -> [0-9]; [a-z] -> [10-35]; otherwise: ASCII
 * @param c 
 * @return int 
 */
long char2num(char c);

/************Dynamic Array (Int) Stack**************/
//dynamic array
typedef struct{
    int len;
    int size;
    int* i;
} dymArr;

//init and kill
void init_dymArr(dymArr*, int size);
void kill_dymArr(dymArr*);
void resize_dymArr(dymArr*, int new_max_size);

//clear
void clear_Arr(dymArr*);

//append
/**Append at last*/
void append_dymArr(dymArr*, int val);
/** Get the item of arr[i]*/
int get_item(dymArr, int i);
/** Get the last item
 * @return last element. If no item left, return `EMTY_QUE_SIG`
*/
int pop_item(dymArr*);

/*************Queue************/
typedef struct{
    dymArr arr;
    int head;
    int tail;
} que;

que init_que(int size);
void kill_que(que*);
void enque(que*, int val);
int deque(que*);
int peek_que(que*);

/************Generic Dynamic Array************/

/** Generic copy*/
void copy_item_array(void* dstArr, int locDst,void* srcArr, int locSrc, size_t size);

/** Universal dynamic Array*/
typedef struct uArray{
    int len;
    size_t eleSize;
    byte* memory;
    int num_maxEle;
} uArray;

void init_uArray(uArray* arr, size_t eleSize);
int len_uArray(uArray* arr);
void get_uArray(uArray* arr, int i,void* item);
void set_uArray(uArray* arr, int i,void* item);
void remove_uArray(uArray* arr, int i);
void insert_uArray(uArray* arr, int i,void* item);
void append_uArray(uArray* arr, void* item);
void update_size_uArray(uArray* arr, int new_max_item);
void kill_uArray(uArray* arr);

/*Sorting*/
/** * QuickSort to increasing order. Reference: This function is modified from https://openhome.cc/Gossip/AlgorithmGossip/QuickSort3.htm#C */
void quicksort(int arr[], int left, int right);

/** * Combine fragments. This function is modifed from: https://openhome.cc/Gossip/AlgorithmGossip/QuickSort3.htm#C */
int partition(int number[], int left, int right);

/** * Switch the value store in `x` and `y`. */
void swap(int* x, int* y);

/*Matrix*/
typedef struct Matrix{
    long** m;
    int nrow;
    int ncol;
} Matrix;

/**
 * @brief 2D matrix with one malloc;
 * @note https://stackoverflow.com/questions/8740195/how-do-we-allocate-a-2-d-array-using-one-malloc-statement
*/
void init_Matrix(Matrix* M, int nrow, int ncol);
void kill_Matrix(Matrix* M);
void set_Matrix(Matrix* M, int r, int c, long val);
long get_Matrix(Matrix*M, int r, int c);

/**Random array*/
void RandGen_long(long* arr, int len, long low, long high, int seed);

#endif

#endif
/**
 * @file FindSimilar.h
 * @author Steven Shao-Ting Chiu (r07945001@ntu.edu.tw)
 * @brief Group Analysis. Use Jaccob's similarity with hash table to identify similar strings.
 * @version 0.1
 * @date 2021-06-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef FINDSIMILAR_H
#define FINDSIMILAR_H
//#include "api.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

#include <time.h>

/**********Constant Variable***********/
#define Q_RABIN 170617
#define D_RABIN 257
#define Q_CLUSTER 200

#define PERM_MOD 41723
#define D_CLUSTER 1
#define T_MINIHASH_PERM 3000

#define MAX_TOKEN_LEN 1000
#define MAX_TOKEN_NUM 10000

long PowerArray[MAX_TOKEN_LEN];
static long PrimeArray[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149};

// Simple Tabulation Hash function
static Matrix RANDOM_T;//random table
/**
 * @brief 
 * @note https://en.wikipedia.org/wiki/Tabulation_hashing
 */
void init_Random_Table();
long getRandomLong();
long hash_Tabu(long x, int i);

static long hash_mod(long x,long a,long  b,long c){
    return (a*x + b) % c;
}

static long hash_merge(long x, long i){
    long h1 = hash_mod(x, 13213,241, Q_CLUSTER);
    long h2 = hash_mod(x, 12131, 1, Q_CLUSTER);
    return h1+ i*h2;
}

typedef struct TxtSmry{
    Matrix SglM; //Shingle Matrix
} TxtSmry;

/*Rabin Karp Hashing*/
void init_PowerArray(long* arr, int len, long base, long mod);
long Hash_RK(char tokenStr[]);

/*Permuation*/
/** Tabulation hashing*/
long hash_tabu(long x, long a, long b);

/** Return location*/
int popTokenHash(char message[], char token[], int iStr, long* Hash);
/* x power n*/
long power_long(long x, int n);

/*Minihashing*/
void set_Sgl_Vec(Matrix* SglM, char text[], int ID, long* a, long* b, short* hashMap);
void miniHash(Matrix* SglM, short* hashmap, long a, long b, int iperm, int ID);

/**Main API*/
void init_FindSimilar(TxtSmry* smry, int n_mails);
void kill_FindSimilar(TxtSmry* smry);
void Preprocess_FindSimilar(TxtSmry* smry, mail*  mails, int n_mails);
double similarity(Matrix* sglM, int IDbase, int IDcmp);
void answer_FindSimilar(TxtSmry* smrys, int ID, double threshold, mail* mails, int n_mails, int* SimList, int* lenSim);

#endif
#ifndef GROUPANALYSIS_H
#define GROUPANALYSIS_H

#endif

#include <stdio.h>
#include <time.h>

static void get_mails(char* filename, mail** mails, int* num_mail){
    FILE* fp;
    size_t len;
    ssize_t read;
    //Mail info
    int id;
    int maxnum = 1000000;
    char* line = (char *) malloc(maxnum);
    char* from= (char *) malloc(maxnum);
    char* subject= (char *) malloc(maxnum);
    char* idstr= (char *) malloc(maxnum);
    char* content= (char *) malloc(maxnum);
    char* to= (char *) malloc(maxnum);
    size_t buffer=32;
    size_t chr;
    

    fp = fopen(filename, "r");
    if (fp == NULL)
        printf("File not found");

    chr = getline(&idstr,&buffer,fp);
    sscanf(idstr, "%d", num_mail);
    *mails = (mail*)malloc(*num_mail*sizeof(mail));
    
    for(int i=0;i<*num_mail;i++){
       
        chr = getline(&line,&buffer,fp);
        chr = getline(&idstr,&buffer,fp);
        chr = getline(&from,&buffer,fp);
        chr = getline(&content,&buffer,fp);
        chr = getline(&subject,&buffer,fp);
        chr = getline(&to,&buffer,fp);

        sscanf(idstr, "%d", &id);
        //Check content
        //Copy mail information
        (*mails)[i].id = id;
        strcpy((*mails)[i].subject, subject);
        strcpy((*mails)[i].content, content);
        strcpy((*mails)[i].from, from);
        strcpy((*mails)[i].to, to);

    }

    fclose(fp);
    free(line);
    free(idstr);
    free(content);
    free(subject);
    free(from);
    free(to);
}

int main(void){
 
    int num_mail;
    mail* mails;
    TxtSmry smry;
    int* list = (int*)malloc(sizeof(int)*MAX_N_MAIL);
    int nlist;
    get_mails("test/data/test.in", &mails, &num_mail);
    
    init_FindSimilar(&smry, num_mail);
    Preprocess_FindSimilar(&smry, mails, num_mail);

    double sim = similarity(&smry.SglM, 0, 1);
    printf("Sim: %f\n", sim);
    printf("Test1:\t%s\n", mails[0].content);
    printf("Test2:\t%s\n", mails[1].content);

    //minihash
    for(int i=0;i<T_MINIHASH_PERM;i++){
        printf("%ld %ld\n", smry.SglM.m[0][i], smry.SglM.m[1][i]);
    }

    kill_FindSimilar(&smry);

}

/*
int main(void) {
    // Var: Api
    int n_mails, n_queries;
    mail *mails;
    query *queries;

    //Var: Find Similar
    int* list_FS = (int*)malloc(MAX_N_MAIL*sizeof(int));
    int len_FS;
    int threshold;
    int mid;

    //Initiation
	api.init(&n_mails, &n_queries, &mails, &queries);   
    //Init_FindSimilar(&smrys, n_mails);

    //Preprocessing
    //Preprocess_FindSimilar(smrys, mails, n_mails);

    //Answer
	for(int i = 0; i < n_queries; i++){

		//Find Similar
        if (queries[i].type == find_similar){
            //data
            mid = queries[i].data.find_similar_data.mid;
            threshold = queries[i].data.find_similar_data.threshold;

            //process
            //answer_FindSimilar(smrys, mid, threshold, n_mails, list_FS, &len_FS);

            //answer
            if(len_FS>0){
                api.answer(queries[i].id, list_FS, len_FS);
            }
            else{api.answer(queries[i].id,NULL,0);}
        }
        
        //Expression Match
        else if(queries[i].type == expression_match){
		    //api.answer(queries[i].id, NULL, 0);
        }

        //Group Analysis
        else {
            //api.answer(queries[i].id, NULL, 0);
        }
    }

    //Garbage Collection
    free(mails);
    free(queries);
    free(list_FS);

    return 0;
}
*/

/************Math************/

//Choose the bigger one
int argmax(int a, int b)
{
   if (a>b){
       return 0;
   }
   else{
       return 1;
   }
}

bool inDomainInt(int val, int lower, int upper){
    if(val<=upper && val>=lower)
        return true;
    else
        return false;
}

/************Tokenize************/
int popToken(char message[], char token[], int iStr){
    char c;
    int asc; //ascii number
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

    return iStr;
}

bool isRegularExpr_ASCII(int asc){
    if(isNumber_ASCII(asc))
        return true;
    else if(isUpperCase_ASCII(asc))
        return true;
    else if(isLowerCase_ASCII(asc))
        return true;
    else
        return false;
}

bool isNumber_ASCII(int asc){
    return inDomainInt(asc, 48, 57);
}

bool isUpperCase_ASCII(int asc){
    return inDomainInt(asc, 65, 90);
}

bool isLowerCase_ASCII(int asc){
    return inDomainInt(asc, 97, 122);
}

long char2num(char c){
    if(isNumber_ASCII(c)){
        return (long)c - '0';
    }
    else if(isLowerCase_ASCII(c)){
        return (long)c - 'a' + 10;
    }
    else{
        return (long)c;
    }
}

/********Dynamic Array (Int) stack*********/

void init_dymArr(dymArr* arr, int size){
    assert(size>=1);
    int* is = (int*)malloc(size*sizeof(int));
    if(is==NULL){
        fprintf(stderr, "Init Error: Insufficient Memory.\n");
        exit(1);
    }

    arr->i = is;
    arr->len = 0;
    arr->size = size;
}

void kill_dymArr(dymArr* arr){
    arr->size=0;
    arr->len=0;
    free(arr->i);
};

void resize_dymArr(dymArr* arr, int new_max_size){
    arr->size = new_max_size;
    arr->i = realloc(arr->i, sizeof(int)*new_max_size);
}

void clear_Arr(dymArr* arr){
    arr->len = 0;
}

void append_dymArr(dymArr* arr, int val){
    ++(arr->len);
    //Augement size

    if((arr->len+1) > arr->size){
      int new_size = (arr->size)*2 + 1;
      arr->i = realloc(arr->i, sizeof(int)*new_size);
      arr->size = new_size;
      if(arr==NULL){
        fprintf(stderr, "Append Error: Insufficient Memory.\n");
        exit(1);
       }
    }

    arr->i[arr->len - 1] = val;
}

int get_item(dymArr arr, int i){
    return arr.i[i];
}

int pop_item(dymArr* arr){
    if(arr->len==0)
        return EMTY_QUE_SIG;
    int val = arr->i[arr->len-1];
    --arr->len;

    return val;
}

/*************Queue************/

que init_que(int size){
    que q;
    init_dymArr(&q.arr,size);
    q.head = -1;
    q.tail = -1;
    return q;
}

void kill_que(que* q){
    kill_dymArr(&q->arr);
}

void enque(que* q, int val){
    append_dymArr(&q->arr, val);
    if(q->head == -1){ //first element
        ++(q->head);
    }
    q->tail = q->arr.len - 1;
}

int deque(que* q){
    if(q->head > q->tail || q->head==-1){
        return EMTY_QUE_SIG;
    }

    int val = get_item(q->arr, q->head);
    ++(q->head);
    return val;
}

int peek_que(que* q){
    if(q->head > q->tail || q->arr.len==0)
        return EMTY_QUE_SIG;
    else 
        return q->arr.i[q->head];
}

/************Generic Array************/

void copy_item_array(void* dstArr, int locDst,void* srcArr, int locSrc, size_t size){
    //Start point
    int start_dst = locDst*size;
    int start_src = locSrc*size;

    if (size=sizeof(int)){
        *(int*)(dstArr+start_dst) = *(int*)(srcArr+start_src);
    }
    else if (size=sizeof(long)){
        //printf("f");
        *(long*)(dstArr+start_dst) = *(long*)(srcArr+start_src);
    }
    else{
        //Copy
        memcpy((byte*)(dstArr+start_dst), (byte*)(srcArr+start_src), size);
        //*(byte*)(srcArr+j+start_src) = *(byte*)(dstArr+j+start_dst);
    }
}

void init_uArray(uArray* arr, size_t eleSize){
    byte* mem = (byte*)malloc(eleSize*INIT_NUM_ARRAY_ELEMENT);
    
    //Check memory is allocated
    if(mem==NULL){
        fprintf(stderr, "Stack Init Error: Insufficient Memory.\n");
        exit(1);
    }

    //Initiation
    arr->eleSize = eleSize;
    arr->len = 0;
    arr->memory = mem;
    arr->num_maxEle=INIT_NUM_ARRAY_ELEMENT;
}

int len_uArray(uArray* arr){
    return arr->len;
}

void get_uArray(uArray* arr, int i,void* item){
    //Check i domain
    if (i>=len_uArray(arr) || i<0){
        fprintf(stderr, "Invalid index with array length %d. Got i=%d\n", arr->len, i);
        exit(1);
    }

    //Copy item
    copy_item_array(item, 0, arr->memory, i, arr->eleSize);
}

void set_uArray(uArray* arr, int i,void* item){
    //Check i domain
    if (i>=len_uArray(arr) || i<0){
        fprintf(stderr, "Invalid index with array length %d. Got i=%d\n", arr->len, i);
        exit(1);
    }

    //Copy item
    copy_item_array(arr->memory, arr->len-1, item, 0, arr->eleSize);
}

void remove_uArray(uArray* arr, int I){
    
    for(int i=arr->len-1;i>I;i--){
        copy_item_array(arr->memory, i-1, arr->memory, i, arr->eleSize);
    }

    --arr->len;

    //Shrink memory
    if(arr->len < arr->num_maxEle/2-10){
        update_size_uArray(arr, arr->num_maxEle/2);
    }
}

void insert_uArray(uArray* arr, int I,void* item){

    //For empty array 
    if(arr->len == 0 && I==0){
        append_uArray(arr, item);
        return;
    }

    ++arr->len;
    //Extend memory
    if(arr->len == arr->num_maxEle){
        update_size_uArray(arr, arr->num_maxEle*2+1);
    }

    //Shift right
    for(int i=I;i<arr->len-1;i++){
        copy_item_array(arr->memory, i+1, arr->memory, i, arr->eleSize);
    }

}

void append_uArray(uArray* arr, void* item){
    ++arr->len;
    //Augment size
    if(arr->len == arr->num_maxEle){
        update_size_uArray(arr, arr->num_maxEle*2+1);
    }   

    copy_item_array(arr->memory, arr->len-1, item, 0, arr->eleSize);
}

void update_size_uArray(uArray* arr, int new_max_item){
    arr->num_maxEle = new_max_item;
    arr->memory = realloc(arr->memory, arr->eleSize*arr->num_maxEle);
    if(arr->memory==NULL){
        fprintf(stderr, "Update size error: Invalid Memory allocation with size %d\n", arr->num_maxEle);
        exit(1);
    }
}

void kill_uArray(uArray* arr){
    free(arr->memory);
    arr->eleSize = 0;
    arr->len = 0;
    arr->num_maxEle = 0;
}

/**Sorting**/

void quicksort(int arr[], int left, int right){
    if (left < right){
        int q = partition(arr, left, right);
        quicksort(arr, left, q-1);
        quicksort(arr, q+1, right);
    }
}

int partition(int arr[], int left, int right){
    int i = left-1;
    int j;
    for(j=left; j < right; j++){
        if(arr[j] <= arr[right]){
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i+1], &arr[right]);

    return i+1;
}

void swap(int* x, int* y){
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

/*matrix*/
void init_Matrix(Matrix* M, int nrow, int ncol){
    long **array = malloc(nrow * sizeof *array + (nrow * (ncol * sizeof **array)));
    memset(array, 0, nrow * sizeof *array + (nrow * (ncol * sizeof **array)));
    size_t i;
    long * const data = array + nrow;
    for(i = 0; i < nrow; i++)
        array[i] = data + i * ncol;

    M->m = array;
    M->ncol = ncol;
    M->nrow = nrow;
}

void kill_Matrix(Matrix* M){
    free(M->m);
    M->ncol = 0;
    M->nrow = 0;
}

void set_Matrix(Matrix* M, int r, int c, long val){
    M->m[r][c] = val;
}

long get_Matrix(Matrix*M, int r, int c){
    return M->m[r][c];
}

void RandGen_long(long* arr, int len, long low, long high, int seed){
    long ai;
    srand(seed);
    for(int i=0;i<len;i++){
        ai = rand() % (high-low) + low;

        if(ai==32471){
            --ai;
        }

        arr[i] = ai;
    }
}

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